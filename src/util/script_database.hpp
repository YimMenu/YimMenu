#include <unordered_map>
#include <string>

namespace big
{
    enum class ProtectionStatus
    {
        ALLOWED,
        BLOCK_ALWAYS,
        BLOCK_IN_FREEMODE // Renamed from BLOCK_IN_FM
    };

    struct ScriptInfo
    {
        std::string name;
        ProtectionStatus status;
    };

    class ScriptProtectionDB
    {
    public:
        ScriptProtectionDB()
        {
            initialize_script_DB();
        }

        ProtectionStatus get_protection_status(int scriptId) const
        {
            auto it = m_scriptMap.find(scriptId);
            if (it != m_scriptMap.end())
            {
                return it->second.status;
            }
            return ProtectionStatus::ALLOWED;
        }

        // Could be useful for debugging someday...
        std::string get_script_name(int scriptId) const
        {
            auto it = m_scriptMap.find(scriptId);
            if (it != m_scriptMap.end())
            {
                return it->second.name;
            }
            return "";
        }

    private:
        std::unordered_map<int, ScriptInfo> m_scriptMap;

        void initialize_script_DB()
        {
            // Please try to keep this in numerical order for code readability
            // Last script ID update 5/5/2024
            m_scriptMap = {
                {9, {"AM_Darts", ProtectionStatus::BLOCK_ALWAYS}},
                {17, {"AM_PI_MENU", ProtectionStatus::BLOCK_ALWAYS}},
                {20, {"fm_intro", ProtectionStatus::BLOCK_ALWAYS}},
                {212, {"golf_mp", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {214, {"tennis_network_mp", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {215, {"Pilot_School_MP", ProtectionStatus::BLOCK_ALWAYS}},
                {216, {"FM_Impromptu_DM_Controler", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {218, {"fm_deathmatch_controler", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {221, {"FM_Race_Controler", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {222, {"FM_Horde_Controler", ProtectionStatus::BLOCK_IN_FREEMODE}},
                {224, {"am_darts_apartment", ProtectionStatus::BLOCK_ALWAYS}},
                {226, {"grid_arcade_cabinet", ProtectionStatus::BLOCK_ALWAYS}},
                {227, {"scroll_arcade_cabinet", ProtectionStatus::BLOCK_ALWAYS}},
			    {228, {"example_arcade", ProtectionStatus::BLOCK_ALWAYS}},
                {229, {"road_arcade", ProtectionStatus::BLOCK_ALWAYS}},
                {230, {"gunslinger_arcade", ProtectionStatus::BLOCK_ALWAYS}}, // Badlands Revenge II?
                {231, {"wizard_arcade", ProtectionStatus::BLOCK_ALWAYS}},
                {235, {"ggsm_arcade", ProtectionStatus::BLOCK_ALWAYS}}, // Space Monkey?
                {236, {"puzzle", ProtectionStatus::BLOCK_ALWAYS}},
                {237, {"camhedz_arcade", ProtectionStatus::BLOCK_ALWAYS}},
                {238, {"SCTV", ProtectionStatus::BLOCK_ALWAYS}}
            };
        }
    };
}
