#pragma once
#include "natives.hpp"

#define PLAYER_INDEX alignas(8) Player
#define ENTITY_INDEX alignas(8) Entity
#define PED_INDEX alignas(8) Ped
#define VEHICLE_INDEX alignas(8) Vehicle
#define INTERIOR_INDEX alignas(8) Interior

#define SCR_HASH alignas(8) Hash
#define SCR_INT alignas(8) int
#define SCR_BOOL alignas(8) BOOL
#define SCR_FLOAT alignas(8) float
#define SCR_VEC3 alignas(8) Vector3

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
#define TEXT_LABEL_23 SCR_TEXT_LABEL<24>
#define TEXT_LABEL_63 SCR_TEXT_LABEL<64>

template <typename T, int SIZE>
struct SCR_ARRAY
{
	SCR_INT      Size;
	alignas(8) T Data[SIZE];

	T& operator [](int index)
	{
		return Data[index]
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
	KLesterCutsceneActive = 12,
	kTrevorCutsceneActive = 13,
	kHeistIntro = 14,
	KPlaneTakedown = 15, // not sure what this is
	kDistractCops = 16, // "Great. Thank you for your help. Now some horrible criminals are in jail for a crime they did commit and it's all your fault!!" ???
	KDestroyVehicle = 17, // ???
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

struct InteriorData
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
};
static_assert(sizeof(InteriorData) == 16 * 8);

struct GlobalPlayerBDEntry
{
	alignas(8) eFreemodeState     FreemodeState;
	uint64_t                      PAD_0001[32]; // TODO
	SCR_INT					      PlayersVisible;
	SCR_INT					      PlayersTracked;
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
};
static_assert(sizeof(GlobalPlayerBDEntry) == 321 * 8);

struct GlobalPlayerBD
{
	SCR_ARRAY<GlobalPlayerBDEntry, 32> Entries;
};