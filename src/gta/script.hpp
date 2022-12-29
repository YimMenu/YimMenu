#pragma once
#include "natives.hpp"
#include "core/enums.hpp"

#define PLAYER_INDEX alignas(8) Player
#define ENTITY_INDEX alignas(8) Entity
#define PED_INDEX alignas(8) Ped
#define VEHICLE_INDEX alignas(8) Vehicle
#define INTERIOR_INDEX alignas(8) Interior

#define SCR_HASH alignas(8) Hash
#define SCR_INT alignas(8) int
#define SCR_BOOL alignas(8) BOOL
#define SCR_FLOAT alignas(8) float
#define SCR_VEC3 Vector3

template <int SIZE>
struct SCR_TEXT_LABEL
{
    alignas(8) char Data[SIZE];
private:
    alignas(8) char _PAD[SIZE];
public:
    operator char* () { return Data; }
};

// this is not a typo
#define TEXT_LABEL_15 SCR_TEXT_LABEL<16>
#define TEXT_LABEL_23 SCR_TEXT_LABEL<24>
#define TEXT_LABEL_31 SCR_TEXT_LABEL<32>
#define TEXT_LABEL_63 SCR_TEXT_LABEL<64>

template <typename T, int SIZE>
struct SCR_ARRAY
{
    SCR_INT      Size;
    alignas(8) T Data[SIZE];

    T& operator [](int index)
    {
        return Data[index];
    }
};

template <typename T>
struct SCR_BITSET
{
    alignas(8) int Value;

    bool operator [](T val)
    {
        return Value & (1 << (int)val);
    }

    void Set(T val)
    {
        Value |= (1 << (int)val);
    }

    void Clear(T val)
    {
        Value &= ~(1 << (int)val);
    }
};

struct Color3
{
    SCR_INT R;
    SCR_INT G;
    SCR_INT B;
};
static_assert(sizeof(Color3) == 3 * 8);

// serialized bitbuffer data of rage::rlGamerHandle + some padding for last gen compatibility
struct GAMER_HANDLE
{
private:
    uint64_t Data[13];
};
static_assert(sizeof(GAMER_HANDLE) == 13 * 8);

enum class eFreemodeState
{
    NONE = 0,
    UNK_2 = 2,
    RUNNING = 4,
    CLOSING = 5,
    UNK_10 = 10,
    UNK_11 = 11
};

enum class eMissionType
{
    NONE,
    MISSION,
    HEIST,
    UNK_3,
    ADVERSARY_MODE,
    LAST_TEAM_STANDING,
    CAPTURE,
    HEIST_SETUP,
    UNK_8, // FMMC_RSTAR_MCP
    UNKNOWN // everything else
};

enum class eAnimationBitset
{
    kCashRainActive       = 12,
    kChampagneSprayActive = 13
};

enum class eBlipFlags
{
    kVisibleOnCutscene = 1,
    kFlashMinimapDisplay = 2,
    kSkipTutorialSessionChecks = 5,
    kHideOnMinimap = 6, // needs testing
    kHideOnMinimapWhenInterior = 6, // needs testing
    kHideOnMinimapWhenBigMapActive = 9, // needs testing
    kDontUsePassiveBlip = 21,
    kUseRampageBlip = 24,
    kHideWhenFading = 25
};

enum class ePlayerStateFlags
{
    kScreenFadingOut = 0,
    kScreenFadedOut = 1,
    kCinematicNewsChannelActive = 2,
    kPlayerSwitchState1 = 5,
    kPlayerSwitchState2 = 6,
    kPlayerSwitchState3 = 7,
    kPlayerSwitchState4 = 8,
    kModshopActive = 9,
    kModshopExitingVehicle = 10,
    kPlayerInSCTV = 31
};

enum class eActivityFlags
{
    kWatchingMovie = 0,
    kInGangAttack = 1,
    kImpromptuRace = 2,
    kCrateDrop = 4, // tf is this? "~s~A plane is on its way to drop a Crate ~HUD_COLOUR_GREEN~~BLIP_CRATEDROP~ ~s~which contains useful equipment. Be the first to collect it."
    kDeliveringSimeonVehicle = 6,
    kInLapDance = 7,
    kHoldUpTutorial = 8,
    kJoyrider = 9, // uh what is this?
    kCarModTutorial = 10,
    kMissionLauncher = 11, // ???
    kLesterCutsceneActive = 12,
    kTrevorCutsceneActive = 13,
    kHeistIntro = 14,
    kPlaneTakedown = 15, // not sure what this is
    kDistractCops = 16, // "Great. Thank you for your help. Now some horrible criminals are in jail for a crime they did commit and it's all your fault!!" ???
    kDestroyVehicle = 17, // ???
    kPartakingInHotTarget = 18,
    kPartakingInKillList = 19,
    kTimeTrialStarted = 21,
    kPartakingInCheckpoints = 22,
    kPartakingInChallenge = 23,
    kPennedInActive = 24,
    kRCTimeTrialStarted = 25,
    kPartakingInHotProperty = 27,
    kPartakingInKingOfTheCastle = 29,
    kPartakingInCriminalDamage = 30,
    kLowriderIntro = 31
};

enum class eGamerTagFlags
{
    kShowPackageCount = 13,
    kFadeOutGamerTag = 17,
    kGangCEO = 19,
    kGangBiker = 20
}; // TODO!

enum class eOrbitalBitset
{
    kOrbitalCannonActive = 0,
    kWatchingMovie = 1, // not a typo, the orbital cannon script needs to know if you are inside a movie theater for some strange reason
    kCutsceneOrInterior = 2,
    kTransactionPending = 3
};

enum class eArcadeGameBitset
{
    kArcadeMachineActivated = 0,
    kLoveMeterActivated = 1,
    kLoveMeterAnimationGenderDecided = 2
};

enum class eOutOfSightFlags
{
    kOutOfSightEnabled = 0,
    kOutOfSightActive = 1, // this controls whether you appear on radar or not
    kHelpDisplayed = 2,
    kDamagedPlayerOutsideOrganization = 3
};

struct JobStats
{
    SCR_INT Wins;
    SCR_INT Losses;
    SCR_INT Kills;
    SCR_INT Deaths;
    SCR_INT PAD_0004; // unused
};

struct JobBet
{
    SCR_INT PAD_0000; // TODO
    SCR_INT Amount;
};

struct MissionBets
{
    SCR_INT                       Identifier; // a random integer between 100 and 10000000
    JobStats                      Stats;
    SCR_ARRAY<JobBet, 32>         PlacedBets;
    SCR_BOOL                      CancelBetting;
};
static_assert(sizeof(MissionBets) == 72 * 8);

struct PlayerBlip
{
    SCR_INT                       PAD_0000;
    SCR_INT                       NumPassengersInVehicle;
    SCR_BITSET<eBlipFlags>        BlipFlags;
    SCR_INT                       PlayerVehicleBlipType; // can be used to spoof your blip as a tank, oppressor etc
    SCR_INT                       IdleDurationUntilBlipIsVisible;
    SCR_INT                       BlipVisibleDuration;
    SCR_INT                       MissionInteriorIndex; // can be used to spoof blip position
    SCR_VEC3                      MissionInteriorBlipLocation;
    SCR_FLOAT                     MissionInteriorBlipRotation;
    SCR_BOOL                      UnknownOverride; // can also be used to spoof position
    SCR_VEC3                      UnknownOverridePosition;
};
static_assert(sizeof(PlayerBlip) == 15 * 8);

struct YachtAppearance
{
    SCR_INT                       PAD_0000; // TODO
    SCR_INT                       PAD_0001;
    SCR_INT                       PAD_0002;
    SCR_INT                       PAD_0003;
    SCR_INT                       PAD_0004;
    TEXT_LABEL_63                 Name;
    SCR_HASH                      NameHash;
};
static_assert(sizeof(YachtAppearance) == 22 * 8);

struct YachtData
{
    SCR_BOOL                      HasYacht;
    SCR_VEC3                      Position;
    SCR_INT                       TravelStage;
    SCR_BOOL                      TravelInProgress;
    SCR_ARRAY<uint64_t, 7>        VehicleNetIds; // the heli and the boats that spawn near the yacht
    SCR_INT                       YachtIndexPlayerIsIn; // owned or unowned
    SCR_INT                       UnkYachtIndex; // TODO
    SCR_INT                       YachtIndexPlayerIsInCouldBeDriving;
    SCR_ARRAY<uint64_t, 2>        NearbyYachts;
    SCR_INT                       ClosestYachtIndex;
    SCR_INT                       TurbulenceState; // controls random camera shakes when on a yacht
    SCR_INT                       DefenseSetting;
    YachtAppearance               Appearance;
    SCR_BOOL                      RemoveClothingWhileInHotTub;
    SCR_HASH                      MissionYachtOwnerHandleHash; // always -1 or NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID())
    SCR_BOOL                      SpawnAccess; // "spawn access"?
    SCR_INT                       MissionYachtIndex;
};
static_assert(sizeof(YachtData) == 49 * 8);

struct SimpleInteriorData
{
    SCR_INT                       Flags; // TODO!!!
    SCR_INT                       Flags2;
    SCR_INT                       Flags3;
    SCR_INT                       Flags4;
    SCR_INT                       Flags5;
    SCR_INT                       Flags6;
    SCR_INT                       Flags7;
    SCR_INT                       SimpleInteriorIndex;
    SCR_INT                       InstanceId;
    SCR_INT                       AllowedGoons;
    PLAYER_INDEX                  Owner;
    PLAYER_INDEX                  VehicleOwner;
    SCR_VEC3                      SpecialVehicleSpawnPosition;
    SCR_FLOAT                     SpecialVehicleSpawnHeading;
    SCR_INT                       EnteringSimpleInteriorIndex;
    SCR_INT                       SpecialVehicleSimpleInteriorIndex; // MOC, Terrorbyte etc
    SCR_INT                       UnkSimpleInteriorIndex;
    SCR_INT                       UnkSimpleInteriorIndex2;
    SCR_VEC3                      AvengerPosition;
    SCR_VEC3                      AvengerPosition2; // not sure how this is different from the field above
    SCR_FLOAT                     AvengerHeading;
    SCR_INT                       MissionSpawnSimpleInteriorIndex;
    SCR_INT                       InteriorSubtype; // nightclub vs nightclub garage etc
};
static_assert(sizeof(SimpleInteriorData) == 29 * 8);

// yes there's a struct for leaving your clubhouse
struct LeaveClubhouse
{
    SCR_BOOL                      Active;
    SCR_BOOL                      Active2;
    SCR_INT                       Identifier;
    SCR_INT                       ExitLocation;
    SCR_ARRAY<uint64_t, 32>       ParticipantHashes;
};
static_assert(sizeof(LeaveClubhouse) == 37 * 8);

struct ArcadeGame
{
    SCR_BITSET<eArcadeGameBitset> Bits;
    SCR_INT                       CabinetIndex;
    SCR_INT                       PAD_0002; // The only valid value is 0 so idk
    SCR_INT                       CabinetGame; // TODO
    SCR_INT                       GameStage;
};
static_assert(sizeof(ArcadeGame) == 5 * 8);

struct GlobalPlayerBDEntry
{
    alignas(8) eFreemodeState     FreemodeState;
    uint64_t                      PAD_0001[32]; // TODO
    SCR_INT                       PlayersVisible;
    SCR_INT                       PlayersTracked;
    SCR_BITSET<eAnimationBitset>  AnimationBitset;
    SCR_INT                       NumSuccessfulHoldups; // resets every 12 minutes
    SCR_INT                       PAD_0037;
    SCR_INT                       PersonalVehicleNetId;
    SCR_INT                       UnkVehicleNetId;
    SCR_INT                       UnkVehicleNetId2;
    SCR_ARRAY<uint64_t, 2>        UnkVehicleNetIds;
    SCR_INT                       DeliveryMechanicNetId;
    SCR_INT                       DeliveryMechanicNetId2;
    SCR_INT                       SpawningVehicleLiveryIndex;
    SCR_INT                       SpawningVehiclePrimaryColor;
    SCR_INT                       SpawningVehicleSecondaryColor;
    SCR_INT                       AvengerNetId;
    SCR_INT                       DeliveryMechanicNetId3; // wtf is this?
    SCR_INT                       TerrorbyteNetId; // or is it the MOC?
    SCR_INT                       SubmarineNetId;
    SCR_INT                       DinghyNetId;
    SCR_INT                       DeliveryMechanicNetId4; // another one...
    SCR_INT                       AcidLabNetId;
    SCR_INT                       DeliveryBikeNetId; // this is a guess, verify
    SCR_BOOL                      PAD_0057;
    uint64_t                      PAD_0058[15]; // confirmed these are not used by PC scripts
    PlayerBlip                    PlayerBlip;
    SCR_BOOL                      NeedToPopulateSessionStartTime; // the session start time is unused
    uint64_t                      PAD_0089[32]; // TODO
    alignas(8) eMissionType       MissionType;
    SCR_BOOL                      SpawningVehicle;
    uint64_t                      PAD_0123[3]; // confirmed these are not used by PC scripts
    MissionBets                   MissionBets;
    SCR_BOOL                      RadarBlipVisibliltyMechanicEnabled;
    SCR_BITSET<ePlayerStateFlags> PlayerStateFlags;
    SCR_INT                       PlayerStateFlags2; // TODO
    SCR_INT                       PlayerStateFlags3; // TODO
    SCR_INT                       CarMeetModShopSlotPreTakeover;
    PLAYER_INDEX                  CurrentCarMeetSlotOwnerIndex; // can be player or player's CEO/MC leader
    SCR_INT                       CarMeetModShopSlotPostTakeover;
    SCR_HASH                      CarMeetModdingVehicleModel;
    PLAYER_INDEX                  CarMeetCurrentlySeatedVehicleOwner;
    SCR_VEC3                      PlayerPosition; // updates every two seconds, used by spectate
    SCR_BOOL                      OffRadarActive;
    SCR_BOOL                      PassengerOfVehicleWithOffRadarDriver;
    SCR_BOOL                      GoonOfBossWithOffRadar;
    SCR_BOOL                      RevealPlayersActive;
    PLAYER_INDEX                  RemoteWantedLevelPlayer; // cut content but still works
    SCR_INT                       RemoteWantedLevelAmount;
    PLAYER_INDEX                  RemoteWantedLevelRemovePlayer; // doesn't work at all
    SCR_INT                       UnkTeleportStage;
    SCR_BITSET<eActivityFlags>    ActivityFlags;
    SCR_INT                       NumReservedMissionPeds;
    SCR_INT                       NumReservedMissionVehicles;
    SCR_INT                       NumReservedMissionObjects;
    SCR_INT                       TransitionSessionState; // TODO reverse enum
    SCR_VEC3                      TransitionReturningPosition; // TODO
    TEXT_LABEL_23                 TransitionContentIDToLaunch;
    SCR_INT                       RespawnState;
    SCR_INT                       LastRespawnTime;
    SCR_BOOL                      CollisionLoaded;
    SCR_BOOL                      CommitingSuicide;
    SCR_BOOL                      RespawningInVehicleAsDriver;
    SCR_BOOL                      RespawningInVehicle;
    SCR_BOOL                      PAD_0238; // this value is set but not read at all by any PC scripts
    SCR_BITSET<eGamerTagFlags>    GamerTagFlags;
    SCR_BOOL                      IsMale;
    SCR_INT                       ArmwrestlingLocationFlags;
    SCR_INT                       PAD_0242; // TODO
    SCR_BOOL                      GamerTagShowArrow;
    SCR_BOOL                      CarWashInProgress;
    INTERIOR_INDEX                CurrentInteriorIndex;
    SCR_INT                       PAD_0246; // TODO
    SCR_INT                       CurrentStoreIndex; // the stores in the map which can be held up
    SCR_BOOL                      ShopActive; // any shop
    SCR_BOOL                      InTaxi;
    SCR_INT                       Haircut;
    SCR_INT                       PrimaryHairColor;
    SCR_INT                       SecondaryHairColor;
    SCR_INT                       FriendlyPlayers; // bitset of player team relgroups that obtain a Respect relationship with player
    SCR_BOOL                      KilledByPlayer; // verify
    SCR_BOOL                      InImpromptuDeathmatch;
    SCR_VEC3                      ImpromptuDeatmatchStartPosition;
    SCR_INT                       PAD_0569; // not read by scripts, impromptu DM related
    SCR_INT                       MissionLoseAnimType;
    SCR_INT                       MissionWinAnimType; // verify
    SCR_INT                       MissionCrewAnimType;
    SCR_INT                       RallyRaceAnim;
    SCR_BOOL                      IsRallyRace;
    SCR_BOOL                      JustGetsPulledOutWhenElectrocuted;
    SCR_INT                       HeistCutSelectionStage; // the only valid values seem to be 6 and 7
    SCR_BOOL                      IsBadsport;
    SCR_FLOAT                     MentalState;
    SCR_BOOL                      IsRockstarDev; // dev dlc check and not the CNetGamePlayer flag so can be used to detect YimMenu
    SCR_BOOL                      ScreenFadedOut;
    SCR_BOOL                      TimeTrialActive;
    YachtData                     YachtData;
    SimpleInteriorData            SimpleInteriorData;
    SCR_BOOL                      PAD_0350; // TODO
    SCR_INT                       PAD_0351; // unused vehicle/interior stuff
    SCR_BOOL                      ShowMOCBlip;
    SCR_BOOL                      ShowAvengerBlip;
    SCR_BOOL                      ShowTerrorbyteBlip;
    SCR_BOOL                      ShowSubmarineBlip;
    SCR_BOOL                      ShowDinghyBlip;
    SCR_BOOL                      ShowDeliveryBikeBlip;
    SCR_BOOL                      ShowAcidLabBlip;
    LeaveClubhouse                LeaveClubhouse;
    SCR_INT                       Friends; // bitset of players that are friends
    SCR_VEC3                      InteriorVehiclePosition; // for terrorbyte and MOC, used to fake player blip position on map
    SCR_FLOAT                     InteriorVehicleHeading;
    SCR_VEC3                      AcidLabPosition; // not read by the scripts
    SCR_FLOAT                     AcidLabHeading;
    SCR_INT                       VehicleTurretsActive; // bitset
    SCR_ARRAY<SCR_VEC3, 3>        VehicleTurretsCameraPosition;
    SCR_INT                       PAD_0416; // TODO
    SCR_BOOL                      DozerDetected; // very shady stuff, anticheat?
    SCR_ARRAY<uint64_t, 6>        MissionTurretParticipants;
    SCR_INT                       PAD_0425; // some seat index
    SCR_INT                       MissionTurretSlot;
    SCR_BITSET<eOrbitalBitset>    OrbitalBitset;
    SCR_BOOL                      FacilityIntroCutsceneInProgress;
    SCR_BOOL                      FacilityIntroCutsceneStarted; // like above but is enabled 2 stages earlier
    SCR_BOOL                      PAD_0430; // todo
    SCR_BOOL                      BeingSolicitedByProstitute; // why tf is this used by the orbital cannon?
    SCR_VEC3                      DronePosition; // updates every second
    SCR_FLOAT                     DroneHeading;
    SCR_INT                       OrbitalBitset2; // ugh
    SCR_INT                       CurrentlyUsingArenaTrapIndex;
    SCR_INT                       CurrentlyUsingArenaTrapActivatedTime;
    ArcadeGame                    ArcadeGame;
    SCR_INT                       DancePartner;
    SCR_INT                       PAD_0445;
    SCR_INT                       BeachPartyFlags;
    uint64_t                      PAD_0477[10]; // I don't think we'll ever be able to figure out what this does
    SCR_INT                       ThreeCardPokerStyle;
    SCR_INT                       BlackjackStyle;
    SCR_BITSET<eOutOfSightFlags>  OutOfSightFlags;
    SCR_VEC3                      OutOfSightArea;
    SCR_INT                       AmmunationWeaponPartFlags;
    PLAYER_INDEX                  LastKilledBy;
    SCR_BOOL                      CanSpawnGunVan;
};
static_assert(sizeof(GlobalPlayerBDEntry) == 466 * 8);

struct GlobalPlayerBD
{
    SCR_ARRAY<GlobalPlayerBDEntry, 32> Entries;
};
static_assert(sizeof(GlobalPlayerBD) == 14913 * 8);

struct GPBD_KickingEntry
{
    SCR_ARRAY<uint64_t, 32> KickVotes; // players you are voting to kick (array of bool)
    SCR_ARRAY<uint64_t, 32> KickWarningsShown;
    SCR_BOOL                WillBeKickedSoon;
    SCR_ARRAY<uint64_t, 32> VoteKickBlockDetected;
};
static_assert(sizeof(GPBD_KickingEntry) == 100 * 8);

struct GPBD_Kicking
{
    SCR_ARRAY<GPBD_KickingEntry, 32> Entries;
};
static_assert(sizeof(GPBD_Kicking) == 3201 * 8);

enum class eBossGoonFlags
{
    kOneOnOneDM = 4,
    kJoinSuccess = 7,
    kJoinFail = 8,
    kSpectating = 24
};

enum class eGoonInviteType
{
    DEBUG,
    NEARBY,
    FRIENDS,
    CREW,
    INDIVIDUAL,
    LOOKING_FOR_WORK
};

enum class eBossVehicleState
{
    NONE,
    SPAWNED,
    DESTROYED = 3
};

enum class eMCRole
{
    PROSPECT = -1,
    VICE_PRESIDENT,
    ROAD_CAPTAIN,
    SERGEANT_IN_ARMS,
    ENFORCER
};

enum class eClubhouseActivity
{
    NONE = -1,
    DARTS,
    ARM_WRESTLING
};

struct MPScriptData
{
    SCR_INT  Index; // this is an enum
    uint64_t Args[15];
    SCR_INT  InstanceId;
    uint64_t MoreArgs[4];
};
static_assert(sizeof(MPScriptData) == 21 * 8);

// this is named stopwatch in the decompiler but "timer" is probably a better name for it
struct Timer
{
    SCR_INT  Time;
    SCR_BOOL IsInitialized;
};
static_assert(sizeof(Timer) == 2 * 8);

struct MCStyle
{
    SCR_BOOL                      Enabled;
    SCR_INT                       BossOutfitType;
    SCR_INT                       GoonOutfitType;
    SCR_ARRAY<uint64_t, 7>        GoonOutfitIndices; // one outfit for each goon, size is 7 instead of 8 for some reason
    SCR_ARRAY<uint64_t, 7>        GoonOutfitIndicesOverride;
    SCR_INT                       PAD_0019;
    SCR_BOOL                      HeadgearEnabled;
    SCR_BOOL                      EmblemEnabled;
};
static_assert(sizeof(MCStyle) == 22 * 8);

struct VehicleExport
{
    SCR_ARRAY<uint64_t, 4>        SellingVehicleIndices;
    SCR_INT                       PAD_0005; // this is set to zero in all export scripts and never read
};
static_assert(sizeof(VehicleExport) == 6 * 8);

struct HangarCargo
{
    SCR_INT                       PAD_0000; // unused?
    SCR_ARRAY<uint64_t, 20>       DeliverableTypes;
    SCR_INT                       CargoType;
};
static_assert(sizeof(HangarCargo) == 23 * 8);

struct CasinoHeistPrep
{
    SCR_INT                       PrepIndex;
    SCR_INT                       SupportCrewMemberIndex; // only set on preps 1 through 3
    SCR_INT                       LoadoutIndex; // only set on prep 1 and 2
};
static_assert(sizeof(CasinoHeistPrep) == 3 * 8);

struct LeaveInHeli
{
    SCR_INT                       Flags;
    PLAYER_INDEX                  Owner;
    SCR_INT                       SeatIndex;
};
static_assert(sizeof(LeaveInHeli) == 3 * 8);

struct BossGoon
{
    PLAYER_INDEX                  Boss; // leader of CEO/MC
    SCR_INT                       TimeBecameBoss;
    SCR_INT                       TimeBecameGoon;
    SCR_INT                       LastPayTime;
    SCR_BITSET<eBossGoonFlags>    Flags;
    SCR_INT                       Flags2; // TODO
    SCR_INT                       Flags3; // TODO
    SCR_INT                       TotalBossGoonTime;
    SCR_ARRAY<uint64_t, 2>        BossGoonUUID;
    SCR_ARRAY<uint64_t, 8>        Goons;
    SCR_INT                       GoonsRequestingJoin; // bitset
    SCR_INT                       PayGrade;
    SCR_INT                       InvitesByBosses; // bitset
    SCR_INT                       TransitionBossPersistanceStage;
    SCR_INT                       EndBeingGoonReason;
    SCR_INT                       PAD_0025; // TODO
    PLAYER_INDEX                  JoiningBoss;
    alignas(8) eGoonInviteType    JoinedInviteType;
    SCR_INT                       NumBossDeathsSinceLastPay;
    SCR_VEC3                      PAD_0029; // TODO
    alignas(8) big::eActivityType UnkActivity;
    alignas(8) big::eActivityType CurrentActivity;
    PLAYER_INDEX                  JoustTarget;
    PLAYER_INDEX                  ExecutiveDeathmatchTarget;
    MPScriptData                  ActiveScript;
    PLAYER_INDEX                  PAD_0057;
    PLAYER_INDEX                  PAD_0058;
    alignas(8) eBossVehicleState  BossVehicleState;
    SCR_INT                       BossVehicleSpawnState;
    PLAYER_INDEX                  PlayerInsideBossVehicle;
    SCR_HASH                      BossVehicleModel;
    Timer                         LastBossVehicleSpawnTimer;
    Timer                         BossVehicleInvincibleTimer;
    SCR_VEC3                      BossVehicleSpawnedPosition;
    alignas(8) HudColor           BossVehicleHudColor;
    TEXT_LABEL_15                 BossVehicleTextLabel;
    SCR_INT                       BossVehicleNetId;
    MCStyle                       MCStyle;
    uint64_t                      PAD_0098[3]; // unused
    SCR_INT                       FriendlyFireDisabledPlayers;
    SCR_INT                       PiracyPreventionYachtIndex; // not used by the scripts
    SCR_INT                       BossGoonMissionLaunchState;
    SCR_INT                       ColorSlot;
    TEXT_LABEL_63                 MCName;
    SCR_INT                       Language; // can be used to get the system language of player
    SCR_INT                       SpawnableBossVehicles;
    SCR_INT                       AutoBuyoutDeliveryLocationIndex;
    SCR_INT                       AutoBuyoutDeliveryLocationSubIndex;
    SCR_INT                       PAD_0125; // unused
    SCR_ARRAY<SCR_VEC3, 8>        PAD_0126; // TODO
    SCR_ARRAY<SCR_VEC3, 8>        ContrabandPositions; // positions of cargo used to notify players to destroy them when they get near
    SCR_HASH                      ContrabandPickupModel;
    PLAYER_INDEX                  StealingContrabandVehiclePlayerIndex;
    SCR_INT                       PAD_0178; // TODO
    SCR_HASH                      ContrabandPickupModel2;
    SCR_BOOL                      DestroyedCargo;
    SCR_INT                       VIPGameplayDisabledTimer;
    SCR_INT                       SettingUpBusiness;
    uint64_t                      PAD_0183[4]; // TODO some unknown contraband struct
    VehicleExport                 VehicleExport;
    uint64_t                      PAD_0193[12]; // TODO
    SCR_ARRAY<uint64_t, 6>        ActiveFreemodeEvents; // force thunder
    uint64_t                      PAD_0212[22]; // I'm not even going to bother with this one
    HangarCargo                   HangarCargo;
    uint64_t                      PAD_0236[23]; // not going to bother with this one either
    SCR_ARRAY<uint64_t, 20>       CasinoDeliverables;
    SCR_INT                       CasinoLimoDestination;
    SCR_BOOL                      CasinoLimoActive;
    SCR_BOOL                      CasinoLuxuryCarActive;
    SCR_HASH                      CasinoLuxuryCarModel;
    CasinoHeistPrep               CasinoHeistPrep;
    SCR_INT                       CayoPrepIndex;
    SCR_INT                       CompanySUVDestination;
    SCR_BOOL                      CompanySUVActive;
    SCR_ARRAY<uint64_t, 8>        ContrabandIndices; // type of selling cargo
    SCR_ARRAY<uint64_t, 10>       VehicleExportIndices; // not sure what this is
    SCR_INT                       VehicleExportMissionType; // valid range is 2000 to 2010, 2000 = 0, 2001 = 1 etc
    SCR_ARRAY<uint64_t, 4>        VehicleExportSellingIndices;
    SCR_BOOL                      PAD_0337; // TODO
    TEXT_LABEL_63                 GangName; // CEO Name
    TEXT_LABEL_63                 ClubhouseName; // cut content?
    SCR_INT                       SourcingContrabandType;
    SCR_INT                       FragileGoodsMissionType;
    SCR_INT                       SalvageMissionType;
    SCR_INT                       DoomsdayPrepIndex;
    SCR_INT                       VehicleExportIndex; // another one...
    SCR_INT                       PAD_0375; // unused
    SCR_INT                       BunkerSourceIndex; // check gb_gunrunning func_1540
    SCR_ARRAY<uint64_t, 8>        BunkerCargoIndices;
    uint64_t                      PAD_0386[5];
    uint64_t                      PAD_0391[2]; // unused
    uint64_t                      PAD_0393[15]; // smuggler data
    SCR_INT                       LastBossWorkTime; // seconds since epoch
    uint64_t                      PAD_0409[19];
    SCR_BOOL                      IsMC;
    alignas(8) eMCRole            MCRole; // applies to goons only, boss is always the MC president
    SCR_BOOL                      FormationFlyingAssist;
    SCR_INT                       PAD_0431; // always set to zero and not read
    SCR_BOOL                      MCFormationActive;
    SCR_BOOL                      MCFormationHelpShown;
    Timer                         MCFormationHealthBonusTimer;
    Timer                         MCFormationLastHealthBonusTimer;
    Timer                         MCFormationBreakTimer;
    SCR_INT                       PAD_0440; // unused
    SCR_BOOL                      MCFormationAssist;
    SCR_BOOL                      MCRidingStyleRelaxed;        
    SCR_FLOAT                     PAD_0443; // set from a tunable
    SCR_FLOAT                     PAD_0444; // set from a tunable
    uint64_t                      PAD_0445[16]; // somewhat unused, a few fields are accessed in the business battle script
    SCR_INT                       ClothingValue; // total value of equipped clothing used by criminal damage
    PLAYER_INDEX                  Adversary; // for common adversary calculations?
    SCR_HASH                      ContrabandType; // unknown HASH_ENUM
    SCR_INT                       HitAndRideGangType;
    SCR_BOOL                      IsMC2;
    SCR_INT                       BossGoonVersion;
    SCR_INT                       MCTotalContributionPoints;
    SCR_INT                       MCContributionPoints;
    SCR_INT                       FavoriteBikeStyle; // not read by the scripts
    SCR_INT                       GreatestFormationTimeIndex;
    SCR_INT                       FormationTime;
    SCR_BOOL                      RidingFavoriteMotorcycle;
    SCR_INT                       ContrabandSellLocation;
    SCR_INT                       BusinessBattleType;
    SCR_INT                       PAD_0475;
    SCR_INT                       NightclubMissionIndex;
    SCR_INT                       NightclubDefendMissionIndex;
    uint64_t                      PAD_0478[18]; // TODO
    SCR_BOOL                      DoubleActionCacheLocationRevealed;
};
static_assert(sizeof(BossGoon) == 497 * 8);

struct MCStats
{
    SCR_INT                       FormationTime0;
    SCR_INT                       FormationTime1;
    SCR_INT                       FormationTime2;
    SCR_INT                       FormationTime3;
    SCR_INT                       MembersMarkedForDeath;
    SCR_INT                       MCKills;
    SCR_INT                       MCDeaths;
    SCR_INT                       RivalPresidentKills;
    SCR_INT                       RivalCEOAndVIPKills;
    SCR_INT                       MeleeKills;
    SCR_INT                       ClubhouseContractsComplete;
    SCR_INT                       ClubhouseContractEarnings;
    SCR_INT                       ClubworkCompleted;
    SCR_INT                       ClubChallengesCompleted;
    SCR_INT                       MemberChallengesCompleted;
};
static_assert(sizeof(MCStats) == 15 * 8);


struct GBPD_FM_3_Entry
{
    alignas(8) big::eActivityType CurrentActivity; // enum is outdated
    SCR_INT                       Flags; // TODO
    alignas(8) big::eActivityType CurrentFreemodeActivity; // subset of CurrentActivity
    SCR_INT                       SeatingFlags;
    SCR_VEC3                      CurrentFreemodeActivityObjectivePosition;
    SCR_INT                       VehiclesNearbyActivityObjective; // only used by challenges and checkpoints
    SCR_BOOL                      PassiveMode;
    SCR_BOOL                      TimeTrialActive; // verify
    BossGoon                      BossGoon;
    uint64_t                      PAD_507[3]; // unused
    SCR_INT                       ScriptEventReplayProtectionCounter;
    Timer                         CoronaForcedLaunchTimer;
    LeaveInHeli                   LeaveInHeli;
    SCR_INT                       OfficeDesktopFlags; // bit 0 -> login, bit 1 -> map
    uint64_t                      PAD_514[8]; // some IE stuff, most of it is unused
    SCR_INT                       IlluminatedClothingState; 
    SCR_INT                       MatchHistoryId1; // used for telemetry
    SCR_INT                       MatchHistoryId2;
    alignas(8) eClubhouseActivity ClubhouseActivity;
    SCR_INT                       ClubhouseFont;
    SCR_INT                       ClubhouseColor;
    SCR_INT                       ClubhouseEmblem;
    SCR_BOOL                      ClubhouseHideSignage;
    uint64_t                      PAD_0533[2]; // facility exit
    uint64_t                      PAD_0535[6]; // no clue what this is
    MCStats                       MCStats;
    uint64_t                      PAD_0556[29];
    SCR_HASH                      ForcedWeapon;
    SCR_INT                       HangarCargoMissionLocationIndex;
    SCR_VEC3                      AvengerPosition;
    SCR_VEC3                      TerrorbytePosition;
    SCR_VEC3                      AcidLabPosition;
    PLAYER_INDEX                  DeliveringExportVehicleOwner;
    uint64_t                      PAD_0597[2]; // TODO
    SCR_INT                       BountyAmount; // values above 10000 will prevent payout
    PLAYER_INDEX                  BountyPlacedBy;
    SCR_INT                       PAD_0601; // unused, set to -1 by business_battles_sell and never read
    SCR_INT                       CurrentlyUsingArenaTurretIndex; // works similar to the vars found in GlobalPlayerBD
    SCR_INT                       CurrentlyUsingArenaTurretActivatedTime;
    SCR_INT                       CasinoStoryProgress;
    SCR_INT                       CasinoFlowProgress;
    SCR_ARRAY<uint64_t, 1>        DailyObjectiveFlags;
};
static_assert(sizeof(GBPD_FM_3_Entry) == 608 * 8);

struct GPBD_FM_3
{
    SCR_ARRAY<GBPD_FM_3_Entry, 32> Entries;
};
static_assert(sizeof(GPBD_FM_3) == 19457 * 8);

enum class eMissionDataFlags
{
    kMissionLaunched = 0,
    kJobDownloaded = 2,
    kStartingJob = 3,
    kRequestingScript = 4,
    kLaunchedScript = 6, // should be set if kMissionLaunched is set
    kAutoStartOnProximity = 7, // used by gang attack
    kNJVSQuickMatch = 8,
    kVoteLiked = 10,
    kVoteDisliked = 11,
    kNoVote = 25
}; // TODO

enum class eTutorialBitset
{
    kInTutorialRace = 0,
    kTutorialRaceActive = 2,
    kShowCredits = 4,
    kNeedFreeVehicle = 6
};

enum class eGangCallServices
{
    kMugger = 0,
    kMercenary = 1
};

enum class eVehicleSelectionState
{
    NONE,
    SELECTING,
    SELECTED
};

enum class eStatState
{
    NONE,
    LETHARGIC,
    OUT_OF_SHAPE,
    HEALTHY,
    ATHLETE,
    TRI_ATHLETE,
    UNTRAINED,
    SPRAY_AND_PRAY,
    POLICE_TRAINING,
    MILITARY_TRAINING,
    DEAD_EYE,
    FRAGILE,
    WEAK,
    AVERAGE,
    TOUGH,
    BODYBUILDER,
    CLUMSY,
    LOUD,
    SNEAKY,
    HUNTER,
    NINJA,
    DANGEROUS,
    RC_PILOT,
    COMMERCIAL_PILOT,
    FIGHTER_PILOT,
    ACE,
    UNLICENSED,
    SUNDAY_DRIVER,
    COMMUTER,
    STREET_RACER,
    PRO_RACER,
    NORMAL,
    UNSTABLE,
    DERANGED,
    MANIAC, 
    PSYCHOPATH,
    DRUNK
};

enum class ePropertyInteriorFlags
{
    kOwnerOfInterior = 0,
    kVisitorOfInterior = 1, // mutually exclusive with above flag
    kConcealWhenDead = 12,
    kRenovatingProperty = 19,
    kPreviewingDecor = 20,
    kRenovatingClubhouse = 21,
    kUsingYachtRmBath1 = 22,
    kUsingYachtRmBath3 = 23,
    kUsingYachtRmWeeBathroom = 25,
    kGunLockerOpen = 27,
    kOfficeSafeOpen = 28,
    kOfficeAssistantMale = 29
};

enum class eInteriorStyleFlags
{
    kGunLockerShowPumpShotgun = 0,
    kGunLockerShowMicroSMG = 1,
    kGunLockerShowC4 = 2, // proximity or sticky
    kGunLockerShowGrenade = 3,
    kGunLockerShowCombatMG = 4,
    kGunLockerShowMarksmanRifle = 5,
    kPurchasedSnacks = 6,
    kPurchasedInteriorRenovations = 7,
    kForceOfficeAssistantSpawn = 8,
    kAssistantAnimationOver = 9,
    kChangeInteriorDecorOfficeHelpShown = 11,
    kChangeInteriorDecorApartmentHelpShown = 12,
    kOwnsOfficeBedroom = 13,
    kOwnsClubhouseBikeShop = 16,
    kOwnsOfficeGunLocker = 17,
    KOwnsClubhouseWalls = 18, // ???
    kOwnsClubhouseFurnishings = 19,
    kOwnsClubhouseDecors = 20
};

struct PlaylistData
{
    PLAYER_INDEX           Host;
    SCR_INT                Flags;
    SCR_BOOL               PAD_0002;
    SCR_INT                CurrentMission;
    SCR_INT                TotalMissions;
    PLAYER_INDEX           PAD_0006;
};
static_assert(sizeof(PlaylistData) == 6 * 8);

struct MissionData
{
    SCR_INT                           PAD_0000; // unused
    SCR_INT                           ScriptId; // TODO: add enum
    SCR_INT                           InstanceId;
    uint64_t                          PAD_0003[7]; // unused
    SCR_VEC3                          TriggerPosition;
    uint64_t                          PAD_0013[3]; // unused
    SCR_INT                           InstanceIdForPresence;
    SCR_INT                           PAD_0017; // unused
    SCR_BITSET<eMissionDataFlags>     Flags;
};
static_assert(sizeof(MissionData) == 19 * 8);

// local copy can be found at Global_2680247
struct JobSettings
{
    SCR_ARRAY<uint64_t, 31>           Settings; // indices vary based on job type. take a look at func_8988 in fmmc_launcher if you wish to change them
    SCR_INT                           NumPlayers; // verify
    SCR_INT                           PAD_0033;
    SCR_INT                           SpawnSimpleInteriorIndex;
    SCR_INT                           PAD_0035; // unused
    SCR_BOOL                          MatchmakingOpen;
    SCR_INT                           ContentHash;
};
static_assert(sizeof(JobSettings) == 38 * 8);

struct VehicleSelection
{
    SCR_BOOL                          Active;
    SCR_BOOL                          Active2;
    PLAYER_INDEX                      PAD_0002; // set to host by fmmc but not read at all
    SCR_HASH                          VehicleModel;
    SCR_INT                           CreatorIndex; 
    alignas(8) eVehicleSelectionState State;
    SCR_INT                           PrimaryColor;
    Color3                            CustomPrimaryColor;
    Color3                            CustomSecondaryColor;
    PLAYER_INDEX                      Partner; // for rally races?
    GAMER_HANDLE                      PartnerHandle;
    SCR_INT                           PreferredRole; // target assault races
    SCR_INT                           PAD_0028; // TODO
    SCR_INT                           ControlType; // 1 = kb&m 2 = controller
    SCR_INT                           BettingFlags;
    SCR_INT                           Team;
    SCR_INT                           Flags;
    SCR_INT                           JoinedMembers; // bitset of joined transition members set by the host
    SCR_INT                           AdversaryOutfitIndex;
    alignas(8) eStatState             StatState; // see func_9142 in fmmc_launcher, shown to other players
    SCR_INT                           CashWager; // shown to other players...
    uint64_t                          PAD_0037[2]; // TODO
    SCR_INT                           PAD_0039; // TODO random integer between 1 and 11
};
static_assert(sizeof(VehicleSelection) == 40 * 8);

struct StrikeTeam
{
    PLAYER_INDEX                      Target;
    Timer                             Cooldown;
    SCR_BOOL                          CancelStrikeTeam; // read but not written to
    SCR_INT                           Level;
};
static_assert(sizeof(StrikeTeam) == 5 * 8);

struct PlayerStats
{
    SCR_INT                           Team;
    SCR_INT                           RP;
    SCR_INT                           CrewRP;
    SCR_INT                           WalletBalance;
    SCR_INT                           HeistBonus;
    SCR_INT                           GlobalRP;
    SCR_INT                           Rank;
    TEXT_LABEL_31                     CrewTitle;
    SCR_INT                           TotalRacesWon;
    SCR_INT                           TotalRacesLost;
    SCR_INT                           TimesFinishRaceAsTop3;
    SCR_INT                           TimesFinishRaceLast;
    SCR_INT                           TimesRaceBestLap;
    SCR_INT                           TotalDeathmatchesWon;
    SCR_INT                           TotalDeathmatchesLost;
    SCR_INT                           TotalTeamDeathmatchesWon;
    SCR_INT                           TotalTeamDeathmatchesLost;
    SCR_INT                           Shots;
    SCR_INT                           Hits;
    SCR_FLOAT                         KdRatio;
    SCR_FLOAT                         DropoutRate;
    SCR_INT                           KillsOnPlayers;
    SCR_INT                           DeathsByPlayers;
    SCR_INT                           TotalFinishDeathmatchAsTop3;
    SCR_INT                           TotalFinishDeathmatchLast;
    SCR_INT                           DartsTotalWins;
    SCR_INT                           DartsTotalMatches;
    SCR_INT                           ArmwrestlingTotalWins;
    SCR_INT                           ArmwrestlingTotalMatches;
    SCR_INT                           TennisMatchesWon;
    SCR_INT                           TennisMatchesLost;
    SCR_INT                           BaseJumpWins;
    SCR_INT                           BaseJumpLosses;
    SCR_INT                           GolfWins;
    SCR_INT                           GolfLosses;
    SCR_INT                           ShootingRangeWins;
    SCR_INT                           ShootingRangeLosses;
    SCR_INT                           ShootingAbility;
    SCR_INT                           MissionWins;
    SCR_INT                           TotalMissionsPlayed;
    SCR_INT                           SurvivalWins;
    SCR_INT                           TotalSurvivalsPlayed;
    SCR_INT                           PAD_0049; // TODO
    SCR_INT                           MissionsCreated;
    SCR_INT                           CommunicationRestrictions;
    SCR_BOOL                          CanSpectate;
    SCR_INT                           MostFavoriteStation;
    SCR_INT                           ProstitutesFrequented;
    SCR_INT                           LapDancesBought;
    SCR_INT                           Money;
    SCR_FLOAT                         WeaponAccuracy;
    SCR_HASH                          FavoriteVehicle;
    SCR_HASH                          FavoriteWeapon;
};
static_assert(sizeof(PlayerStats) == 60 * 8);

struct IEWarehouseData
{
    SCR_INT                           OwnedWarehouse;
    SCR_INT                           NumVehicles;
    SCR_ARRAY<uint64_t, 40>           Vehicles;
    SCR_INT                           PAD_0043; // set to zero and not read
    SCR_INT                           OwnedWarehouseVariation;
};
static_assert(sizeof(IEWarehouseData) == 45 * 8);

struct PropertyInteriorData
{
    SCR_ARRAY<uint64_t, 30>           PropertyIds;
    SCR_BITSET<ePropertyInteriorFlags>Flags; // I really don't want to indent everything again
    SCR_INT                           RingingPlayers; // bitset of players requesting entry into property
    SCR_INT                           Index; // the value you pass to the send to apartment TSE
    SCR_INT                           Instance;
    SCR_INT                           ExteriorIndex;
    PLAYER_INDEX                      ExteriorOwner;
    SCR_ARRAY<uint64_t, 32>           RingingPlayersState; // 0 = ringing, 1 = accepted, 2 = denied
    GAMER_HANDLE                      OwnerHandle; // can be used to bypass RID spoofing when player is inside interior
    SCR_ARRAY<uint64_t, 30>           EclipseTheme; // not sure why this is an array of 30 yet
    SCR_INT                           ApartmentType; // normal vs stilt vs eclipse
    SCR_INT                           OwnerInstance; // same as Instance in most cases
    uint64_t                          PAD_0116[16]; // TODO
    SCR_INT                           OfficeSafeMoneyMultiplier;
    SCR_BITSET<eInteriorStyleFlags>   StyleFlags;
    SCR_INT                           PAD_0134; // unused
    SCR_INT                           AssistantGreetingChoice;
    SCR_INT                           AssistantDialogBitset;
    SCR_INT                           AssistantDialogBitset2;
    SCR_INT                           LifetimeCargoMissionsComplete; // used for trophy type
    SCR_INT                           CasinoChipsMultiplier;
    SCR_INT                           AssistantDialogBitset3;
    SCR_INT                           AssistantDialogBitset4;
    SCR_INT                           AssistantDialogBitset5;
    SCR_INT                           AssistantDialogBitset6; // do we REALLY need 6 bitsets for assistant dialog?
    IEWarehouseData                   IEWarehouseData;
    SCR_INT                           Garage1DataBitset;
    SCR_INT                           Garage2DataBitset;
    SCR_INT                           Garage3DataBitset;
    SCR_INT                           ModshopDataBitset;
};
static_assert(sizeof(PropertyInteriorData) == 193 * 8);

struct GPBD_FM_Entry
{    
    SCR_INT                           CurrentActivity;
    SCR_INT                           MissionScriptInstance;
    SCR_INT                           PAD_0002; // TODO
    SCR_INT                           NumFreeSpectatorSlots;
    SCR_INT                           NumPlayersInTransition; // not really
    SCR_INT                           NJVSVoteState; // voting screen shown after a mission ends
    SCR_INT                           NJVSVoteContentBitset;
    SCR_BOOL                          NJVSChoiceMade;
    SCR_INT                           NJVSLeaveState; // network error or quit
    SCR_INT                           JobPoints; // can be spoofed to change the "JP" value in the player list
    PLAYER_INDEX                      NextHost; // transfer transition host when joining next job
    PlaylistData                      PlaylistData;
    TEXT_LABEL_63                     JobName;
    SCR_ARRAY<uint64_t, 2>            ActiveGunRange; // this should have really been an enum lol
    MissionData                       MissionData;
    uint64_t                          PAD_0055[2]; // unused
    JobSettings                       JobSettings;
    SCR_INT                           FMMCLauncherState;
    VehicleSelection                  VehicleSelection;
    SCR_INT                           JobStartCloudTime; // this is a struct but too lazy to create one
    SCR_INT                           ContentHash; 
    SCR_BOOL                          PAD_0138; // unused
    SCR_BITSET<eTutorialBitset>       TutorialBitset;
    SCR_BITSET<eGangCallServices>     GangCallRequestedServices;
    PLAYER_INDEX                      GangCallTarget; // can be used to send muggers/hit squad
    SCR_BITSET<eGangCallServices>     GangCallSentServices;
    SCR_INT                           TutorialBitset2;
    TEXT_LABEL_23                     PlayingContentUsedId;
    TEXT_LABEL_23                     MatchId;
    uint64_t                          PAD_0156[8]; // unused
    TEXT_LABEL_63                     DisplayJobName; // as shown in the playerlist?
    StrikeTeam                        StrikeTeam;
    uint64_t                          PAD_0185[7]; // pad
    SCR_INT                           FMMCState;
    SCR_INT                           PAD_0193; // TODO
    SCR_INT                           KillStreak;
    SCR_INT                           NumSuicides; // deducts RP reward in missions
    SCR_INT                           DeathmatchBounty; // "You have been deducted $~1~ for being idle for too long, and you now have a bounty placed on you."
    SCR_BOOL                          CollectedBounty;
    SCR_INT                           AliveDeathmatchPlayers;
    SCR_INT                           WantedLevelFlags;
    SCR_ARRAY<uint64_t, 2>            PAD_0201;
    SCR_INT                           HairdoShopIndex;
    SCR_INT                           PAD_0204;
    PlayerStats                       PlayerStats;
    SCR_INT                           PAD_265;
    SCR_INT                           Mood;

};
static_assert(sizeof(GPBD_FM_Entry) == 267 * 8);

struct GPBD_FM
{
    SCR_ARRAY<GPBD_FM_Entry, 32> Entries;
};
//static_assert(sizeof(GPBD_FM) == 0 * 8);
