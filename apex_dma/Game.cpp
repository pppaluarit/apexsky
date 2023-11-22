#include "prediction.h"
#include <array>
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

extern Memory apex_mem;

extern bool firing_range;

float bulletspeed = 0.08;
float bulletgrav = 0.05;

// glowtype not used, but dont delete its still used.
extern int glowtype;
extern int glowtype2;
// setting up vars, dont edit
extern float smooth;
extern bool aim_no_recoil;
extern int bone;
bool bone_auto = true;
extern float veltest;
extern float max_dist;

bool Entity::Observing(uint64_t entitylist) {
  return *(bool *)(buffer + OFFSET_OBSERVER_MODE);
}

// https://github.com/CasualX/apexbot/blob/master/src/state.cpp#L104
void get_class_name(uint64_t entity_ptr, char *out_str) {
  uint64_t client_networkable_vtable;
  apex_mem.Read<uint64_t>(entity_ptr + 8 * 3, client_networkable_vtable);

  uint64_t get_client_class;
  apex_mem.Read<uint64_t>(client_networkable_vtable + 8 * 3, get_client_class);

  uint32_t disp;
  apex_mem.Read<uint32_t>(get_client_class + 3, disp);
  const uint64_t client_class_ptr = get_client_class + disp + 7;

  ClientClass client_class;
  apex_mem.Read<ClientClass>(client_class_ptr, client_class);

  apex_mem.ReadArray<char>(client_class.pNetworkName, out_str, 32);
}

int Entity::getTeamId() { return *(int *)(buffer + OFFSET_TEAM); }

int Entity::getHealth() { return *(int *)(buffer + OFFSET_HEALTH); }
// seer health and shield i added

int Entity::getArmortype() {
  int armortype;
  apex_mem.Read<int>(ptr + OFFSET_ARMORTYPE, armortype);
  return armortype;
}

int Entity::getShield() { return *(int *)(buffer + OFFSET_SHIELD); }

int Entity::getMaxshield() { return *(int *)(buffer + OFFSET_MAXSHIELD); }

Vector Entity::getAbsVelocity() {
  return *(Vector *)(buffer + OFFSET_ABS_VELOCITY);
}

Vector Entity::getPosition() { return *(Vector *)(buffer + OFFSET_ORIGIN); }

bool Entity::isPlayer() {
  return *(uint64_t *)(buffer + OFFSET_NAME) == 125780153691248;
}
// firing range dummys
bool Entity::isDummy() {
  char class_name[33] = {};
  get_class_name(ptr, class_name);

  return strncmp(class_name, "CAI_BaseNPC", 11) == 0;
}

bool Entity::isKnocked() {
  return *(int *)(buffer + OFFSET_BLEED_OUT_STATE) > 0;
}

bool Entity::isAlive() { return *(int *)(buffer + OFFSET_LIFE_STATE) == 0; }

float Entity::lastVisTime() { return *(float *)(buffer + OFFSET_VISIBLE_TIME); }

float Entity::lastCrossHairTime() {
  return *(float *)(buffer + OFFSET_CROSSHAIR_LAST);
}

Vector Entity::getBonePositionByHitbox(int id) {
  Vector origin = getPosition();

  // BoneByHitBox
  uint64_t Model = *(uint64_t *)(buffer + OFFSET_STUDIOHDR);

  // get studio hdr
  uint64_t StudioHdr;
  apex_mem.Read<uint64_t>(Model + 0x8, StudioHdr);

  // get hitbox array
  uint16_t HitboxCache;
  apex_mem.Read<uint16_t>(StudioHdr + 0x34, HitboxCache);
  uint64_t HitboxArray =
      StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));

  uint16_t IndexCache;
  apex_mem.Read<uint16_t>(HitboxArray + 0x4, IndexCache);
  int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));

  uint16_t Bone;
  apex_mem.Read<uint16_t>(HitboxIndex + HitboxArray + (id * 0x20), Bone);

  if (Bone < 0 || Bone > 255)
    return Vector();

  // hitpos
  uint64_t Bones = *(uint64_t *)(buffer + OFFSET_BONES);

  matrix3x4_t Matrix = {};
  apex_mem.Read<matrix3x4_t>(Bones + Bone * sizeof(matrix3x4_t), Matrix);

  return Vector(Matrix.m_flMatVal[0][3] + origin.x,
                Matrix.m_flMatVal[1][3] + origin.y,
                Matrix.m_flMatVal[2][3] + origin.z);
}

QAngle Entity::GetSwayAngles() {
  return *(QAngle *)(buffer + OFFSET_BREATH_ANGLES);
}

QAngle Entity::GetViewAngles() {
  return *(QAngle *)(buffer + OFFSET_VIEWANGLES);
}

Vector Entity::GetViewAnglesV() {
  return *(Vector *)(buffer + OFFSET_VIEWANGLES);
}

float Entity::GetYaw() {
  float yaw = 0;
  apex_mem.Read<float>(ptr + OFFSET_YAW, yaw);

  if (yaw < 0)
    yaw += 360;
  yaw += 90;
  if (yaw > 360)
    yaw -= 360;

  return yaw;
}

bool Entity::isGlowing() { return *(int *)(buffer + OFFSET_GLOW_ENABLE) == 7; }

bool Entity::isZooming() { return *(int *)(buffer + OFFSET_ZOOMING) == 1; }

extern uint64_t g_Base;
extern int settingIndex;
extern int contextId;
extern std::array<float, 3> highlightParameter;
// custom glow colo RGB
unsigned char outsidevalue = 125;
extern unsigned char insidevalue;
extern unsigned char insidevalueItem;
extern unsigned char outlinesize;
void Entity::enableGlow() {
  // static const int contextId = 5;
  // int settingIndex = 44;
  std::array<unsigned char, 4> highlightFunctionBits = {
      insidevalue,  // InsideFunction
      outsidevalue, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE
      outlinesize,  // OutlineRadius: size * 255 / 8
      64 // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7)
  };
  // std::array<float, 3> highlightParameter = { 0, 1, 0 };
  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, contextId);
  apex_mem.Write<unsigned char>(
      ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + contextId, settingIndex);

  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 1);
  apex_mem.Write<unsigned char>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 1,
                                settingIndex);

  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 2);
  apex_mem.Write<unsigned char>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 2,
                                settingIndex);

  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 3);
  apex_mem.Write<unsigned char>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 3,
                                settingIndex);

  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 4);
  apex_mem.Write<unsigned char>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 4,
                                settingIndex);
  // apex_mem.Write<int>(ptr + 0x298 + contextId, settingIndex);
  long highlightSettingsPtr;
  apex_mem.Read<long>(g_Base + HIGHLIGHT_SETTINGS, highlightSettingsPtr);
  apex_mem.Write<int>(ptr + OFFSET_GLOW_THROUGH_WALLS, 2);
  apex_mem.Write<typeof(highlightFunctionBits)>(
      highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * settingIndex + 4,
      highlightFunctionBits);
  apex_mem.Write<typeof(highlightParameter)>(
      highlightSettingsPtr + HIGHLIGHT_TYPE_SIZE * settingIndex + 8,
      highlightParameter);
  apex_mem.Write(g_Base + 0x270, 1);
  apex_mem.Write(ptr + 0x270, 1);
  // printf("%f\n", deltaTime2);
}
void Entity::disableGlow() {

  // apex_mem.Write<int>(ptr + OFFSET_GLOW_T1, 0);
  // apex_mem.Write<int>(ptr + OFFSET_GLOW_T2, 0);
  // apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 2);
  // apex_mem.Write<int>(ptr + OFFSET_GLOW_THROUGH_WALLS, 5);
  // apex_mem.Write<float>(ptr + GLOW_COLOR_R, 0.0f);
  // apex_mem.Write<float>(ptr + GLOW_COLOR_G, 0.0f);
  // apex_mem.Write<float>(ptr + GLOW_COLOR_B, 0.0f);
  // apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 2);
  // apex_mem.Write<int>(ptr + OFFSET_GLOW_THROUGH_WALLS, 5);
}

void Entity::SetViewAngles(SVector angles) {
  apex_mem.Write<SVector>(ptr + OFFSET_VIEWANGLES, angles);
}

void Entity::SetViewAngles(QAngle &angles) { SetViewAngles(SVector(angles)); }

Vector Entity::GetCamPos() { return *(Vector *)(buffer + OFFSET_CAMERAPOS); }

QAngle Entity::GetRecoil() { return *(QAngle *)(buffer + OFFSET_AIMPUNCH); }

void Entity::get_name(uint64_t g_Base, uint64_t index, char *name) {
  index *= 0x10;
  uint64_t name_ptr = 0;
  apex_mem.Read<uint64_t>(g_Base + OFFSET_NAME_LIST + index, name_ptr);
  apex_mem.ReadArray<char>(name_ptr, name, 32);
}

// Items
bool Item::isItem() {
  char class_name[33] = {};
  get_class_name(ptr, class_name);

  return strncmp(class_name, "CPropSurvival", 13) == 0;
}
// Deathboxes
bool Item::isBox() {
  char class_name[33] = {};
  get_class_name(ptr, class_name);

  return strncmp(class_name, "CDeathBoxProp", 13) == 0;
}
// Traps
bool Item::isTrap() {
  char class_name[33] = {};
  get_class_name(ptr, class_name);

  return strncmp(class_name, "caustic_trap", 13) == 0;
}

bool Item::isGlowing() {
  return *(int *)(buffer + OFFSET_ITEM_GLOW) == 1363184265;
}

void Item::enableGlow() {
  /* for (int i = 1; i <= 70; i++) {
  // Write the current value to the memory locations
  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 6);
  apex_mem.Write<int>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 2, 6);

  // Print the current value
  std::cout << "Value: " << i << std::endl;

  // Sleep for 2 seconds
  std::this_thread::sleep_for(std::chrono::seconds(5));
} */
  /* //apex_mem.Write<GlowMode>(ptr + GLOW_TYPE, { 101,102,96,90 });
      apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 6);
      apex_mem.Write<int>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 6, 6);
  apex_mem.Write<int>(ptr + OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE , 2); */

  // apex_memRead<uint32_t>(entity + OFFSET_HIGHLIGHTCURRENTCONTEXTID);
}

void Item::disableGlow() {
  apex_mem.Write<int>(ptr + OFFSET_GLOW_ENABLE, 0);
  apex_mem.Write<int>(ptr + OFFSET_HIGHLIGHTSERVERACTIVESTATES + 0, 0);
  apex_mem.Write<int>(ptr + OFFSET_GLOW_THROUGH_WALLS_GLOW_VISIBLE_TYPE, 5);
}

Vector Item::getPosition() { return *(Vector *)(buffer + OFFSET_ORIGIN); }

float CalculateFov(Entity &from, Entity &target) {
  QAngle ViewAngles = from.GetSwayAngles();
  Vector LocalCamera = from.GetCamPos();
  Vector EntityPosition = target.getPosition();
  QAngle Angle = Math::CalcAngle(LocalCamera, EntityPosition);
  return Math::GetFov(ViewAngles, Angle);
}

QAngle CalculateBestBoneAim(Entity &from, uintptr_t t, float max_fov) {
  Entity target = getEntity(t);
  if (firing_range) {
    if (!target.isAlive()) {
      return QAngle(0, 0, 0);
    }
  } else {
    if (!target.isAlive() || target.isKnocked()) {
      return QAngle(0, 0, 0);
    }
  }

  Vector LocalCamera = from.GetCamPos();
  Vector TargetBonePosition;
  float distanceToTarget;
  QAngle CalculatedAngles = QAngle(0, 0, 0);

  WeaponXEntity curweap = WeaponXEntity();
  curweap.update(from.ptr);
  float BulletSpeed = curweap.get_projectile_speed();
  float BulletGrav = curweap.get_projectile_gravity();
  float zoom_fov = curweap.get_zoom_fov();

  if (zoom_fov != 0.0f && zoom_fov != 1.0f) {
    max_fov *= zoom_fov / 90.0f;
  }

  // Find best bone
  if (bone_auto) {
    float NearestBoneDistance = max_dist;
    for (int i = 0; i < 4; i++) {
      Vector currentBonePosition = target.getBonePositionByHitbox(i);
      float DistanceFromCrosshair =
          (currentBonePosition - LocalCamera).Length();
      if (DistanceFromCrosshair < NearestBoneDistance) {
        TargetBonePosition = currentBonePosition;
        distanceToTarget = DistanceFromCrosshair;
        NearestBoneDistance = DistanceFromCrosshair;
      }
    }
  } else {
    TargetBonePosition = target.getBonePositionByHitbox(bone);
    distanceToTarget = (TargetBonePosition - LocalCamera).Length();
  }

  if (BulletSpeed > 1.f) {

    PredictCtx Ctx;
    Ctx.StartPos = LocalCamera;
    Ctx.TargetPos = TargetBonePosition;
    Ctx.BulletSpeed = BulletSpeed - (BulletSpeed * bulletspeed);
    Ctx.BulletGravity = BulletGrav + (BulletGrav * bulletgrav);

    // Get the target's velocity and add it to the prediction context
    Vector targetVel = target.getAbsVelocity();

    // Calculate the time since the last frame (in seconds)
    float deltaTime = 0.0133333;

    // Add the target's velocity to the prediction context, with an offset in
    // the y direction
    float timeToTarget = distanceToTarget / BulletSpeed;
    Vector targetPosAhead = TargetBonePosition + (targetVel * timeToTarget);
    Ctx.TargetVel =
        Vector(targetVel.x, targetVel.y + (targetVel.Length() * deltaTime),
               targetVel.z);
    Ctx.TargetPos = targetPosAhead;

    if (BulletPredict(Ctx))
      CalculatedAngles = QAngle{Ctx.AimAngles.x, Ctx.AimAngles.y, 0.f};
  }

  if (CalculatedAngles == QAngle(0, 0, 0))
    CalculatedAngles = Math::CalcAngle(LocalCamera, TargetBonePosition);
  QAngle ViewAngles = from.GetViewAngles();
  QAngle SwayAngles = from.GetSwayAngles();
  double fov = Math::GetFov(SwayAngles, CalculatedAngles);
  if (fov > max_fov) {
    return QAngle(0, 0, 0);
  }

  if (aim_no_recoil)
    CalculatedAngles -= SwayAngles - ViewAngles;
  Math::NormalizeAngles(CalculatedAngles);
  QAngle Delta = CalculatedAngles - ViewAngles;

  Math::NormalizeAngles(Delta);

  QAngle SmoothedAngles = ViewAngles + Delta / smooth;
  return SmoothedAngles;
}

Entity getEntity(uintptr_t ptr) {
  Entity entity = Entity();
  entity.ptr = ptr;
  apex_mem.ReadArray<uint8_t>(ptr, entity.buffer, sizeof(entity.buffer));
  return entity;
}

Item getItem(uintptr_t ptr) {
  Item entity = Item();
  entity.ptr = ptr;
  apex_mem.ReadArray<uint8_t>(ptr, entity.buffer, sizeof(entity.buffer));
  return entity;
}

bool WorldToScreen(Vector from, float *m_vMatrix, int targetWidth,
                   int targetHeight, Vector &to) {
  float w = m_vMatrix[12] * from.x + m_vMatrix[13] * from.y +
            m_vMatrix[14] * from.z + m_vMatrix[15];

  if (w < 0.01f)
    return false;

  to.x = m_vMatrix[0] * from.x + m_vMatrix[1] * from.y + m_vMatrix[2] * from.z +
         m_vMatrix[3];
  to.y = m_vMatrix[4] * from.x + m_vMatrix[5] * from.y + m_vMatrix[6] * from.z +
         m_vMatrix[7];

  float invw = 1.0f / w;
  to.x *= invw;
  to.y *= invw;

  float x = targetWidth / 2;
  float y = targetHeight / 2;

  x += 0.5 * to.x * targetWidth + 0.5;
  y -= 0.5 * to.y * targetHeight + 0.5;

  to.x = x;
  to.y = y;
  to.z = 0;
  return true;
}

void WeaponXEntity::update(uint64_t LocalPlayer) {
  extern uint64_t g_Base;
  uint64_t entitylist = g_Base + OFFSET_ENTITYLIST;
  uint64_t wephandle = 0;
  apex_mem.Read<uint64_t>(LocalPlayer + OFFSET_WEAPON, wephandle);

  wephandle &= 0xffff;

  uint64_t wep_entity = 0;
  apex_mem.Read<uint64_t>(entitylist + (wephandle << 5), wep_entity);

  projectile_speed = 0;
  apex_mem.Read<float>(wep_entity + OFFSET_BULLET_SPEED, projectile_speed);
  projectile_scale = 0;
  apex_mem.Read<float>(wep_entity + OFFSET_BULLET_SCALE, projectile_scale);
  zoom_fov = 0;
  apex_mem.Read<float>(wep_entity + OFFSET_ZOOM_FOV, zoom_fov);
  ammo = 0;
  apex_mem.Read<int>(wep_entity + OFFSET_AMMO, ammo);
}

float WeaponXEntity::get_projectile_speed() { return projectile_speed; }

float WeaponXEntity::get_projectile_gravity() {
  return 750.0f * projectile_scale;
}

float WeaponXEntity::get_zoom_fov() { return zoom_fov; }

int WeaponXEntity::get_ammo() { return ammo; }
