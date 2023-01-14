#pragma once
#include <script/types.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

enum class eDeliverableState
{
	INVALID = -1,
	INITIAL,
	DELIVERED
};

struct PLAYER_MISSION_INFO
{
	SCR_INT                            State;
	SCR_INT                            Index; // GSBD_MissionRequest index
};
static_assert(sizeof(PLAYER_MISSION_INFO) == 2 * 8);

struct CRATE_DROP
{
	SCR_INT                            PAD_0000; // unused
	SCR_BOOL                           EnableCrateDrops; // tries to trigger strange last gen stuff unsuccessfully
	uint64_t                           PAD_0003[2]; // unused
};
static_assert(sizeof(CRATE_DROP) == 4 * 8);

struct DELIVERABLE_ID
{
	PLAYER_INDEX                       Owner;
	SCR_INT                            Id; // "FMDeliverableID"
};
static_assert(sizeof(DELIVERABLE_ID) == 2 * 8);

struct DELIVERABLE_SCRIPT_INFO
{
	SCR_HASH                           Hash;
	uint64_t                           PAD_0001[2]; // unused
};
static_assert(sizeof(DELIVERABLE_SCRIPT_INFO) == 3 * 8);

struct UNK_0962
{
	PLAYER_INDEX                       PAD_0000;
	SCR_ARRAY<uint64_t, 18>            PAD_0001;
	SCR_ARRAY<DELIVERABLE_SCRIPT_INFO, 18> PAD_0020;
};
static_assert(sizeof(UNK_0962) == 75 * 8);

struct DELIVERABLE
{
	alignas(8) eDeliverableState       State;
	DELIVERABLE_ID                     DeliverableId;
	SCR_INT                            Type;
	SCR_INT                            PAD_0004; // this is always set to zero
	SCR_ARRAY<uint64_t, 5>             DroppedOffLocations; // "activeDropOff is not the same as sctiptDropOff"
	DELIVERABLE_SCRIPT_INFO            ScriptInfo;
	SCR_INT                            NumDropOffs;
};
static_assert(sizeof(DELIVERABLE) == 15 * 8);

// "FREEMODE_DELIVERY_SERVER_ADD_DELIVERABLE_ID" "_FREEMODE_DELIVERY_MAINTAIN_SERVER"
struct FREEMODE_DELIVERY
{
	SCR_BOOL                           Initialized;
	SCR_ARRAY<DELIVERABLE, 64>         Deliverables;
	SCR_ARRAY<UNK_0962, 10>            PAD_0962; // TODO
};
static_assert(sizeof(FREEMODE_DELIVERY) == 1713 * 8);

struct GLOBAL_CLUB_INFO
{
	uint64_t                           PAD_0000[16];
};
static_assert(sizeof(GLOBAL_CLUB_INFO) == 16 * 8);

struct GSBD_BlockB
{
	SCR_INT                            MissionLauncherInitializedBitset;
	PLAYER_INDEX                       ScriptHost;
	SCR_INT                            PAD_0002;
	SCR_BOOL                           PAD_0003; // forces a team update thingy
	SCR_ARRAY<PLAYER_MISSION_INFO, 32> PlayerMissionInfos;
	SCR_INT                            HostMigrationCounter;
	uint64_t                           PAD_0080[14]; // unused
	CRATE_DROP                         CrateDrop;
	uint64_t                           PAD_0088[6]; // unused
	uint64_t                           PAD_0094[33]; // ???
	uint64_t                           PAD_0127[65]; // even more strange stuff (cut content?)
	SCR_ARRAY<uint64_t, 6>             TurretCooldownTimers;
	FREEMODE_DELIVERY                  FreemodeDelivery;
	SCR_ARRAY<GLOBAL_CLUB_INFO, 3>     GlobalClubInfos;
	SCR_ARRAY<uint64_t, 32>            CarMeetModShopSlotIndices;
	SCR_ARRAY<uint64_t, 32>            CarMeetModShopOccupiedGoons;
	SCR_ARRAY<SCR_ARRAY<uint64_t,3>,32>CarMeetModShopOccupiedVehicleSlots;
};
static_assert(sizeof(GSBD_BlockB) == 2156 * 8);

struct IMPOUND_VEHICLE_INFO
{
	SCR_INT                             ImpoundId;
	SCR_BOOL                            OccupiedCheckDone;
	SCR_INT                             EntityAreaHandle;
	SCR_INT                             TimeCreated;
};
static_assert(sizeof(IMPOUND_VEHICLE_INFO) == 4 * 8);

struct CEO_COLOR
{
	PLAYER_INDEX                        Owner;
	SCR_INT                             Color;
};
static_assert(sizeof(CEO_COLOR) == 2 * 8);

struct CEO_COLORS
{
	SCR_ARRAY<uint64_t, 10>             CeoColorIndices;
	SCR_ARRAY<uint64_t, 32>             CeoColorIndices2;
	SCR_ARRAY<CEO_COLOR, 10>            CeoColors;
	SCR_INT                             PAD_0065;
	uint64_t                            PAD_0066[19];
};
static_assert(sizeof(CEO_COLORS) == 85 * 8);

struct SMPL_INTERIOR_DATA_SERVER
{
	SCR_INT                             PAD_0000; // unused
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorInstances;
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorIds; // used solely for telemetry
	SCR_INT                             PlayerInteriorCreationRequestBitset;
	SCR_ARRAY<uint64_t, 32>             PlayerOwnerBitset;
	SCR_INT                             PlayerInteriorRemovalRequestBitset;
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorCreationTimes;
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorSimpleInteriorTypes;
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorIsOwnerless;
	SCR_ARRAY<uint64_t, 32>             PlayerInteriorOwners;
};
static_assert(sizeof(SMPL_INTERIOR_DATA_SERVER) == 234 * 8);

struct LEAVE_CLUBHOUSE_SERVER
{
	SCR_ARRAY<uint64_t, 32>             Identifiers;
	SCR_ARRAY<uint64_t, 32>             ExitLocations;
	SCR_ARRAY<uint64_t, 32>             ExitLocationSlots;
};
static_assert(sizeof(LEAVE_CLUBHOUSE_SERVER) == 99 * 8);

struct IE_DELIVERY_INFO
{
	PLAYER_INDEX                        Player_;
	SCR_HASH                            VehicleModel;
	PLAYER_INDEX                        ContrabandOwner;
	SCR_INT                             TimeCreated;
	SCR_BOOL                            PAD_0004;
};
static_assert(sizeof(IE_DELIVERY_INFO) == 5 * 8);

struct GSBD
{
	alignas(8) eFreemodeState           FreemodeState;
	SCR_INT                             SessionToken; // time when freemode had started for the script host
	SCR_ARRAY<IMPOUND_VEHICLE_INFO, 32> ImpoundVehicleInfos;
	SCR_ARRAY<SCR_VEC3, 32>             SpawnPositions;
	SCR_ARRAY<uint64_t, 32>             SpawnPositionCreationTimes;
	SCR_ARRAY<uint64_t, 32>             SpawnPositionsValid;
	SCR_ARRAY<uint64_t, 32>             PAD_0294;
	SCR_ARRAY<uint64_t, 32>             SpawnPositionTokens;
	SCR_INT                             SpawnPositionCounter;
	SCR_ARRAY<uint64_t, 32>             RespawnVehicles;
	SCR_ARRAY<uint64_t, 32>             RespawnVehicleSeats;
	SCR_ARRAY<uint64_t, 32>             MorsMutualSpawnSlots;
	SCR_INT                             MorsMutualSpawnPlayersBitset;
	uint64_t                            PAD_0461[353]; // TODO
	SCR_BOOL                            CopTimerOn; // cut CnC content
	SCR_BOOL                            CrookTimerOn;
	SCR_BOOL                            PAD_0816; // always set to FALSE
	SCR_INT                             PAD_0817; // unused
	CEO_COLORS                          CeoColors;
	SMPL_INTERIOR_DATA_SERVER           SimpleInteriorData;
	LEAVE_CLUBHOUSE_SERVER              LeaveClubhouse;
	SCR_ARRAY<IE_DELIVERY_INFO, 32>     IEDeliveryInfos;
	SCR_INT                             PAD_1397;
	NETWORK_INDEX                       IAATurretCameraVehicleId; // used by DDH act 1
	uint64_t                            PAD_1399[97];
	SCR_INT                             CayoPericoStrandedAnimalChoice;
};
static_assert(sizeof(GSBD) == 1497 * 8);

struct PLAYER_BOUNTY
{
	SCR_BOOL                              HasBounty;
	SCR_INT                               BountyAmount;
	SCR_INT                               PAD_0002; // unused
};
static_assert(sizeof(PLAYER_BOUNTY) == 3 * 8);

struct ACTIVE_CONTACT_SERVICE
{
	SCR_INT                               Id;
	PLAYER_INDEX                          Target;
	SCR_BOOL                              Bounty; // unknown usage
	SCR_INT                               Flags;
};
static_assert(sizeof(ACTIVE_CONTACT_SERVICE) == 4 * 8);

struct WEAPON_PICKUPS
{
	SCR_INT                               LastUnkWeaponPickupTime;
	SCR_INT                               LastMeleeWeaponPickupTime;
	SCR_INT                               LastProjectilePickupTime;
	SCR_INT                               LastGunPickupTime;
	SCR_ARRAY<uint64_t, 62>               Indices;
	SCR_ARRAY<uint64_t, 62>               Owners;
	SCR_INT                               SpawnCounter;
	SCR_INT                               AmmoCount;
};
static_assert(sizeof(WEAPON_PICKUPS) == 132 * 8);

struct BIKER_CONTRACTS_SERVER
{
	SCR_ARRAY<uint64_t, 3>                ActiveContracts;
	SCR_ARRAY<uint64_t, 3>                ContractCompleteCount;
	SCR_INT                               CompletedContractBitset;
	SCR_INT                               LastContractRefreshTime;
};
static_assert(sizeof(BIKER_CONTRACTS_SERVER) == 10 * 8);

struct GSBD_FM
{
	SCR_ARRAY<uint64_t, 2>                ModelSwapBits;
	SCR_INT                               PAD_0003; // unused
	SCR_ARRAY<PLAYER_BOUNTY, 32>          PlayerBounties;
	uint64_t                              PAD_0101[5]; // unused
	SCR_ARRAY<uint64_t, 2>                MuggingPlayers; // 0 = mugger, 1 = merryweather mercs
	SCR_ARRAY<uint64_t, 2>                MuggedPlayers;
	uint64_t                              PAD_0112[4]; // unused
	SCR_ARRAY<uint64_t, 60>               PAD_0116; // TODO
	SCR_INT                               ShopProcessingBitset;
	SCR_ARRAY<uint64_t, 79>               ActiveContactServiceBitsets;
	SCR_ARRAY<ACTIVE_CONTACT_SERVICE, 32> ActiveContactServices;
	PLAYER_INDEX                          SpectatorTVWantedPlayer;
	SCR_BOOL                              SpectatorTVWantedClosing;
	SCR_BOOL                              SpectatorTVWantedActive;
	uint64_t                              PAD_0390[2]; // not read by the scripts
	SCR_INT                               PAD_0392; // TODO
	uint64_t                              PAD_0393[6]; // TODO
	WEAPON_PICKUPS                        WeaponPickups;
	BIKER_CONTRACTS_SERVER                BikerContracts;
	SCR_ARRAY<uint64_t, 32>               DoubleActionCacheLocationRevealed;
};
static_assert(sizeof(GSBD_FM) == 574 * 8);
