#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_MONEY_NETWORK_INITIALIZE_CASH(int wallet, int bank)
	{
		MONEY::NETWORK_INITIALIZE_CASH(wallet, bank);
	}

	static void LUA_NATIVE_MONEY_NETWORK_DELETE_CHARACTER(int characterSlot, bool p1, bool p2)
	{
		MONEY::NETWORK_DELETE_CHARACTER(characterSlot, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_MANUAL_DELETE_CHARACTER(int characterSlot)
	{
		MONEY::NETWORK_MANUAL_DELETE_CHARACTER(characterSlot);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_GET_PLAYER_IS_HIGH_EARNER()
	{
		auto retval = (bool)MONEY::NETWORK_GET_PLAYER_IS_HIGH_EARNER();
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_CLEAR_CHARACTER_WALLET(int characterSlot)
	{
		MONEY::NETWORK_CLEAR_CHARACTER_WALLET(characterSlot);
	}

	static void LUA_NATIVE_MONEY_NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, uintptr_t gamerHandle)
	{
		MONEY::NETWORK_GIVE_PLAYER_JOBSHARE_CASH(amount, (Any*)gamerHandle);
	}

	static void LUA_NATIVE_MONEY_NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, uintptr_t gamerHandle)
	{
		MONEY::NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(value, (Any*)gamerHandle);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CAN_SHARE_JOB_CASH()
	{
		auto retval = (bool)MONEY::NETWORK_CAN_SHARE_JOB_CASH();
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_REFUND_CASH(int index, sol::stack_object context, sol::stack_object reason, bool p3)
	{
		MONEY::NETWORK_REFUND_CASH(index, context.is<const char*>() ? context.as<const char*>() : nullptr, reason.is<const char*>() ? reason.as<const char*>() : nullptr, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_DEDUCT_CASH(int amount, sol::stack_object p1, sol::stack_object p2, bool p3, bool p4, bool p5)
	{
		MONEY::NETWORK_DEDUCT_CASH(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3, p4, p5);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_MONEY_CAN_BET(int amount, bool p1, bool p2)
	{
		auto retval = (bool)MONEY::NETWORK_MONEY_CAN_BET(amount, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CAN_BET(int amount)
	{
		auto retval = (bool)MONEY::NETWORK_CAN_BET(amount);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET(Hash hash)
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_CAN_BET(hash);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET_PVC()
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_CAN_BET_PVC();
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET_AMOUNT(Any p0)
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_CAN_BET_AMOUNT(p0);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BUY_CHIPS_PVC()
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_CAN_BUY_CHIPS_PVC();
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_BUY_CHIPS(int p0, int p1)
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_BUY_CHIPS(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CASINO_SELL_CHIPS(int p0, int p1)
	{
		auto retval = (bool)MONEY::NETWORK_CASINO_SELL_CHIPS(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE()
	{
		MONEY::NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE();
	}

	static std::tuple<bool, int> LUA_NATIVE_MONEY_CAN_PAY_AMOUNT_TO_BOSS(int p0, int p1, int amount, int p3)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)MONEY::CAN_PAY_AMOUNT_TO_BOSS(p0, p1, amount, &p3);
		std::get<1>(return_values) = p3;

		return return_values;
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PICKUP(int amount)
	{
		MONEY::NETWORK_EARN_FROM_PICKUP(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CASHING_OUT(int amount)
	{
		MONEY::NETWORK_EARN_FROM_CASHING_OUT(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_GANGATTACK_PICKUP(int amount)
	{
		MONEY::NETWORK_EARN_FROM_GANGATTACK_PICKUP(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ASSASSINATE_TARGET_KILLED(int amount)
	{
		MONEY::NETWORK_EARN_ASSASSINATE_TARGET_KILLED(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_ROB_ARMORED_CARS(int amount)
	{
		MONEY::NETWORK_EARN_FROM_ROB_ARMORED_CARS(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CRATE_DROP(int amount)
	{
		MONEY::NETWORK_EARN_FROM_CRATE_DROP(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BETTING(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_FROM_BETTING(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOB(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_FROM_JOB(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOBX2(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_FROM_JOBX2(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PREMIUM_JOB(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_FROM_PREMIUM_JOB(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BEND_JOB(int amount, sol::stack_object heistHash)
	{
		MONEY::NETWORK_EARN_FROM_BEND_JOB(amount, heistHash.is<const char*>() ? heistHash.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CHALLENGE_WIN(Any p0, uintptr_t p1, bool p2)
	{
		MONEY::NETWORK_EARN_FROM_CHALLENGE_WIN(p0, (Any*)p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BOUNTY(int amount, uintptr_t gamerHandle, uintptr_t p2, Any p3)
	{
		MONEY::NETWORK_EARN_FROM_BOUNTY(amount, (Any*)gamerHandle, (Any*)p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_IMPORT_EXPORT(int amount, Hash modelHash)
	{
		MONEY::NETWORK_EARN_FROM_IMPORT_EXPORT(amount, modelHash);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_HOLDUPS(int amount)
	{
		MONEY::NETWORK_EARN_FROM_HOLDUPS(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName)
	{
		MONEY::NETWORK_EARN_FROM_PROPERTY(amount, propertyName);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_AI_TARGET_KILL(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FROM_AI_TARGET_KILL(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_NOT_BADSPORT(int amount)
	{
		MONEY::NETWORK_EARN_FROM_NOT_BADSPORT(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7)
	{
		MONEY::NETWORK_EARN_FROM_VEHICLE(p0, p1, p2, p3, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PERSONAL_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8)
	{
		MONEY::NETWORK_EARN_FROM_PERSONAL_VEHICLE(p0, p1, p2, p3, p4, p5, p6, p7, p8);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_DAILY_OBJECTIVES(int amount, sol::stack_object type, int characterSlot)
	{
		MONEY::NETWORK_EARN_FROM_DAILY_OBJECTIVES(amount, type.is<const char*>() ? type.as<const char*>() : nullptr, characterSlot);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_AMBIENT_JOB(int p0, sol::stack_object p1, uintptr_t p2)
	{
		MONEY::NETWORK_EARN_FROM_AMBIENT_JOB(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr, (Any*)p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOB_BONUS(Any p0, uintptr_t p1, uintptr_t p2)
	{
		MONEY::NETWORK_EARN_FROM_JOB_BONUS(p0, (Any*)p1, (Any*)p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CRIMINAL_MASTERMIND(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_FROM_CRIMINAL_MASTERMIND(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_HEIST_AWARD(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_HEIST_AWARD(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FIRST_TIME_BONUS(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_FIRST_TIME_BONUS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GOON(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_GOON(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BOSS(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_BOSS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_AGENCY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_WAREHOUSE(int amount, int id)
	{
		MONEY::NETWORK_EARN_FROM_WAREHOUSE(amount, id);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CONTRABAND(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_FROM_CONTRABAND(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_DESTROYING_CONTRABAND(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_FROM_DESTROYING_CONTRABAND(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_SMUGGLER_WORK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		MONEY::NETWORK_EARN_FROM_SMUGGLER_WORK(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_HANGAR_TRADE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FROM_HANGAR_TRADE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_PURCHASE_CLUB_HOUSE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_PURCHASE_CLUB_HOUSE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_PRODUCT(int amount, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_FROM_BUSINESS_PRODUCT(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_VEHICLE_EXPORT(int amount, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_FROM_VEHICLE_EXPORT(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SMUGGLER_AGENCY(int amount, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_SMUGGLER_AGENCY(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BOUNTY_HUNTER_REWARD(Any p0)
	{
		MONEY::NETWORK_EARN_BOUNTY_HUNTER_REWARD(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_BATTLE(Any p0)
	{
		MONEY::NETWORK_EARN_FROM_BUSINESS_BATTLE(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION(Any p0, int p1)
	{
		MONEY::NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION(Any p0)
	{
		MONEY::NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_HUB_SELL(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_FROM_BUSINESS_HUB_SELL(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_FMBB_BOSS_WORK(Any p0)
	{
		MONEY::NETWORK_EARN_FROM_FMBB_BOSS_WORK(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FMBB_WAGE_BONUS(Any p0)
	{
		MONEY::NETWORK_EARN_FMBB_WAGE_BONUS(p0);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CAN_SPEND_MONEY(Any p0, bool p1, bool p2, bool p3, Any p4, Any p5)
	{
		auto retval = (bool)MONEY::NETWORK_CAN_SPEND_MONEY(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CAN_SPEND_MONEY2(Any p0, bool p1, bool p2, bool p3, uintptr_t p4, Any p5, Any p6)
	{
		auto retval = (bool)MONEY::NETWORK_CAN_SPEND_MONEY2(p0, p1, p2, p3, (Any*)p4, p5, p6);
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_ITEM(int amount, Hash item, Any p2, Any p3, bool p4, sol::stack_object item_name, Any p6, Any p7, Any p8, bool p9)
	{
		MONEY::NETWORK_BUY_ITEM(amount, item, p2, p3, p4, item_name.is<const char*>() ? item_name.as<const char*>() : nullptr, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_TAXI(int amount, bool p1, bool p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPENT_TAXI(amount, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_PAY_EMPLOYEE_WAGE(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_PAY_EMPLOYEE_WAGE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_PAY_MATCH_ENTRY_FEE(int amount, sol::stack_object matchId, bool p2, bool p3)
	{
		MONEY::NETWORK_PAY_MATCH_ENTRY_FEE(amount, matchId.is<const char*>() ? matchId.as<const char*>() : nullptr, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BETTING(int amount, int p1, sol::stack_object matchId, bool p3, bool p4)
	{
		MONEY::NETWORK_SPENT_BETTING(amount, p1, matchId.is<const char*>() ? matchId.as<const char*>() : nullptr, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_WAGER(Any p0, Any p1, int amount)
	{
		MONEY::NETWORK_SPENT_WAGER(p0, p1, amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_IN_STRIPCLUB(Any p0, bool p1, Any p2, bool p3)
	{
		MONEY::NETWORK_SPENT_IN_STRIPCLUB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_HEALTHCARE(int cost, bool p1, bool p2)
	{
		MONEY::NETWORK_BUY_HEALTHCARE(cost, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_AIRSTRIKE(int cost, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_BUY_AIRSTRIKE(cost, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_BACKUP_GANG(int p0, int p1, bool p2, bool p3, int npcProvider)
	{
		MONEY::NETWORK_BUY_BACKUP_GANG(p0, p1, p2, p3, npcProvider);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_HELI_STRIKE(int cost, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_BUY_HELI_STRIKE(cost, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_AMMO_DROP(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_AMMO_DROP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_BOUNTY(int amount, Player victim, bool p2, bool p3, Any p4)
	{
		MONEY::NETWORK_BUY_BOUNTY(amount, victim, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_PROPERTY(int cost, Hash propertyName, bool p2, bool p3)
	{
		MONEY::NETWORK_BUY_PROPERTY(cost, propertyName, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_SMOKES(int p0, bool p1, bool p2)
	{
		MONEY::NETWORK_BUY_SMOKES(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HELI_PICKUP(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_HELI_PICKUP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BOAT_PICKUP(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BOAT_PICKUP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BULL_SHARK(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BULL_SHARK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CASH_DROP(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_CASH_DROP(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HIRE_MUGGER(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_HIRE_MUGGER(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_ROBBED_BY_MUGGER(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HIRE_MERCENARY(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_HIRE_MERCENARY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_WANTEDLEVEL(Any p0, uintptr_t p1, bool p2, bool p3, Any p4)
	{
		MONEY::NETWORK_SPENT_BUY_WANTEDLEVEL(p0, (Any*)p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_OFFTHERADAR(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_OFFTHERADAR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_REVEAL_PLAYERS(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_REVEAL_PLAYERS(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CARWASH(Any p0, Any p1, Any p2, bool p3, bool p4)
	{
		MONEY::NETWORK_SPENT_CARWASH(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CINEMA(Any p0, Any p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_CINEMA(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_TELESCOPE(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_TELESCOPE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HOLDUPS(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_HOLDUPS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_PASSIVE_MODE(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_PASSIVE_MODE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BANK_INTEREST(int p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_BANK_INTEREST(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PROSTITUTES(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_PROSTITUTES(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_ARREST_BAIL(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_ARREST_BAIL(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, uintptr_t gamerHandle, bool notBankrupt, bool hasTheMoney)
	{
		MONEY::NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(amount, vehicleModel, (Any*)gamerHandle, notBankrupt, hasTheMoney);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CALL_PLAYER(Any p0, uintptr_t p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_CALL_PLAYER(p0, (Any*)p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BOUNTY(Any p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_BOUNTY(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_FROM_ROCKSTAR(int p0, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_FROM_ROCKSTAR(p0, p1, p2);
	}

	static int LUA_NATIVE_MONEY_NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS(int amount)
	{
		auto retval = MONEY::NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS(amount);
		return retval;
	}

	static std::tuple<const char*, int, int> LUA_NATIVE_MONEY_PROCESS_CASH_GIFT(int p0, int p1, sol::stack_object p2)
	{
		std::tuple<const char*, int, int> return_values;
		std::get<0>(return_values) = MONEY::PROCESS_CASH_GIFT(&p0, &p1, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;

		return return_values;
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_MOVE_SUBMARINE(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPENT_MOVE_SUBMARINE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PLAYER_HEALTHCARE(int p0, int p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_PLAYER_HEALTHCARE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_NO_COPS(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_NO_COPS(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CARGO_SOURCING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		MONEY::NETWORK_SPENT_CARGO_SOURCING(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_REQUEST_JOB(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_REQUEST_JOB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_REQUEST_HEIST(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPENT_REQUEST_HEIST(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_FAIRGROUND_RIDE(int amount, Any p1, bool p2, bool p3, Any p4)
	{
		MONEY::NETWORK_BUY_FAIRGROUND_RIDE(amount, p1, p2, p3, p4);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS()
	{
		auto retval = (bool)MONEY::NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS();
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_JOB_SKIP(int amount, sol::stack_object matchId, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_JOB_SKIP(amount, matchId.is<const char*>() ? matchId.as<const char*>() : nullptr, p2, p3);
	}

	static bool LUA_NATIVE_MONEY_NETWORK_SPENT_BOSS_GOON(int amount, bool p1, bool p2)
	{
		auto retval = (bool)MONEY::NETWORK_SPENT_BOSS_GOON(amount, p1, p2);
		return retval;
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GOON(int p0, int p1, int amount)
	{
		MONEY::NETWORK_SPEND_GOON(p0, p1, amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BOSS(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPEND_BOSS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_MOVE_YACHT(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_MOVE_YACHT(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_RENAME_ORGANIZATION(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_RENAME_ORGANIZATION(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_BUY_CONTRABAND_MISSION(int p0, int p1, Hash p2, bool p3, bool p4)
	{
		MONEY::NETWORK_BUY_CONTRABAND_MISSION(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_HELI(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PA_SERVICE_HELI(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_VEHICLE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PA_SERVICE_VEHICLE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_SNACK(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PA_SERVICE_SNACK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_DANCER(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PA_SERVICE_DANCER(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_IMPOUND(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPENT_PA_SERVICE_IMPOUND(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PA_HELI_PICKUP(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PA_HELI_PICKUP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY(int amount, uintptr_t data, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY(amount, (Any*)data, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_JUKEBOX(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_JUKEBOX(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_CLUB_HOUSE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_CLUB_HOUSE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_TRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_TRADE_BUSINESS_PROPERTY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_MC_ABILITY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPENT_MC_ABILITY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PAY_BUSINESS_SUPPLIES(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PAY_BUSINESS_SUPPLIES(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_CHANGE_APPEARANCE(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPENT_CHANGE_APPEARANCE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_VEHICLE_EXPORT_MODS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9)
	{
		MONEY::NETWORK_SPENT_VEHICLE_EXPORT_MODS(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_OFFICE_GARAGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_OFFICE_GARAGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_IMPORT_EXPORT_REPAIR(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPENT_IMPORT_EXPORT_REPAIR(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_HANGAR(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_HANGAR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_HANGAR(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_HANGAR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HANGAR_UTILITY_CHARGES(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_HANGAR_UTILITY_CHARGES(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_HANGAR_STAFF_CHARGES(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_HANGAR_STAFF_CHARGES(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_TRUCK(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_TRUCK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_TRUCK(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_TRUCK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_BUNKER(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_BUNKER(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPRADE_BUNKER(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPRADE_BUNKER(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_SELL_BUNKER(int amount, Hash bunkerHash)
	{
		MONEY::NETWORK_EARN_FROM_SELL_BUNKER(amount, bunkerHash);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BALLISTIC_EQUIPMENT(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_BALLISTIC_EQUIPMENT(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_RDR_BONUS(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_RDR_BONUS(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_WAGE_PAYMENT(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_WAGE_PAYMENT(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_WAGE_PAYMENT_BONUS(int amount)
	{
		MONEY::NETWORK_EARN_WAGE_PAYMENT_BONUS(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_BASE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_BASE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_BASE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_BASE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_TILTROTOR(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_BUY_TILTROTOR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_TILTROTOR(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_TILTROTOR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_EMPLOY_ASSASSINS(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_EMPLOY_ASSASSINS(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_CANNON(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_GANGOPS_CANNON(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_GANGOPS_SKIP_MISSION(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SELL_BASE(int amount, Hash baseNameHash)
	{
		MONEY::NETWORK_EARN_SELL_BASE(amount, baseNameHash);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_TARGET_REFUND(int amount, int p1)
	{
		MONEY::NETWORK_EARN_TARGET_REFUND(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_WAGES(int amount, int p1)
	{
		MONEY::NETWORK_EARN_GANGOPS_WAGES(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_WAGES_BONUS(int amount, int p1)
	{
		MONEY::NETWORK_EARN_GANGOPS_WAGES_BONUS(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAR_CHALLENGE(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_DAR_CHALLENGE(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DOOMSDAY_FINALE_BONUS(int amount, Hash vehicleHash)
	{
		MONEY::NETWORK_EARN_DOOMSDAY_FINALE_BONUS(amount, vehicleHash);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_AWARD(int amount, sol::stack_object p1, Any p2)
	{
		MONEY::NETWORK_EARN_GANGOPS_AWARD(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_ELITE(int amount, sol::stack_object p1, int actIndex)
	{
		MONEY::NETWORK_EARN_GANGOPS_ELITE(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr, actIndex);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY(int earnedMoney)
	{
		MONEY::NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY(earnedMoney);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_START_STRAND(int type, int amount, bool p2, bool p3)
	{
		MONEY::NETWORK_SPEND_GANGOPS_START_STRAND(type, amount, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_TRIP_SKIP(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPEND_GANGOPS_TRIP_SKIP(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_PREP_PARTICIPATION(int amount)
	{
		MONEY::NETWORK_EARN_GANGOPS_PREP_PARTICIPATION(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_SETUP(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_GANGOPS_SETUP(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_FINALE(int amount, sol::stack_object p1)
	{
		MONEY::NETWORK_EARN_GANGOPS_FINALE(amount, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_REPAIR_COST(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_SPEND_GANGOPS_REPAIR_COST(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_NIGHTCLUB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB_DANCING(Any p0)
	{
		MONEY::NETWORK_EARN_NIGHTCLUB_DANCING(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BB_EVENT_BONUS(int amount)
	{
		MONEY::NETWORK_EARN_BB_EVENT_BONUS(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_HACKER_TRUCK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_HACKER_TRUCK(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_HACKER_TRUCK(Any p0, int amount, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_HACKER_TRUCK(p0, amount, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		MONEY::NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_RDR_HATCHET_BONUS(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPENT_RDR_HATCHET_BONUS(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE(Player player, int amount, Any p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE(player, amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_NIGHTCLUB_BAR_DRINK(int amount, Any p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPEND_NIGHTCLUB_BAR_DRINK(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BOUNTY_HUNTER_MISSION(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPEND_BOUNTY_HUNTER_MISSION(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_REHIRE_DJ(int amount, Any p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_REHIRE_DJ(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_ARENA_JOIN_SPECTATOR(int amount, Any p1, bool p2, bool p3)
	{
		MONEY::NETWORK_SPENT_ARENA_JOIN_SPECTATOR(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_CAREER_PROGRESSION(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_ARENA_CAREER_PROGRESSION(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_MAKE_IT_RAIN(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPEND_MAKE_IT_RAIN(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ARENA(int amount, bool p1, bool p2, sol::stack_object p3)
	{
		MONEY::NETWORK_SPEND_BUY_ARENA(amount, p1, p2, p3.is<const char*>() ? p3.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ARENA(int amount, bool p1, bool p2, sol::stack_object p3)
	{
		MONEY::NETWORK_SPEND_UPGRADE_ARENA(amount, p1, p2, p3.is<const char*>() ? p3.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_ARENA_SPECTATOR_BOX(int amount, int type, bool p2, bool p3)
	{
		MONEY::NETWORK_SPEND_ARENA_SPECTATOR_BOX(amount, type, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT(int amount, Any p1, bool p2)
	{
		MONEY::NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SPIN_THE_WHEEL_CASH(int amount)
	{
		MONEY::NETWORK_EARN_SPIN_THE_WHEEL_CASH(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_ARENA_PREMIUM(int amount, bool p1, bool p2)
	{
		MONEY::NETWORK_SPEND_ARENA_PREMIUM(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR(int amount, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_ARENA_WAR(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET(int amount)
	{
		MONEY::NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR_EVENT_CARGO(int amount)
	{
		MONEY::NETWORK_EARN_ARENA_WAR_EVENT_CARGO(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_RC_TIME_TRIAL(int amount)
	{
		MONEY::NETWORK_EARN_RC_TIME_TRIAL(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_OBJECTIVE_EVENT(int amount)
	{
		MONEY::NETWORK_EARN_DAILY_OBJECTIVE_EVENT(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_MEMBERSHIP(int amount, bool p1, bool p2, int p3)
	{
		MONEY::NETWORK_SPEND_CASINO_MEMBERSHIP(amount, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_CASINO(int amount, bool p1, bool p2, uintptr_t data)
	{
		MONEY::NETWORK_SPEND_BUY_CASINO(amount, p1, p2, (Any*)data);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_CASINO(int amount, bool p1, bool p2, uintptr_t data)
	{
		MONEY::NETWORK_SPEND_UPGRADE_CASINO(amount, p1, p2, (Any*)data);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_GENERIC(int amount, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_CASINO_GENERIC(amount, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_TIME_TRIAL_WIN(int amount)
	{
		MONEY::NETWORK_EARN_CASINO_TIME_TRIAL_WIN(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLES_ACTION_FIGURES(int amount)
	{
		MONEY::NETWORK_EARN_COLLECTABLES_ACTION_FIGURES(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION(int amount)
	{
		MONEY::NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SELL_PRIZE_VEHICLE(int amount, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_SELL_PRIZE_VEHICLE(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_MISSION_REWARD(int amount)
	{
		MONEY::NETWORK_EARN_CASINO_MISSION_REWARD(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_STORY_MISSION_REWARD(int amount)
	{
		MONEY::NETWORK_EARN_CASINO_STORY_MISSION_REWARD(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_MISSION_PARTICIPATION(int amount)
	{
		MONEY::NETWORK_EARN_CASINO_MISSION_PARTICIPATION(amount);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_AWARD(int amount, Hash hash)
	{
		MONEY::NETWORK_EARN_CASINO_AWARD(amount, hash);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ARCADE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BUY_ARCADE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ARCADE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_UPGRADE_ARCADE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10)
	{
		MONEY::NETWORK_SPEND_CASINO_HEIST(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_ARCADE_MGMT(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_ARCADE_MGMT(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_PLAY_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_PLAY_ARCADE(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_ARCADE(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		MONEY::NETWORK_EARN_CASINO_HEIST(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_ARCADE(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_UPGRADE_ARCADE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		MONEY::NETWORK_EARN_ARCADE(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLES(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_COLLECTABLES(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CHALLENGE(int amount, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_CHALLENGE(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_HEIST_AWARDS(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_EARN_CASINO_HEIST_AWARDS(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLE_ITEM(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_COLLECTABLE_ITEM(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_YATCH_MISSION(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_YATCH_MISSION(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DISPATCH_CALL(int amount, Any p1)
	{
		MONEY::NETWORK_EARN_DISPATCH_CALL(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BEACH_PARTY(Any p0)
	{
		MONEY::NETWORK_SPEND_BEACH_PARTY(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SUBMARINE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		MONEY::NETWORK_SPEND_SUBMARINE(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_CLUB(int amount1, Any p1, bool p2, Any p3, int p4, int p5, int p6, int amount2, Any p8)
	{
		MONEY::NETWORK_SPEND_CASINO_CLUB(amount1, p1, p2, p3, p4, p5, p6, amount2, p8);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_SUB(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BUY_SUB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_SUB(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_UPGRADE_SUB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_ISLAND_HEIST(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_ISLAND_HEIST(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_ISLAND_HEIST(int amount1, Any p1, Any p2, Any p3, int amount2, int p5)
	{
		MONEY::NETWORK_EARN_ISLAND_HEIST(amount1, p1, p2, p3, amount2, p5);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BEACH_PARTY_LOST_FOUND(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_BEACH_PARTY_LOST_FOUND(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_MEMBERSHIP(int amount1, Any p1, Any p2, int amount2, Any p4)
	{
		MONEY::NETWORK_SPEND_CAR_CLUB_MEMBERSHIP(amount1, p1, p2, amount2, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_BAR(Any p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPEND_CAR_CLUB_BAR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_AUTOSHOP_MODIFY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_AUTOSHOP_MODIFY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_TAKEOVER(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_CAR_CLUB_TAKEOVER(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_AUTOSHOP(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BUY_AUTOSHOP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_AUTOSHOP(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_UPGRADE_AUTOSHOP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AUTOSHOP_BUSINESS(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_AUTOSHOP_BUSINESS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AUTOSHOP_INCOME(Any p0, int p1)
	{
		MONEY::NETWORK_EARN_AUTOSHOP_INCOME(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_CARCLUB_MEMBERSHIP(Any p0)
	{
		MONEY::NETWORK_EARN_CARCLUB_MEMBERSHIP(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_VEHICLE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_DAILY_VEHICLE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_VEHICLE_BONUS(Any p0)
	{
		MONEY::NETWORK_EARN_DAILY_VEHICLE_BONUS(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_TUNER_AWARD(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_TUNER_AWARD(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_TUNER_ROBBERY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_EARN_TUNER_ROBBERY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_AUTOSHOP(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_UPGRADE_AUTOSHOP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_INTERACTION_MENU_ABILITY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_INTERACTION_MENU_ABILITY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SET_COMMON_FIELDS(Any p0, Any p1, Any p2, bool p3)
	{
		MONEY::NETWORK_SPEND_SET_COMMON_FIELDS(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SET_DISCOUNT(bool p0)
	{
		MONEY::NETWORK_SPEND_SET_DISCOUNT(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_AGENCY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BUY_AGENCY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_AGENCY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_UPGRADE_AGENCY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_AGENCY(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_AGENCY(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_HIDDEN(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_HIDDEN(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SOURCE_BIKE(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_SOURCE_BIKE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_COMP_SUV(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_COMP_SUV(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SUV_FST_TRVL(int p0, bool p1, bool p2, Any p3)
	{
		MONEY::NETWORK_SPEND_SUV_FST_TRVL(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_SUPPLY(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_SUPPLY(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BIKE_SHOP(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BIKE_SHOP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_VEHICLE_REQUESTED(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		MONEY::NETWORK_SPEND_VEHICLE_REQUESTED(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_GUNRUNNING(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_GUNRUNNING(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_SAFE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AGENCY_SAFE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_CONTRACT(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AWARD_CONTRACT(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_CONTRACT(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AGENCY_CONTRACT(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_PHONE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AWARD_PHONE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_PHONE(Any p0, Any p1, Any p2)
	{
		MONEY::NETWORK_EARN_AGENCY_PHONE(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_FIXER_MISSION(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AWARD_FIXER_MISSION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_PREP(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FIXER_PREP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_FINALE(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FIXER_FINALE(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_SHORT_TRIP(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_AWARD_SHORT_TRIP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_RIVAL_DELIVERY(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_FIXER_RIVAL_DELIVERY(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_AGENCY(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_UPGRADE_AGENCY(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_APARTMENT_UTILITIES(int amount, bool p1, bool p2, uintptr_t data)
	{
		MONEY::NETWORK_SPEND_APARTMENT_UTILITIES(amount, p1, p2, (Any*)data);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUSINESS_PROPERTY_FEES(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_SPEND_BUSINESS_PROPERTY_FEES(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SIGHTSEEING_REWARD(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_EARN_SIGHTSEEING_REWARD(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BIKER_SHOP(Any p0, Any p1)
	{
		MONEY::NETWORK_EARN_BIKER_SHOP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BIKER(Any p0)
	{
		MONEY::NETWORK_EARN_BIKER(p0);
	}

	static void LUA_NATIVE_MONEY_NETWORK_YOHAN_SOURCE_GOODS(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::NETWORK_YOHAN_SOURCE_GOODS(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_MFGARAGE_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_BUY_MFGARAGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_MFGARAGE_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_UPGRADE_MFGARAGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_SUPPLIES_(int p0, bool p1, bool p2, int p3)
	{
		MONEY::_NETWORK_SPEND_BUY_SUPPLIES(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ACID_LAB_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_BUY_ACID_LAB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR_(int p0, bool p1, bool p2, int p3)
	{
		MONEY::_NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP_(int p0, bool p1, bool p2, int p3)
	{
		MONEY::_NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_MINES_(int p0, bool p1, bool p2, int p3)
	{
		MONEY::_NETWORK_SPEND_UPGRADE_ACID_LAB_MINES(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_RENAME_ACID_LAB_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_RENAME_ACID_LAB(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPEND_RENAME_ACID_PRODUCT_(Any p0, Any p1, Any p2, Any p3)
	{
		MONEY::_NETWORK_SPEND_RENAME_ACID_PRODUCT(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_JUGGALO_MISSION_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_JUGGALO_MISSION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_ACID_LAB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_ACID_LAB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_DAILY_STASH_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_DAILY_STASH(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_DEAD_DROP_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_DEAD_DROP(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_RANDOM_EVENT_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_RANDOM_EVENT(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_TAXI_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_AWARD_TAXI(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_STREET_DEALER_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_STREET_DEALER(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SELL_ACID_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_SELL_ACID(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_JUGGALO_STORY_MISSION_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_JUGGALO_STORY_MISSION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FOOLIGAN_JOB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_FOOLIGAN_JOB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_TAXI_JOB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_TAXI_JOB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_AVENGER_(int amount, int p1)
	{
		MONEY::_NETWORK_EARN_AVENGER(amount, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_SMUGGLER_OPS_(Any p0, Any p1, Any p2)
	{
		MONEY::_NETWORK_EARN_SMUGGLER_OPS(p0, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_BONUS_OBJECTIVE_(int amount, Any p1, Any p2)
	{
		MONEY::_NETWORK_EARN_BONUS_OBJECTIVE(amount, p1, p2);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_PROGRESS_HUB_(Any p0, Any p1)
	{
		MONEY::_NETWORK_EARN_PROGRESS_HUB(p0, p1);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_AIR_FREIGHT_(int hangarCargoSourcingPrice, bool fromBank, bool fromBankAndWallet, int cost, int warehouseId, int warehouseSlot)
	{
		MONEY::_NETWORK_SPENT_AIR_FREIGHT(hangarCargoSourcingPrice, fromBank, fromBankAndWallet, cost, warehouseId, warehouseSlot);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP_(int amount, bool fromBank, bool fromBankAndWallet, int cost)
	{
		MONEY::_NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP(amount, fromBank, fromBankAndWallet, cost);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_STEALTH_MODULE_(int amount, bool fromBank, bool fromBankAndWallet, Hash p3)
	{
		MONEY::_NETWORK_SPENT_STEALTH_MODULE(amount, fromBank, fromBankAndWallet, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_MISSILE_JAMMER_(int amount, bool fromBank, bool fromBankAndWallet, Hash p3)
	{
		MONEY::_NETWORK_SPENT_MISSILE_JAMMER(amount, fromBank, fromBankAndWallet, p3);
	}

	static void LUA_NATIVE_MONEY_NETWORK_SPENT_GENERIC_(int price, bool p1, bool p2, Hash stat, Hash spent, sol::stack_object p5, sol::stack_object p6, uintptr_t data)
	{
		MONEY::_NETWORK_SPENT_GENERIC(price, p1, p2, stat, spent, p5.is<const char*>() ? p5.as<const char*>() : nullptr, p6.is<const char*>() ? p6.as<const char*>() : nullptr, (Any*)data);
	}

	static void LUA_NATIVE_MONEY_NETWORK_EARN_GENERIC_(int amount, Hash earn, sol::stack_object p2, sol::stack_object p3, uintptr_t data)
	{
		MONEY::_NETWORK_EARN_GENERIC(amount, earn, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3.is<const char*>() ? p3.as<const char*>() : nullptr, (Any*)data);
	}

	static void LUA_NATIVE_MONEY_NETWORK_CLEAR_TRANSACTION_TELEMETRY_NONCE_()
	{
		MONEY::_NETWORK_CLEAR_TRANSACTION_TELEMETRY_NONCE();
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_VC_BANK_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_VC_BANK_BALANCE();
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_VC_WALLET_BALANCE(int characterSlot)
	{
		auto retval = MONEY::NETWORK_GET_VC_WALLET_BALANCE(characterSlot);
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_VC_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_VC_BALANCE();
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_EVC_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_EVC_BALANCE();
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_PVC_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_PVC_BALANCE();
		return retval;
	}

	static const char* LUA_NATIVE_MONEY_NETWORK_GET_STRING_WALLET_BALANCE(int characterSlot)
	{
		auto retval = MONEY::NETWORK_GET_STRING_WALLET_BALANCE(characterSlot);
		return retval;
	}

	static const char* LUA_NATIVE_MONEY_NETWORK_GET_STRING_BANK_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_STRING_BANK_BALANCE();
		return retval;
	}

	static const char* LUA_NATIVE_MONEY_NETWORK_GET_STRING_BANK_WALLET_BALANCE(int character)
	{
		auto retval = MONEY::NETWORK_GET_STRING_BANK_WALLET_BALANCE(character);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_WALLET(int amount, int characterSlot)
	{
		auto retval = (bool)MONEY::NETWORK_GET_CAN_SPEND_FROM_WALLET(amount, characterSlot);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_BANK(int amount)
	{
		auto retval = (bool)MONEY::NETWORK_GET_CAN_SPEND_FROM_BANK(amount);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET(int amount, int characterSlot)
	{
		auto retval = (bool)MONEY::NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET(amount, characterSlot);
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_PVC_TRANSFER_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_PVC_TRANSFER_BALANCE();
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_GET_CAN_TRANSFER_CASH(int amount)
	{
		auto retval = (bool)MONEY::NETWORK_GET_CAN_TRANSFER_CASH(amount);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_NETWORK_CAN_RECEIVE_PLAYER_CASH(Any p0, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)MONEY::NETWORK_CAN_RECEIVE_PLAYER_CASH(p0, p1, p2, p3);
		return retval;
	}

	static int LUA_NATIVE_MONEY_NETWORK_GET_REMAINING_TRANSFER_BALANCE()
	{
		auto retval = MONEY::NETWORK_GET_REMAINING_TRANSFER_BALANCE();
		return retval;
	}

	static int LUA_NATIVE_MONEY_WITHDRAW_VC(int amount)
	{
		auto retval = MONEY::WITHDRAW_VC(amount);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_DEPOSIT_VC(int amount)
	{
		auto retval = (bool)MONEY::DEPOSIT_VC(amount);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_HAS_VC_WITHDRAWAL_COMPLETED(Any p0)
	{
		auto retval = (bool)MONEY::HAS_VC_WITHDRAWAL_COMPLETED(p0);
		return retval;
	}

	static bool LUA_NATIVE_MONEY_WAS_VC_WITHDRAWAL_SUCCESSFUL(Any p0)
	{
		auto retval = (bool)MONEY::WAS_VC_WITHDRAWAL_SUCCESSFUL(p0);
		return retval;
	}

	void init_native_binding_MONEY(sol::state& L)
	{
		auto MONEY = L["MONEY"].get_or_create<sol::table>();
		MONEY.set_function("NETWORK_INITIALIZE_CASH", LUA_NATIVE_MONEY_NETWORK_INITIALIZE_CASH);
		MONEY.set_function("NETWORK_DELETE_CHARACTER", LUA_NATIVE_MONEY_NETWORK_DELETE_CHARACTER);
		MONEY.set_function("NETWORK_MANUAL_DELETE_CHARACTER", LUA_NATIVE_MONEY_NETWORK_MANUAL_DELETE_CHARACTER);
		MONEY.set_function("NETWORK_GET_PLAYER_IS_HIGH_EARNER", LUA_NATIVE_MONEY_NETWORK_GET_PLAYER_IS_HIGH_EARNER);
		MONEY.set_function("NETWORK_CLEAR_CHARACTER_WALLET", LUA_NATIVE_MONEY_NETWORK_CLEAR_CHARACTER_WALLET);
		MONEY.set_function("NETWORK_GIVE_PLAYER_JOBSHARE_CASH", LUA_NATIVE_MONEY_NETWORK_GIVE_PLAYER_JOBSHARE_CASH);
		MONEY.set_function("NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH", LUA_NATIVE_MONEY_NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH);
		MONEY.set_function("NETWORK_CAN_SHARE_JOB_CASH", LUA_NATIVE_MONEY_NETWORK_CAN_SHARE_JOB_CASH);
		MONEY.set_function("NETWORK_REFUND_CASH", LUA_NATIVE_MONEY_NETWORK_REFUND_CASH);
		MONEY.set_function("NETWORK_DEDUCT_CASH", LUA_NATIVE_MONEY_NETWORK_DEDUCT_CASH);
		MONEY.set_function("NETWORK_MONEY_CAN_BET", LUA_NATIVE_MONEY_NETWORK_MONEY_CAN_BET);
		MONEY.set_function("NETWORK_CAN_BET", LUA_NATIVE_MONEY_NETWORK_CAN_BET);
		MONEY.set_function("NETWORK_CASINO_CAN_BET", LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET);
		MONEY.set_function("NETWORK_CASINO_CAN_BET_PVC", LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET_PVC);
		MONEY.set_function("NETWORK_CASINO_CAN_BET_AMOUNT", LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BET_AMOUNT);
		MONEY.set_function("NETWORK_CASINO_CAN_BUY_CHIPS_PVC", LUA_NATIVE_MONEY_NETWORK_CASINO_CAN_BUY_CHIPS_PVC);
		MONEY.set_function("NETWORK_CASINO_BUY_CHIPS", LUA_NATIVE_MONEY_NETWORK_CASINO_BUY_CHIPS);
		MONEY.set_function("NETWORK_CASINO_SELL_CHIPS", LUA_NATIVE_MONEY_NETWORK_CASINO_SELL_CHIPS);
		MONEY.set_function("NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE", LUA_NATIVE_MONEY_NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE);
		MONEY.set_function("CAN_PAY_AMOUNT_TO_BOSS", LUA_NATIVE_MONEY_CAN_PAY_AMOUNT_TO_BOSS);
		MONEY.set_function("NETWORK_EARN_FROM_PICKUP", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PICKUP);
		MONEY.set_function("NETWORK_EARN_FROM_CASHING_OUT", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CASHING_OUT);
		MONEY.set_function("NETWORK_EARN_FROM_GANGATTACK_PICKUP", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_GANGATTACK_PICKUP);
		MONEY.set_function("NETWORK_EARN_ASSASSINATE_TARGET_KILLED", LUA_NATIVE_MONEY_NETWORK_EARN_ASSASSINATE_TARGET_KILLED);
		MONEY.set_function("NETWORK_EARN_FROM_ROB_ARMORED_CARS", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_ROB_ARMORED_CARS);
		MONEY.set_function("NETWORK_EARN_FROM_CRATE_DROP", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CRATE_DROP);
		MONEY.set_function("NETWORK_EARN_FROM_BETTING", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BETTING);
		MONEY.set_function("NETWORK_EARN_FROM_JOB", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOB);
		MONEY.set_function("NETWORK_EARN_FROM_JOBX2", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOBX2);
		MONEY.set_function("NETWORK_EARN_FROM_PREMIUM_JOB", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PREMIUM_JOB);
		MONEY.set_function("NETWORK_EARN_FROM_BEND_JOB", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BEND_JOB);
		MONEY.set_function("NETWORK_EARN_FROM_CHALLENGE_WIN", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CHALLENGE_WIN);
		MONEY.set_function("NETWORK_EARN_FROM_BOUNTY", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BOUNTY);
		MONEY.set_function("NETWORK_EARN_FROM_IMPORT_EXPORT", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_IMPORT_EXPORT);
		MONEY.set_function("NETWORK_EARN_FROM_HOLDUPS", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_HOLDUPS);
		MONEY.set_function("NETWORK_EARN_FROM_PROPERTY", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PROPERTY);
		MONEY.set_function("NETWORK_EARN_FROM_AI_TARGET_KILL", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_AI_TARGET_KILL);
		MONEY.set_function("NETWORK_EARN_FROM_NOT_BADSPORT", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_NOT_BADSPORT);
		MONEY.set_function("NETWORK_EARN_FROM_VEHICLE", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_VEHICLE);
		MONEY.set_function("NETWORK_EARN_FROM_PERSONAL_VEHICLE", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_PERSONAL_VEHICLE);
		MONEY.set_function("NETWORK_EARN_FROM_DAILY_OBJECTIVES", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_DAILY_OBJECTIVES);
		MONEY.set_function("NETWORK_EARN_FROM_AMBIENT_JOB", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_AMBIENT_JOB);
		MONEY.set_function("NETWORK_EARN_FROM_JOB_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_JOB_BONUS);
		MONEY.set_function("NETWORK_EARN_FROM_CRIMINAL_MASTERMIND", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CRIMINAL_MASTERMIND);
		MONEY.set_function("NETWORK_EARN_HEIST_AWARD", LUA_NATIVE_MONEY_NETWORK_EARN_HEIST_AWARD);
		MONEY.set_function("NETWORK_EARN_FIRST_TIME_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_FIRST_TIME_BONUS);
		MONEY.set_function("NETWORK_EARN_GOON", LUA_NATIVE_MONEY_NETWORK_EARN_GOON);
		MONEY.set_function("NETWORK_EARN_BOSS", LUA_NATIVE_MONEY_NETWORK_EARN_BOSS);
		MONEY.set_function("NETWORK_EARN_AGENCY", LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY);
		MONEY.set_function("NETWORK_EARN_FROM_WAREHOUSE", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_WAREHOUSE);
		MONEY.set_function("NETWORK_EARN_FROM_CONTRABAND", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CONTRABAND);
		MONEY.set_function("NETWORK_EARN_FROM_DESTROYING_CONTRABAND", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_DESTROYING_CONTRABAND);
		MONEY.set_function("NETWORK_EARN_FROM_SMUGGLER_WORK", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_SMUGGLER_WORK);
		MONEY.set_function("NETWORK_EARN_FROM_HANGAR_TRADE", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_HANGAR_TRADE);
		MONEY.set_function("NETWORK_EARN_PURCHASE_CLUB_HOUSE", LUA_NATIVE_MONEY_NETWORK_EARN_PURCHASE_CLUB_HOUSE);
		MONEY.set_function("NETWORK_EARN_FROM_BUSINESS_PRODUCT", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_PRODUCT);
		MONEY.set_function("NETWORK_EARN_FROM_VEHICLE_EXPORT", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_VEHICLE_EXPORT);
		MONEY.set_function("NETWORK_EARN_SMUGGLER_AGENCY", LUA_NATIVE_MONEY_NETWORK_EARN_SMUGGLER_AGENCY);
		MONEY.set_function("NETWORK_EARN_BOUNTY_HUNTER_REWARD", LUA_NATIVE_MONEY_NETWORK_EARN_BOUNTY_HUNTER_REWARD);
		MONEY.set_function("NETWORK_EARN_FROM_BUSINESS_BATTLE", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_BATTLE);
		MONEY.set_function("NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION);
		MONEY.set_function("NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION);
		MONEY.set_function("NETWORK_EARN_FROM_BUSINESS_HUB_SELL", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_BUSINESS_HUB_SELL);
		MONEY.set_function("NETWORK_EARN_FROM_FMBB_BOSS_WORK", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_FMBB_BOSS_WORK);
		MONEY.set_function("NETWORK_EARN_FMBB_WAGE_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_FMBB_WAGE_BONUS);
		MONEY.set_function("NETWORK_CAN_SPEND_MONEY", LUA_NATIVE_MONEY_NETWORK_CAN_SPEND_MONEY);
		MONEY.set_function("NETWORK_CAN_SPEND_MONEY2", LUA_NATIVE_MONEY_NETWORK_CAN_SPEND_MONEY2);
		MONEY.set_function("NETWORK_BUY_ITEM", LUA_NATIVE_MONEY_NETWORK_BUY_ITEM);
		MONEY.set_function("NETWORK_SPENT_TAXI", LUA_NATIVE_MONEY_NETWORK_SPENT_TAXI);
		MONEY.set_function("NETWORK_PAY_EMPLOYEE_WAGE", LUA_NATIVE_MONEY_NETWORK_PAY_EMPLOYEE_WAGE);
		MONEY.set_function("NETWORK_PAY_MATCH_ENTRY_FEE", LUA_NATIVE_MONEY_NETWORK_PAY_MATCH_ENTRY_FEE);
		MONEY.set_function("NETWORK_SPENT_BETTING", LUA_NATIVE_MONEY_NETWORK_SPENT_BETTING);
		MONEY.set_function("NETWORK_SPENT_WAGER", LUA_NATIVE_MONEY_NETWORK_SPENT_WAGER);
		MONEY.set_function("NETWORK_SPENT_IN_STRIPCLUB", LUA_NATIVE_MONEY_NETWORK_SPENT_IN_STRIPCLUB);
		MONEY.set_function("NETWORK_BUY_HEALTHCARE", LUA_NATIVE_MONEY_NETWORK_BUY_HEALTHCARE);
		MONEY.set_function("NETWORK_BUY_AIRSTRIKE", LUA_NATIVE_MONEY_NETWORK_BUY_AIRSTRIKE);
		MONEY.set_function("NETWORK_BUY_BACKUP_GANG", LUA_NATIVE_MONEY_NETWORK_BUY_BACKUP_GANG);
		MONEY.set_function("NETWORK_BUY_HELI_STRIKE", LUA_NATIVE_MONEY_NETWORK_BUY_HELI_STRIKE);
		MONEY.set_function("NETWORK_SPENT_AMMO_DROP", LUA_NATIVE_MONEY_NETWORK_SPENT_AMMO_DROP);
		MONEY.set_function("NETWORK_BUY_BOUNTY", LUA_NATIVE_MONEY_NETWORK_BUY_BOUNTY);
		MONEY.set_function("NETWORK_BUY_PROPERTY", LUA_NATIVE_MONEY_NETWORK_BUY_PROPERTY);
		MONEY.set_function("NETWORK_BUY_SMOKES", LUA_NATIVE_MONEY_NETWORK_BUY_SMOKES);
		MONEY.set_function("NETWORK_SPENT_HELI_PICKUP", LUA_NATIVE_MONEY_NETWORK_SPENT_HELI_PICKUP);
		MONEY.set_function("NETWORK_SPENT_BOAT_PICKUP", LUA_NATIVE_MONEY_NETWORK_SPENT_BOAT_PICKUP);
		MONEY.set_function("NETWORK_SPENT_BULL_SHARK", LUA_NATIVE_MONEY_NETWORK_SPENT_BULL_SHARK);
		MONEY.set_function("NETWORK_SPENT_CASH_DROP", LUA_NATIVE_MONEY_NETWORK_SPENT_CASH_DROP);
		MONEY.set_function("NETWORK_SPENT_HIRE_MUGGER", LUA_NATIVE_MONEY_NETWORK_SPENT_HIRE_MUGGER);
		MONEY.set_function("NETWORK_SPENT_ROBBED_BY_MUGGER", LUA_NATIVE_MONEY_NETWORK_SPENT_ROBBED_BY_MUGGER);
		MONEY.set_function("NETWORK_SPENT_HIRE_MERCENARY", LUA_NATIVE_MONEY_NETWORK_SPENT_HIRE_MERCENARY);
		MONEY.set_function("NETWORK_SPENT_BUY_WANTEDLEVEL", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_WANTEDLEVEL);
		MONEY.set_function("NETWORK_SPENT_BUY_OFFTHERADAR", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_OFFTHERADAR);
		MONEY.set_function("NETWORK_SPENT_BUY_REVEAL_PLAYERS", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_REVEAL_PLAYERS);
		MONEY.set_function("NETWORK_SPENT_CARWASH", LUA_NATIVE_MONEY_NETWORK_SPENT_CARWASH);
		MONEY.set_function("NETWORK_SPENT_CINEMA", LUA_NATIVE_MONEY_NETWORK_SPENT_CINEMA);
		MONEY.set_function("NETWORK_SPENT_TELESCOPE", LUA_NATIVE_MONEY_NETWORK_SPENT_TELESCOPE);
		MONEY.set_function("NETWORK_SPENT_HOLDUPS", LUA_NATIVE_MONEY_NETWORK_SPENT_HOLDUPS);
		MONEY.set_function("NETWORK_SPENT_BUY_PASSIVE_MODE", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_PASSIVE_MODE);
		MONEY.set_function("NETWORK_SPENT_BANK_INTEREST", LUA_NATIVE_MONEY_NETWORK_SPENT_BANK_INTEREST);
		MONEY.set_function("NETWORK_SPENT_PROSTITUTES", LUA_NATIVE_MONEY_NETWORK_SPENT_PROSTITUTES);
		MONEY.set_function("NETWORK_SPENT_ARREST_BAIL", LUA_NATIVE_MONEY_NETWORK_SPENT_ARREST_BAIL);
		MONEY.set_function("NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM", LUA_NATIVE_MONEY_NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM);
		MONEY.set_function("NETWORK_SPENT_CALL_PLAYER", LUA_NATIVE_MONEY_NETWORK_SPENT_CALL_PLAYER);
		MONEY.set_function("NETWORK_SPENT_BOUNTY", LUA_NATIVE_MONEY_NETWORK_SPENT_BOUNTY);
		MONEY.set_function("NETWORK_SPENT_FROM_ROCKSTAR", LUA_NATIVE_MONEY_NETWORK_SPENT_FROM_ROCKSTAR);
		MONEY.set_function("NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS", LUA_NATIVE_MONEY_NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS);
		MONEY.set_function("PROCESS_CASH_GIFT", LUA_NATIVE_MONEY_PROCESS_CASH_GIFT);
		MONEY.set_function("NETWORK_SPENT_MOVE_SUBMARINE", LUA_NATIVE_MONEY_NETWORK_SPENT_MOVE_SUBMARINE);
		MONEY.set_function("NETWORK_SPENT_PLAYER_HEALTHCARE", LUA_NATIVE_MONEY_NETWORK_SPENT_PLAYER_HEALTHCARE);
		MONEY.set_function("NETWORK_SPENT_NO_COPS", LUA_NATIVE_MONEY_NETWORK_SPENT_NO_COPS);
		MONEY.set_function("NETWORK_SPENT_CARGO_SOURCING", LUA_NATIVE_MONEY_NETWORK_SPENT_CARGO_SOURCING);
		MONEY.set_function("NETWORK_SPENT_REQUEST_JOB", LUA_NATIVE_MONEY_NETWORK_SPENT_REQUEST_JOB);
		MONEY.set_function("NETWORK_SPENT_REQUEST_HEIST", LUA_NATIVE_MONEY_NETWORK_SPENT_REQUEST_HEIST);
		MONEY.set_function("NETWORK_BUY_FAIRGROUND_RIDE", LUA_NATIVE_MONEY_NETWORK_BUY_FAIRGROUND_RIDE);
		MONEY.set_function("NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS", LUA_NATIVE_MONEY_NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS);
		MONEY.set_function("NETWORK_SPENT_JOB_SKIP", LUA_NATIVE_MONEY_NETWORK_SPENT_JOB_SKIP);
		MONEY.set_function("NETWORK_SPENT_BOSS_GOON", LUA_NATIVE_MONEY_NETWORK_SPENT_BOSS_GOON);
		MONEY.set_function("NETWORK_SPEND_GOON", LUA_NATIVE_MONEY_NETWORK_SPEND_GOON);
		MONEY.set_function("NETWORK_SPEND_BOSS", LUA_NATIVE_MONEY_NETWORK_SPEND_BOSS);
		MONEY.set_function("NETWORK_SPENT_MOVE_YACHT", LUA_NATIVE_MONEY_NETWORK_SPENT_MOVE_YACHT);
		MONEY.set_function("NETWORK_SPENT_RENAME_ORGANIZATION", LUA_NATIVE_MONEY_NETWORK_SPENT_RENAME_ORGANIZATION);
		MONEY.set_function("NETWORK_BUY_CONTRABAND_MISSION", LUA_NATIVE_MONEY_NETWORK_BUY_CONTRABAND_MISSION);
		MONEY.set_function("NETWORK_SPENT_PA_SERVICE_HELI", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_HELI);
		MONEY.set_function("NETWORK_SPENT_PA_SERVICE_VEHICLE", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_VEHICLE);
		MONEY.set_function("NETWORK_SPENT_PA_SERVICE_SNACK", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_SNACK);
		MONEY.set_function("NETWORK_SPENT_PA_SERVICE_DANCER", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_DANCER);
		MONEY.set_function("NETWORK_SPENT_PA_SERVICE_IMPOUND", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_SERVICE_IMPOUND);
		MONEY.set_function("NETWORK_SPENT_PA_HELI_PICKUP", LUA_NATIVE_MONEY_NETWORK_SPENT_PA_HELI_PICKUP);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE", LUA_NATIVE_MONEY_NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE);
		MONEY.set_function("NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE", LUA_NATIVE_MONEY_NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE);
		MONEY.set_function("NETWORK_SPENT_JUKEBOX", LUA_NATIVE_MONEY_NETWORK_SPENT_JUKEBOX);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_CLUB_HOUSE", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_CLUB_HOUSE);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_CLUB_HOUSE", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_CLUB_HOUSE);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_TRADE_BUSINESS_PROPERTY", LUA_NATIVE_MONEY_NETWORK_SPENT_TRADE_BUSINESS_PROPERTY);
		MONEY.set_function("NETWORK_SPENT_MC_ABILITY", LUA_NATIVE_MONEY_NETWORK_SPENT_MC_ABILITY);
		MONEY.set_function("NETWORK_SPENT_PAY_BUSINESS_SUPPLIES", LUA_NATIVE_MONEY_NETWORK_SPENT_PAY_BUSINESS_SUPPLIES);
		MONEY.set_function("NETWORK_SPENT_CHANGE_APPEARANCE", LUA_NATIVE_MONEY_NETWORK_SPENT_CHANGE_APPEARANCE);
		MONEY.set_function("NETWORK_SPENT_VEHICLE_EXPORT_MODS", LUA_NATIVE_MONEY_NETWORK_SPENT_VEHICLE_EXPORT_MODS);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_OFFICE_GARAGE", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_OFFICE_GARAGE);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_OFFICE_GARAGE", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_OFFICE_GARAGE);
		MONEY.set_function("NETWORK_SPENT_IMPORT_EXPORT_REPAIR", LUA_NATIVE_MONEY_NETWORK_SPENT_IMPORT_EXPORT_REPAIR);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_HANGAR", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_HANGAR);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_HANGAR", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_HANGAR);
		MONEY.set_function("NETWORK_SPENT_HANGAR_UTILITY_CHARGES", LUA_NATIVE_MONEY_NETWORK_SPENT_HANGAR_UTILITY_CHARGES);
		MONEY.set_function("NETWORK_SPENT_HANGAR_STAFF_CHARGES", LUA_NATIVE_MONEY_NETWORK_SPENT_HANGAR_STAFF_CHARGES);
		MONEY.set_function("NETWORK_SPENT_BUY_TRUCK", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_TRUCK);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_TRUCK", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_TRUCK);
		MONEY.set_function("NETWORK_SPENT_BUY_BUNKER", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_BUNKER);
		MONEY.set_function("NETWORK_SPENT_UPRADE_BUNKER", LUA_NATIVE_MONEY_NETWORK_SPENT_UPRADE_BUNKER);
		MONEY.set_function("NETWORK_EARN_FROM_SELL_BUNKER", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_SELL_BUNKER);
		MONEY.set_function("NETWORK_SPENT_BALLISTIC_EQUIPMENT", LUA_NATIVE_MONEY_NETWORK_SPENT_BALLISTIC_EQUIPMENT);
		MONEY.set_function("NETWORK_EARN_RDR_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_RDR_BONUS);
		MONEY.set_function("NETWORK_EARN_WAGE_PAYMENT", LUA_NATIVE_MONEY_NETWORK_EARN_WAGE_PAYMENT);
		MONEY.set_function("NETWORK_EARN_WAGE_PAYMENT_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_WAGE_PAYMENT_BONUS);
		MONEY.set_function("NETWORK_SPENT_BUY_BASE", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_BASE);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_BASE", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_BASE);
		MONEY.set_function("NETWORK_SPENT_BUY_TILTROTOR", LUA_NATIVE_MONEY_NETWORK_SPENT_BUY_TILTROTOR);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_TILTROTOR", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_TILTROTOR);
		MONEY.set_function("NETWORK_SPENT_EMPLOY_ASSASSINS", LUA_NATIVE_MONEY_NETWORK_SPENT_EMPLOY_ASSASSINS);
		MONEY.set_function("NETWORK_SPEND_GANGOPS_CANNON", LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_CANNON);
		MONEY.set_function("NETWORK_SPEND_GANGOPS_SKIP_MISSION", LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_SKIP_MISSION);
		MONEY.set_function("NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION", LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION);
		MONEY.set_function("NETWORK_EARN_SELL_BASE", LUA_NATIVE_MONEY_NETWORK_EARN_SELL_BASE);
		MONEY.set_function("NETWORK_EARN_TARGET_REFUND", LUA_NATIVE_MONEY_NETWORK_EARN_TARGET_REFUND);
		MONEY.set_function("NETWORK_EARN_GANGOPS_WAGES", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_WAGES);
		MONEY.set_function("NETWORK_EARN_GANGOPS_WAGES_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_WAGES_BONUS);
		MONEY.set_function("NETWORK_EARN_DAR_CHALLENGE", LUA_NATIVE_MONEY_NETWORK_EARN_DAR_CHALLENGE);
		MONEY.set_function("NETWORK_EARN_DOOMSDAY_FINALE_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_DOOMSDAY_FINALE_BONUS);
		MONEY.set_function("NETWORK_EARN_GANGOPS_AWARD", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_AWARD);
		MONEY.set_function("NETWORK_EARN_GANGOPS_ELITE", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_ELITE);
		MONEY.set_function("NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY", LUA_NATIVE_MONEY_NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY);
		MONEY.set_function("NETWORK_SPEND_GANGOPS_START_STRAND", LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_START_STRAND);
		MONEY.set_function("NETWORK_SPEND_GANGOPS_TRIP_SKIP", LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_TRIP_SKIP);
		MONEY.set_function("NETWORK_EARN_GANGOPS_PREP_PARTICIPATION", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_PREP_PARTICIPATION);
		MONEY.set_function("NETWORK_EARN_GANGOPS_SETUP", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_SETUP);
		MONEY.set_function("NETWORK_EARN_GANGOPS_FINALE", LUA_NATIVE_MONEY_NETWORK_EARN_GANGOPS_FINALE);
		MONEY.set_function("NETWORK_SPEND_GANGOPS_REPAIR_COST", LUA_NATIVE_MONEY_NETWORK_SPEND_GANGOPS_REPAIR_COST);
		MONEY.set_function("NETWORK_EARN_NIGHTCLUB", LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB);
		MONEY.set_function("NETWORK_EARN_NIGHTCLUB_DANCING", LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB_DANCING);
		MONEY.set_function("NETWORK_EARN_BB_EVENT_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_BB_EVENT_BONUS);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_HACKER_TRUCK", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_HACKER_TRUCK);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_HACKER_TRUCK", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_HACKER_TRUCK);
		MONEY.set_function("NETWORK_EARN_HACKER_TRUCK", LUA_NATIVE_MONEY_NETWORK_EARN_HACKER_TRUCK);
		MONEY.set_function("NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE", LUA_NATIVE_MONEY_NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE);
		MONEY.set_function("NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE", LUA_NATIVE_MONEY_NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE);
		MONEY.set_function("NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE", LUA_NATIVE_MONEY_NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE);
		MONEY.set_function("NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE", LUA_NATIVE_MONEY_NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE);
		MONEY.set_function("NETWORK_SPENT_RDR_HATCHET_BONUS", LUA_NATIVE_MONEY_NETWORK_SPENT_RDR_HATCHET_BONUS);
		MONEY.set_function("NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE", LUA_NATIVE_MONEY_NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE);
		MONEY.set_function("NETWORK_SPEND_NIGHTCLUB_BAR_DRINK", LUA_NATIVE_MONEY_NETWORK_SPEND_NIGHTCLUB_BAR_DRINK);
		MONEY.set_function("NETWORK_SPEND_BOUNTY_HUNTER_MISSION", LUA_NATIVE_MONEY_NETWORK_SPEND_BOUNTY_HUNTER_MISSION);
		MONEY.set_function("NETWORK_SPENT_REHIRE_DJ", LUA_NATIVE_MONEY_NETWORK_SPENT_REHIRE_DJ);
		MONEY.set_function("NETWORK_SPENT_ARENA_JOIN_SPECTATOR", LUA_NATIVE_MONEY_NETWORK_SPENT_ARENA_JOIN_SPECTATOR);
		MONEY.set_function("NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION", LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION);
		MONEY.set_function("NETWORK_EARN_ARENA_CAREER_PROGRESSION", LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_CAREER_PROGRESSION);
		MONEY.set_function("NETWORK_SPEND_MAKE_IT_RAIN", LUA_NATIVE_MONEY_NETWORK_SPEND_MAKE_IT_RAIN);
		MONEY.set_function("NETWORK_SPEND_BUY_ARENA", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ARENA);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ARENA", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ARENA);
		MONEY.set_function("NETWORK_SPEND_ARENA_SPECTATOR_BOX", LUA_NATIVE_MONEY_NETWORK_SPEND_ARENA_SPECTATOR_BOX);
		MONEY.set_function("NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT", LUA_NATIVE_MONEY_NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT);
		MONEY.set_function("NETWORK_EARN_SPIN_THE_WHEEL_CASH", LUA_NATIVE_MONEY_NETWORK_EARN_SPIN_THE_WHEEL_CASH);
		MONEY.set_function("NETWORK_SPEND_ARENA_PREMIUM", LUA_NATIVE_MONEY_NETWORK_SPEND_ARENA_PREMIUM);
		MONEY.set_function("NETWORK_EARN_ARENA_WAR", LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR);
		MONEY.set_function("NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET", LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET);
		MONEY.set_function("NETWORK_EARN_ARENA_WAR_EVENT_CARGO", LUA_NATIVE_MONEY_NETWORK_EARN_ARENA_WAR_EVENT_CARGO);
		MONEY.set_function("NETWORK_EARN_RC_TIME_TRIAL", LUA_NATIVE_MONEY_NETWORK_EARN_RC_TIME_TRIAL);
		MONEY.set_function("NETWORK_EARN_DAILY_OBJECTIVE_EVENT", LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_OBJECTIVE_EVENT);
		MONEY.set_function("NETWORK_SPEND_CASINO_MEMBERSHIP", LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_MEMBERSHIP);
		MONEY.set_function("NETWORK_SPEND_BUY_CASINO", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_CASINO);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_CASINO", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_CASINO);
		MONEY.set_function("NETWORK_SPEND_CASINO_GENERIC", LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_GENERIC);
		MONEY.set_function("NETWORK_EARN_CASINO_TIME_TRIAL_WIN", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_TIME_TRIAL_WIN);
		MONEY.set_function("NETWORK_EARN_COLLECTABLES_ACTION_FIGURES", LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLES_ACTION_FIGURES);
		MONEY.set_function("NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION);
		MONEY.set_function("NETWORK_EARN_SELL_PRIZE_VEHICLE", LUA_NATIVE_MONEY_NETWORK_EARN_SELL_PRIZE_VEHICLE);
		MONEY.set_function("NETWORK_EARN_CASINO_MISSION_REWARD", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_MISSION_REWARD);
		MONEY.set_function("NETWORK_EARN_CASINO_STORY_MISSION_REWARD", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_STORY_MISSION_REWARD);
		MONEY.set_function("NETWORK_EARN_CASINO_MISSION_PARTICIPATION", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_MISSION_PARTICIPATION);
		MONEY.set_function("NETWORK_EARN_CASINO_AWARD", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_AWARD);
		MONEY.set_function("NETWORK_SPEND_BUY_ARCADE", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ARCADE);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ARCADE", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ARCADE);
		MONEY.set_function("NETWORK_SPEND_CASINO_HEIST", LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_HEIST);
		MONEY.set_function("NETWORK_SPEND_ARCADE_MGMT", LUA_NATIVE_MONEY_NETWORK_SPEND_ARCADE_MGMT);
		MONEY.set_function("NETWORK_SPEND_PLAY_ARCADE", LUA_NATIVE_MONEY_NETWORK_SPEND_PLAY_ARCADE);
		MONEY.set_function("NETWORK_SPEND_ARCADE", LUA_NATIVE_MONEY_NETWORK_SPEND_ARCADE);
		MONEY.set_function("NETWORK_EARN_CASINO_HEIST", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_HEIST);
		MONEY.set_function("NETWORK_EARN_UPGRADE_ARCADE", LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_ARCADE);
		MONEY.set_function("NETWORK_EARN_ARCADE", LUA_NATIVE_MONEY_NETWORK_EARN_ARCADE);
		MONEY.set_function("NETWORK_EARN_COLLECTABLES", LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLES);
		MONEY.set_function("NETWORK_EARN_CHALLENGE", LUA_NATIVE_MONEY_NETWORK_EARN_CHALLENGE);
		MONEY.set_function("NETWORK_EARN_CASINO_HEIST_AWARDS", LUA_NATIVE_MONEY_NETWORK_EARN_CASINO_HEIST_AWARDS);
		MONEY.set_function("NETWORK_EARN_COLLECTABLE_ITEM", LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLE_ITEM);
		MONEY.set_function("NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION", LUA_NATIVE_MONEY_NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION);
		MONEY.set_function("NETWORK_EARN_YATCH_MISSION", LUA_NATIVE_MONEY_NETWORK_EARN_YATCH_MISSION);
		MONEY.set_function("NETWORK_EARN_DISPATCH_CALL", LUA_NATIVE_MONEY_NETWORK_EARN_DISPATCH_CALL);
		MONEY.set_function("NETWORK_SPEND_BEACH_PARTY", LUA_NATIVE_MONEY_NETWORK_SPEND_BEACH_PARTY);
		MONEY.set_function("NETWORK_SPEND_SUBMARINE", LUA_NATIVE_MONEY_NETWORK_SPEND_SUBMARINE);
		MONEY.set_function("NETWORK_SPEND_CASINO_CLUB", LUA_NATIVE_MONEY_NETWORK_SPEND_CASINO_CLUB);
		MONEY.set_function("NETWORK_SPEND_BUY_SUB", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_SUB);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_SUB", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_SUB);
		MONEY.set_function("NETWORK_SPEND_ISLAND_HEIST", LUA_NATIVE_MONEY_NETWORK_SPEND_ISLAND_HEIST);
		MONEY.set_function("NETWORK_EARN_ISLAND_HEIST", LUA_NATIVE_MONEY_NETWORK_EARN_ISLAND_HEIST);
		MONEY.set_function("NETWORK_EARN_BEACH_PARTY_LOST_FOUND", LUA_NATIVE_MONEY_NETWORK_EARN_BEACH_PARTY_LOST_FOUND);
		MONEY.set_function("NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION", LUA_NATIVE_MONEY_NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION);
		MONEY.set_function("NETWORK_SPEND_CAR_CLUB_MEMBERSHIP", LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_MEMBERSHIP);
		MONEY.set_function("NETWORK_SPEND_CAR_CLUB_BAR", LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_BAR);
		MONEY.set_function("NETWORK_SPEND_AUTOSHOP_MODIFY", LUA_NATIVE_MONEY_NETWORK_SPEND_AUTOSHOP_MODIFY);
		MONEY.set_function("NETWORK_SPEND_CAR_CLUB_TAKEOVER", LUA_NATIVE_MONEY_NETWORK_SPEND_CAR_CLUB_TAKEOVER);
		MONEY.set_function("NETWORK_SPEND_BUY_AUTOSHOP", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_AUTOSHOP);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_AUTOSHOP", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_AUTOSHOP);
		MONEY.set_function("NETWORK_EARN_AUTOSHOP_BUSINESS", LUA_NATIVE_MONEY_NETWORK_EARN_AUTOSHOP_BUSINESS);
		MONEY.set_function("NETWORK_EARN_AUTOSHOP_INCOME", LUA_NATIVE_MONEY_NETWORK_EARN_AUTOSHOP_INCOME);
		MONEY.set_function("NETWORK_EARN_CARCLUB_MEMBERSHIP", LUA_NATIVE_MONEY_NETWORK_EARN_CARCLUB_MEMBERSHIP);
		MONEY.set_function("NETWORK_EARN_DAILY_VEHICLE", LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_VEHICLE);
		MONEY.set_function("NETWORK_EARN_DAILY_VEHICLE_BONUS", LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_VEHICLE_BONUS);
		MONEY.set_function("NETWORK_EARN_TUNER_AWARD", LUA_NATIVE_MONEY_NETWORK_EARN_TUNER_AWARD);
		MONEY.set_function("NETWORK_EARN_TUNER_ROBBERY", LUA_NATIVE_MONEY_NETWORK_EARN_TUNER_ROBBERY);
		MONEY.set_function("NETWORK_EARN_UPGRADE_AUTOSHOP", LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_AUTOSHOP);
		MONEY.set_function("NETWORK_SPEND_INTERACTION_MENU_ABILITY", LUA_NATIVE_MONEY_NETWORK_SPEND_INTERACTION_MENU_ABILITY);
		MONEY.set_function("NETWORK_SPEND_SET_COMMON_FIELDS", LUA_NATIVE_MONEY_NETWORK_SPEND_SET_COMMON_FIELDS);
		MONEY.set_function("NETWORK_SPEND_SET_DISCOUNT", LUA_NATIVE_MONEY_NETWORK_SPEND_SET_DISCOUNT);
		MONEY.set_function("NETWORK_SPEND_BUY_AGENCY", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_AGENCY);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_AGENCY", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_AGENCY);
		MONEY.set_function("NETWORK_SPEND_AGENCY", LUA_NATIVE_MONEY_NETWORK_SPEND_AGENCY);
		MONEY.set_function("NETWORK_SPEND_HIDDEN", LUA_NATIVE_MONEY_NETWORK_SPEND_HIDDEN);
		MONEY.set_function("NETWORK_SPEND_SOURCE_BIKE", LUA_NATIVE_MONEY_NETWORK_SPEND_SOURCE_BIKE);
		MONEY.set_function("NETWORK_SPEND_COMP_SUV", LUA_NATIVE_MONEY_NETWORK_SPEND_COMP_SUV);
		MONEY.set_function("NETWORK_SPEND_SUV_FST_TRVL", LUA_NATIVE_MONEY_NETWORK_SPEND_SUV_FST_TRVL);
		MONEY.set_function("NETWORK_SPEND_SUPPLY", LUA_NATIVE_MONEY_NETWORK_SPEND_SUPPLY);
		MONEY.set_function("NETWORK_SPEND_BIKE_SHOP", LUA_NATIVE_MONEY_NETWORK_SPEND_BIKE_SHOP);
		MONEY.set_function("NETWORK_SPEND_VEHICLE_REQUESTED", LUA_NATIVE_MONEY_NETWORK_SPEND_VEHICLE_REQUESTED);
		MONEY.set_function("NETWORK_SPEND_GUNRUNNING", LUA_NATIVE_MONEY_NETWORK_SPEND_GUNRUNNING);
		MONEY.set_function("NETWORK_EARN_AGENCY_SAFE", LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_SAFE);
		MONEY.set_function("NETWORK_EARN_AWARD_CONTRACT", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_CONTRACT);
		MONEY.set_function("NETWORK_EARN_AGENCY_CONTRACT", LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_CONTRACT);
		MONEY.set_function("NETWORK_EARN_AWARD_PHONE", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_PHONE);
		MONEY.set_function("NETWORK_EARN_AGENCY_PHONE", LUA_NATIVE_MONEY_NETWORK_EARN_AGENCY_PHONE);
		MONEY.set_function("NETWORK_EARN_AWARD_FIXER_MISSION", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_FIXER_MISSION);
		MONEY.set_function("NETWORK_EARN_FIXER_PREP", LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_PREP);
		MONEY.set_function("NETWORK_EARN_FIXER_FINALE", LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_FINALE);
		MONEY.set_function("NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP", LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP);
		MONEY.set_function("NETWORK_EARN_AWARD_SHORT_TRIP", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_SHORT_TRIP);
		MONEY.set_function("NETWORK_EARN_FIXER_RIVAL_DELIVERY", LUA_NATIVE_MONEY_NETWORK_EARN_FIXER_RIVAL_DELIVERY);
		MONEY.set_function("NETWORK_EARN_UPGRADE_AGENCY", LUA_NATIVE_MONEY_NETWORK_EARN_UPGRADE_AGENCY);
		MONEY.set_function("NETWORK_SPEND_APARTMENT_UTILITIES", LUA_NATIVE_MONEY_NETWORK_SPEND_APARTMENT_UTILITIES);
		MONEY.set_function("NETWORK_SPEND_BUSINESS_PROPERTY_FEES", LUA_NATIVE_MONEY_NETWORK_SPEND_BUSINESS_PROPERTY_FEES);
		MONEY.set_function("NETWORK_EARN_SIGHTSEEING_REWARD", LUA_NATIVE_MONEY_NETWORK_EARN_SIGHTSEEING_REWARD);
		MONEY.set_function("NETWORK_EARN_BIKER_SHOP", LUA_NATIVE_MONEY_NETWORK_EARN_BIKER_SHOP);
		MONEY.set_function("NETWORK_EARN_BIKER", LUA_NATIVE_MONEY_NETWORK_EARN_BIKER);
		MONEY.set_function("NETWORK_YOHAN_SOURCE_GOODS", LUA_NATIVE_MONEY_NETWORK_YOHAN_SOURCE_GOODS);
		MONEY.set_function("NETWORK_SPEND_BUY_MFGARAGE_", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_MFGARAGE_);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_MFGARAGE_", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_MFGARAGE_);
		MONEY.set_function("NETWORK_SPEND_BUY_SUPPLIES_", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_SUPPLIES_);
		MONEY.set_function("NETWORK_SPEND_BUY_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_SPEND_BUY_ACID_LAB_);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT_", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT_);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR_", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR_);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP_", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP_);
		MONEY.set_function("NETWORK_SPEND_UPGRADE_ACID_LAB_MINES_", LUA_NATIVE_MONEY_NETWORK_SPEND_UPGRADE_ACID_LAB_MINES_);
		MONEY.set_function("NETWORK_SPEND_RENAME_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_SPEND_RENAME_ACID_LAB_);
		MONEY.set_function("NETWORK_SPEND_RENAME_ACID_PRODUCT_", LUA_NATIVE_MONEY_NETWORK_SPEND_RENAME_ACID_PRODUCT_);
		MONEY.set_function("NETWORK_EARN_AWARD_JUGGALO_MISSION_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_JUGGALO_MISSION_);
		MONEY.set_function("NETWORK_EARN_AWARD_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_ACID_LAB_);
		MONEY.set_function("NETWORK_EARN_AWARD_DAILY_STASH_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_DAILY_STASH_);
		MONEY.set_function("NETWORK_EARN_AWARD_DEAD_DROP_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_DEAD_DROP_);
		MONEY.set_function("NETWORK_EARN_AWARD_RANDOM_EVENT_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_RANDOM_EVENT_);
		MONEY.set_function("NETWORK_EARN_AWARD_TAXI_", LUA_NATIVE_MONEY_NETWORK_EARN_AWARD_TAXI_);
		MONEY.set_function("NETWORK_EARN_STREET_DEALER_", LUA_NATIVE_MONEY_NETWORK_EARN_STREET_DEALER_);
		MONEY.set_function("NETWORK_EARN_SELL_ACID_", LUA_NATIVE_MONEY_NETWORK_EARN_SELL_ACID_);
		MONEY.set_function("NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB_);
		MONEY.set_function("NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB_);
		MONEY.set_function("NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB_", LUA_NATIVE_MONEY_NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB_);
		MONEY.set_function("NETWORK_EARN_JUGGALO_STORY_MISSION_", LUA_NATIVE_MONEY_NETWORK_EARN_JUGGALO_STORY_MISSION_);
		MONEY.set_function("NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION_", LUA_NATIVE_MONEY_NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION_);
		MONEY.set_function("NETWORK_EARN_FOOLIGAN_JOB_", LUA_NATIVE_MONEY_NETWORK_EARN_FOOLIGAN_JOB_);
		MONEY.set_function("NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION_", LUA_NATIVE_MONEY_NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION_);
		MONEY.set_function("NETWORK_EARN_TAXI_JOB_", LUA_NATIVE_MONEY_NETWORK_EARN_TAXI_JOB_);
		MONEY.set_function("NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED_", LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED_);
		MONEY.set_function("NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION_", LUA_NATIVE_MONEY_NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION_);
		MONEY.set_function("NETWORK_EARN_AVENGER_", LUA_NATIVE_MONEY_NETWORK_EARN_AVENGER_);
		MONEY.set_function("NETWORK_EARN_SMUGGLER_OPS_", LUA_NATIVE_MONEY_NETWORK_EARN_SMUGGLER_OPS_);
		MONEY.set_function("NETWORK_EARN_BONUS_OBJECTIVE_", LUA_NATIVE_MONEY_NETWORK_EARN_BONUS_OBJECTIVE_);
		MONEY.set_function("NETWORK_EARN_PROGRESS_HUB_", LUA_NATIVE_MONEY_NETWORK_EARN_PROGRESS_HUB_);
		MONEY.set_function("NETWORK_SPENT_AIR_FREIGHT_", LUA_NATIVE_MONEY_NETWORK_SPENT_AIR_FREIGHT_);
		MONEY.set_function("NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP_", LUA_NATIVE_MONEY_NETWORK_SPENT_SKIP_CARGO_SOURCE_SETUP_);
		MONEY.set_function("NETWORK_SPENT_STEALTH_MODULE_", LUA_NATIVE_MONEY_NETWORK_SPENT_STEALTH_MODULE_);
		MONEY.set_function("NETWORK_SPENT_MISSILE_JAMMER_", LUA_NATIVE_MONEY_NETWORK_SPENT_MISSILE_JAMMER_);
		MONEY.set_function("NETWORK_SPENT_GENERIC_", LUA_NATIVE_MONEY_NETWORK_SPENT_GENERIC_);
		MONEY.set_function("NETWORK_EARN_GENERIC_", LUA_NATIVE_MONEY_NETWORK_EARN_GENERIC_);
		MONEY.set_function("NETWORK_CLEAR_TRANSACTION_TELEMETRY_NONCE_", LUA_NATIVE_MONEY_NETWORK_CLEAR_TRANSACTION_TELEMETRY_NONCE_);
		MONEY.set_function("NETWORK_GET_VC_BANK_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_VC_BANK_BALANCE);
		MONEY.set_function("NETWORK_GET_VC_WALLET_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_VC_WALLET_BALANCE);
		MONEY.set_function("NETWORK_GET_VC_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_VC_BALANCE);
		MONEY.set_function("NETWORK_GET_EVC_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_EVC_BALANCE);
		MONEY.set_function("NETWORK_GET_PVC_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_PVC_BALANCE);
		MONEY.set_function("NETWORK_GET_STRING_WALLET_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_STRING_WALLET_BALANCE);
		MONEY.set_function("NETWORK_GET_STRING_BANK_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_STRING_BANK_BALANCE);
		MONEY.set_function("NETWORK_GET_STRING_BANK_WALLET_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_STRING_BANK_WALLET_BALANCE);
		MONEY.set_function("NETWORK_GET_CAN_SPEND_FROM_WALLET", LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_WALLET);
		MONEY.set_function("NETWORK_GET_CAN_SPEND_FROM_BANK", LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_BANK);
		MONEY.set_function("NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET", LUA_NATIVE_MONEY_NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET);
		MONEY.set_function("NETWORK_GET_PVC_TRANSFER_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_PVC_TRANSFER_BALANCE);
		MONEY.set_function("NETWORK_GET_CAN_TRANSFER_CASH", LUA_NATIVE_MONEY_NETWORK_GET_CAN_TRANSFER_CASH);
		MONEY.set_function("NETWORK_CAN_RECEIVE_PLAYER_CASH", LUA_NATIVE_MONEY_NETWORK_CAN_RECEIVE_PLAYER_CASH);
		MONEY.set_function("NETWORK_GET_REMAINING_TRANSFER_BALANCE", LUA_NATIVE_MONEY_NETWORK_GET_REMAINING_TRANSFER_BALANCE);
		MONEY.set_function("WITHDRAW_VC", LUA_NATIVE_MONEY_WITHDRAW_VC);
		MONEY.set_function("DEPOSIT_VC", LUA_NATIVE_MONEY_DEPOSIT_VC);
		MONEY.set_function("HAS_VC_WITHDRAWAL_COMPLETED", LUA_NATIVE_MONEY_HAS_VC_WITHDRAWAL_COMPLETED);
		MONEY.set_function("WAS_VC_WITHDRAWAL_SUCCESSFUL", LUA_NATIVE_MONEY_WAS_VC_WITHDRAWAL_SUCCESSFUL);
	}
}
