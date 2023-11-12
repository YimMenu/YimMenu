#pragma once
#include "bad_players.hpp"

#include "thread_pool.hpp"

namespace bad_players_nm
{
	std::map<uint64_t, bad_player> bad_players_list;

	void load_blocked_list()
	{
		try
		{
			if (auto filePath = getSavedFilePath(); std::filesystem::exists(filePath))
			{
				std::ifstream f(filePath);

				if (f.is_open())
				{
					bad_players_list = json::parse(f);
					f.close();
				}
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << e.what();
		}
	}

	void save_blocked_list()
	{
		std::map<uint64_t, bad_player> filtered_map;
		for (const auto& entry : bad_players_list)
			if (entry.second.block_join)
				filtered_map[entry.first] = entry.second;

		try
		{
			json j = filtered_map;
			if (std::ofstream o(getSavedFilePath()); o.is_open())
			{
				o << std::setw(4) << j << std::endl;
				o.close();
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << e.what();
		}
	}
}