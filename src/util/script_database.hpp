#include <string>
#include <unordered_map>

namespace big
{
	enum class protection_status
	{
		ALLOWED_NOTIFY,
		BLOCK_ALWAYS,
		BLOCK_IN_FREEMODE
	};

	struct script_info
	{
		std::string name;
		protection_status status;
	};

	class script_protection_DB
	{
	public:
		script_protection_DB()
		{
			initialize_script_DB();
		}

		protection_status get_protection_status(int scriptId) const
		{
			auto it = m_script_map.find(scriptId);
			if (it != m_script_map.end())
			{
				return it->second.status;
			}
			return protection_status::ALLOWED_NOTIFY;
		}

		// Could be useful for debugging someday...
		std::string get_script_name(int scriptId) const
		{
			auto it = m_script_map.find(scriptId);
			if (it != m_script_map.end())
			{
				return it->second.name;
			}
			return "";
		}

	private:
		std::unordered_map<int, script_info> m_script_map;

		void initialize_script_DB()
		{
			// Please try to keep this in numerical order for code readability
			// Last script ID update 5/5/2024
			m_script_map = {{9, {"AM_Darts", protection_status::BLOCK_ALWAYS}},
			    {17, {"AM_PI_MENU", protection_status::BLOCK_ALWAYS}},
			    {20, {"fm_intro", protection_status::BLOCK_ALWAYS}},
			    {212, {"golf_mp", protection_status::BLOCK_IN_FREEMODE}},
			    {214, {"tennis_network_mp", protection_status::BLOCK_IN_FREEMODE}},
			    {215, {"Pilot_School_MP", protection_status::BLOCK_ALWAYS}},
			    {216, {"FM_Impromptu_DM_Controler", protection_status::BLOCK_IN_FREEMODE}},
			    {218, {"fm_deathmatch_controler", protection_status::BLOCK_IN_FREEMODE}},
			    {221, {"FM_Race_Controler", protection_status::BLOCK_IN_FREEMODE}},
			    {222, {"FM_Horde_Controler", protection_status::BLOCK_IN_FREEMODE}},
			    {224, {"am_darts_apartment", protection_status::BLOCK_ALWAYS}},
			    {226, {"grid_arcade_cabinet", protection_status::BLOCK_ALWAYS}},
			    {227, {"scroll_arcade_cabinet", protection_status::BLOCK_ALWAYS}},
			    {228, {"example_arcade", protection_status::BLOCK_ALWAYS}},
			    {229, {"road_arcade", protection_status::BLOCK_ALWAYS}},
			    {230, {"gunslinger_arcade", protection_status::BLOCK_ALWAYS}}, // Badlands Revenge II?
			    {231, {"wizard_arcade", protection_status::BLOCK_ALWAYS}},
			    {235, {"ggsm_arcade", protection_status::BLOCK_ALWAYS}}, // Space Monkey?
			    {236, {"puzzle", protection_status::BLOCK_ALWAYS}},      // Qub3d?
			    {237, {"camhedz_arcade", protection_status::BLOCK_ALWAYS}},
			    {238, {"SCTV", protection_status::BLOCK_ALWAYS}}};
		}
	};
}
