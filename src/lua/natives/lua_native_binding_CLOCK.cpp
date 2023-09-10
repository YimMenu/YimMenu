#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_CLOCK_SET_CLOCK_TIME(int hour, int minute, int second)
	{
		CLOCK::SET_CLOCK_TIME(hour, minute, second);
	}

	static void LUA_NATIVE_CLOCK_PAUSE_CLOCK(bool toggle)
	{
		CLOCK::PAUSE_CLOCK(toggle);
	}

	static void LUA_NATIVE_CLOCK_ADVANCE_CLOCK_TIME_TO(int hour, int minute, int second)
	{
		CLOCK::ADVANCE_CLOCK_TIME_TO(hour, minute, second);
	}

	static void LUA_NATIVE_CLOCK_ADD_TO_CLOCK_TIME(int hours, int minutes, int seconds)
	{
		CLOCK::ADD_TO_CLOCK_TIME(hours, minutes, seconds);
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_HOURS()
	{
		auto retval = CLOCK::GET_CLOCK_HOURS();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_MINUTES()
	{
		auto retval = CLOCK::GET_CLOCK_MINUTES();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_SECONDS()
	{
		auto retval = CLOCK::GET_CLOCK_SECONDS();
		return retval;
	}

	static void LUA_NATIVE_CLOCK_SET_CLOCK_DATE(int day, int month, int year)
	{
		CLOCK::SET_CLOCK_DATE(day, month, year);
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_DAY_OF_WEEK()
	{
		auto retval = CLOCK::GET_CLOCK_DAY_OF_WEEK();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_DAY_OF_MONTH()
	{
		auto retval = CLOCK::GET_CLOCK_DAY_OF_MONTH();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_MONTH()
	{
		auto retval = CLOCK::GET_CLOCK_MONTH();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_CLOCK_YEAR()
	{
		auto retval = CLOCK::GET_CLOCK_YEAR();
		return retval;
	}

	static int LUA_NATIVE_CLOCK_GET_MILLISECONDS_PER_GAME_MINUTE()
	{
		auto retval = CLOCK::GET_MILLISECONDS_PER_GAME_MINUTE();
		return retval;
	}

	static std::tuple<int, int, int, int, int, int> LUA_NATIVE_CLOCK_GET_POSIX_TIME(int year, int month, int day, int hour, int minute, int second)
	{
		std::tuple<int, int, int, int, int, int> return_values;
		CLOCK::GET_POSIX_TIME(&year, &month, &day, &hour, &minute, &second);
		std::get<0>(return_values) = year;
		std::get<1>(return_values) = month;
		std::get<2>(return_values) = day;
		std::get<3>(return_values) = hour;
		std::get<4>(return_values) = minute;
		std::get<5>(return_values) = second;

		return return_values;
	}

	static std::tuple<int, int, int, int, int, int> LUA_NATIVE_CLOCK_GET_UTC_TIME(int year, int month, int day, int hour, int minute, int second)
	{
		std::tuple<int, int, int, int, int, int> return_values;
		CLOCK::GET_UTC_TIME(&year, &month, &day, &hour, &minute, &second);
		std::get<0>(return_values) = year;
		std::get<1>(return_values) = month;
		std::get<2>(return_values) = day;
		std::get<3>(return_values) = hour;
		std::get<4>(return_values) = minute;
		std::get<5>(return_values) = second;

		return return_values;
	}

	static std::tuple<int, int, int, int, int, int> LUA_NATIVE_CLOCK_GET_LOCAL_TIME(int year, int month, int day, int hour, int minute, int second)
	{
		std::tuple<int, int, int, int, int, int> return_values;
		CLOCK::GET_LOCAL_TIME(&year, &month, &day, &hour, &minute, &second);
		std::get<0>(return_values) = year;
		std::get<1>(return_values) = month;
		std::get<2>(return_values) = day;
		std::get<3>(return_values) = hour;
		std::get<4>(return_values) = minute;
		std::get<5>(return_values) = second;

		return return_values;
	}

	void init_native_binding_CLOCK(sol::state& L)
	{
		auto CLOCK = L["CLOCK"].get_or_create<sol::table>();
		CLOCK.set_function("SET_CLOCK_TIME", LUA_NATIVE_CLOCK_SET_CLOCK_TIME);
		CLOCK.set_function("PAUSE_CLOCK", LUA_NATIVE_CLOCK_PAUSE_CLOCK);
		CLOCK.set_function("ADVANCE_CLOCK_TIME_TO", LUA_NATIVE_CLOCK_ADVANCE_CLOCK_TIME_TO);
		CLOCK.set_function("ADD_TO_CLOCK_TIME", LUA_NATIVE_CLOCK_ADD_TO_CLOCK_TIME);
		CLOCK.set_function("GET_CLOCK_HOURS", LUA_NATIVE_CLOCK_GET_CLOCK_HOURS);
		CLOCK.set_function("GET_CLOCK_MINUTES", LUA_NATIVE_CLOCK_GET_CLOCK_MINUTES);
		CLOCK.set_function("GET_CLOCK_SECONDS", LUA_NATIVE_CLOCK_GET_CLOCK_SECONDS);
		CLOCK.set_function("SET_CLOCK_DATE", LUA_NATIVE_CLOCK_SET_CLOCK_DATE);
		CLOCK.set_function("GET_CLOCK_DAY_OF_WEEK", LUA_NATIVE_CLOCK_GET_CLOCK_DAY_OF_WEEK);
		CLOCK.set_function("GET_CLOCK_DAY_OF_MONTH", LUA_NATIVE_CLOCK_GET_CLOCK_DAY_OF_MONTH);
		CLOCK.set_function("GET_CLOCK_MONTH", LUA_NATIVE_CLOCK_GET_CLOCK_MONTH);
		CLOCK.set_function("GET_CLOCK_YEAR", LUA_NATIVE_CLOCK_GET_CLOCK_YEAR);
		CLOCK.set_function("GET_MILLISECONDS_PER_GAME_MINUTE", LUA_NATIVE_CLOCK_GET_MILLISECONDS_PER_GAME_MINUTE);
		CLOCK.set_function("GET_POSIX_TIME", LUA_NATIVE_CLOCK_GET_POSIX_TIME);
		CLOCK.set_function("GET_UTC_TIME", LUA_NATIVE_CLOCK_GET_UTC_TIME);
		CLOCK.set_function("GET_LOCAL_TIME", LUA_NATIVE_CLOCK_GET_LOCAL_TIME);
	}
}
