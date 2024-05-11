use named_constants::named_constants;

#[named_constants]
#[repr(u64)]
pub enum ScriptNetVarName {
    skyDiveTrailOverrideIndex = 0x3ed944f235cc8e5e,
    playerAllowedToLeech = 0x83ec8fcbf2d0443d,
    isOptInServer = 0x536e4975305dfbb9,
    gameStateChangeTime = 0x89cd3aa36240a90e,
    gameStartTime = 0x726174544e837083,
    gameEndTime = 0x54646e45664870c6,
    switchedSides = 0x6465686424faa59f,
    replayDisabled = 0x694479704d155b4b,
    roundWinningKillReplayEnabled = 0xd363b2c4d7fe65f2,
    roundWinningKillReplayPlaying = 0xdd1eb2c236d7d00f,
    roundScoreLimitComplete = 0x3bad85364716303f,
    roundWinningKillReplayEntHealthFrac = 0x34d4fe6b0e0ebcff,
    badRepPresent = 0x725070661eb1e018,
    roundBased = 0x736142646e8192ce,
    roundStartTime = 0x617453735b0b6157,
    roundEndTime = 0x646e456478bb6295,
    roundsPlayed = 0x6c5073647b0b6689,
    PreGameStartTime = 0xb5911db4f59f3341,
    winningTeam = 0x54676e696f30c516,
    attackingTeam = 0x6e696b642161ca25,
    characterIndex = 0x6574637019dbe048,
    overrideRUIType = 0x65646980b690ddb9,
    skinIndex = 0x65646e496e6a59fc,
    frameIndex = 0x646e49656d6dbec2,
    stanceIndex = 0x6e4965636f216cfe,
    firstBadgeIndex = 0x64614276a70ce166,
    firstBadgeDataInt = 0x77eb42eb9ff82942,
    secondBadgeIndex = 0xd840ef39bec8497a,
    secondBadgeDataInt = 0xe8bcff24a12ac18c,
    thirdBadgeIndex = 0x64614266a413e078,
    thirdBadgeDataInt = 0x77e8bcffb943326c,
    lootRarity = 0x69726152747d8c08,
    ownerEHI = 0x49484572656e7879,
    hasShipKeycard = 0x4b706974a8282075,
    hasDeathFieldImmunity = 0xfe62efe569bab84d,
    isMapZoneDisplayTextDisabled = 0xf909020ec4c1d528,
    pickLoadoutGamestateStartTime = 0x56250044dc20aca5,
    pickLoadoutGamestateEndTime = 0x70380ad41f8950fc,
    hasLockedInCharacter = 0x4d52cb4011292455,
    lockedInCharacterTime = 0x247a2d20fba71b31,
    characterSelectLockstepPlayerIndex = 0x5591ada40e5212c2,
    characterSelectFocusCharacterGUID = 0x733ce8339604bc0,
    characterSelectFocusSkinGUID = 0x854ca4acf4fcbd57,
    characterSelectionReady = 0x8b014350c5753c99,
    characterSelectLockstepIndex = 0xfbc5a2dd7f477856,
    characterSelectLockstepStartTime = 0xb2568da0f08bb56c,
    characterSelectLockstepEndTime = 0xf7c27c9d4e82fcfd,
    characterSelectPicksEndTime = 0x65c9b9bc567a0331,
    squadPresentationStartTime = 0x9857f744700bd2c9,
    championSquadPresentationStartTime = 0x4e853294e58ab8aa,
    championEEH = 0x6e6f69706de08fae,
    championSquad1EEH = 0x40a150be446c28d6,
    championSquad2EEH = 0x40a153be446c28d6,
    focalTrap = 0x6172546c61645541,
    coverFireMeter = 0x7269467ed5951f80,
    coverFireLocked = 0x72694675a4439d59,
    gladCardPlayer = 0x6472614e184f9c9c,
    hasDataKnife = 0x4b61746151c358a3,
    isEliminated = 0x6e696d69794546f0,
    isJumpmaster = 0x616d706d839fe358,
    isJumpingWithSquad = 0x3050cd5f09f6317d,
    playerInPlane = 0x6e4972662d616e7a,
    freefallActive = 0x6c6c616f18d0d663,
    freefallEmoteAvailable = 0x6671e931b74f9a90,
    freefallIsFromPlane = 0x789bd3f3b7eefe9b,
    inventoryEnabled = 0xbc80a324ccef8145,
    isScoreboardEnabled = 0xa5cc6aa2a74dc16c,
    pingEnabled = 0x62616e456842d8e9,
    kills = 0x6dfab35,
    damageDealt = 0x65446567623812dd,
    assists = 0x645e4337,
    isHealing = 0x6e696c616549425e,
    healingKitTypeCurrentlyBeingUsed = 0x3fba6084946723dd,
    isReceivingFirstAid = 0x29531d4db9268a12,
    selectedHealthPickupType = 0x848953974c9e839a,
    TrainingEndTime = 0x676e697541d76654,
    playerPrimaryWeapon0 = 0xba57b2a650cbf770,
    playerPrimaryWeapon1 = 0xba57b2a650cbb763,
    anonymizePlayerName = 0xc0531d7ccab9a08b,
    nv_PlayerMatchState = 0x59a48f24ff398b44,
    respawnStatus = 0x536e776250250b9c,
    respawnStatusEndTime = 0xb476b81a5065c7b2,
    respawnBannerPickedUpTime = 0x85b3cff36a287c76,
    respawnsRemaining = 0x8a7d8f0ebc65294f,
    currentDeathFieldStage = 0x48643d6cf521d143,
    nextCircleStartTime = 0xb8ec5c6388c548de,
    circleCloseTime = 0x53bc9aa360106f45,
    PlaneDoorsOpenTime = 0x1c778849f7d51c98,
    PlaneDoorsCloseTime = 0x31469553dfe5cec1,
    connectedPlayerCount = 0x6e2f886746bff353,
    livingPlayerCount = 0x7fc6118252dac63c,
    squadsRemainingCount = 0x625804b40705faa8,
    gameState = 0x74617453656e2844,
    skydiveFreelookActive = 0x59d6ec24d32ce8cb,
    skydiveFollowPlayer = 0x79d10d571de9cd66,
    killLeader = 0x6461654c6c78a51f,
    craftingMaterials = 0x13645b282d3ab90d,
    Crafting_NumHarvesters = 0x1975423de0179993,
    Crafting_NumWorkbenches = 0x1475503781977eaa,
    Crafting_StartTime = 0x179354282e8d2312,
    forcedDialogueOnly = 0xd8696f5e533ee026,
    PilotAbilitySelectMenu_Enabled = 0xe1c8b97a4ea8f0e0,
    respawnAvailableBits0 = 0xe2f89b18338056b4,
    respawnAvailableBits1 = 0xe2f89b18338096ad,
    respawnAvailableBits2 = 0xe2f89b183381d0ea,
    respawnAvailableBits3 = 0xe2f89b1833801cfb,
    bleedoutEndTime = 0x74756f6b4ddb6c46,
    bleedoutType = 0x74756f646fa4d725,
    reviveEndTime = 0x6e4565772b4874b4,
    reviveType = 0x7954657669853812,
    hackStartTime = 0x7261745448957082,
    revivePlayerHealer = 0x7dd2480554984268,
    xpMultiplier = 0x7069746c82ac80af,
    tutorialContext = 0x6c61697de18cc468,
    spectatorTargetCount = 0x22a9cd26dc806be5,
    cameraNearbyEnemySquads = 0x80f4361ab095bbe0,
    uiGameStartTime = 0x7453657a79f96f73,
    uiDisableDev = 0x6c62617375e1ddfc,
    Loadout_CharacterSelection = 0x3db0a8e87e98867a,
    Loadout_CharacterSkin = 0x34945bb7aaa34056,
    Loadout_IntroQuip = 0x6e69746f6d46425e,
    Loadout_KillQuip = 0x29a135f6b5d39cdb,
    Loadout_GladiatorCardFrame = 0x9436c16ca93c0d70,
    Loadout_GladiatorCardStance = 0x9430fc72be449d9b,
    Loadout_GladiatorCardBadge0 = 0xeb05cd72739b39f0,
    Loadout_GladiatorCardBadge0Tier = 0xeb053ffc62b3f4b1,
    Loadout_GladiatorCardBadge1 = 0xeb05cd727cd22492,
    Loadout_GladiatorCardBadge1Tier = 0xeb053ff3b246b4b1,
    Loadout_GladiatorCardBadge2 = 0xeb05cd727c8bd38d,
    Loadout_GladiatorCardBadge2Tier = 0xeb053fcfd02e74b1,
    Loadout_GladiatorCardTracker0 = 0x9436fbe36e9e071d,
    Loadout_GladiatorCardTracker0Value = 0x8c79fc9923831a27,
    Loadout_GladiatorCardTracker1 = 0x9436fbe36e894810,
    Loadout_GladiatorCardTracker1Value = 0x8c79fc9823831a27,
    Loadout_GladiatorCardTracker2 = 0x9436fbe36eeffb5b,
    Loadout_GladiatorCardTracker2Value = 0x8c79fc9723831a27,
    Loadout_SkydiveTrail = 0x5a534dcc3cc1d6d,
    ApexScreensMasterState_Pos0_CommenceTime = 0x68bbfe7f3a79e54b,
    ApexScreensMasterState_Pos0_ModeIndex = 0x41e22bac6ca79828,
    ApexScreensMasterState_Pos0_TransitionStyle = 0xb804bf032da912ae,
    ApexScreensMasterState_Pos0_Player = 0x43317f408eac4d22,
    ApexScreensMasterState_Pos1_CommenceTime = 0x68bbfe7f3a98254b,
    ApexScreensMasterState_Pos1_ModeIndex = 0x41e22bac6ca69828,
    ApexScreensMasterState_Pos1_TransitionStyle = 0xb804bf032dca52ae,
    ApexScreensMasterState_Pos1_Player = 0xb5ff48bcdb49cef1,
    ApexScreensMasterState_Pos2_CommenceTime = 0x68bbfe7f35b5654b,
    ApexScreensMasterState_Pos2_ModeIndex = 0x41e22bac6ca59828,
    ApexScreensMasterState_Pos2_TransitionStyle = 0xb804bf032dea92ae,
    ApexScreensMasterState_Pos2_Player = 0xb5ff48bcdb48cef1,
    NV_ApexScreensEventTimeA = 0x3d8b260ccb6083f9,
    NV_ApexScreensEventTimeB = 0x3c8b260ccb6083f9,
    NV_ApexScreensEventIntA = 0xa9485ec2027b2905,
}
