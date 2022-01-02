#include "main_tabs.hpp"
#include "util/system.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"


namespace big
{
    static ImVec4 base = ImVec4(0.502f, 0.075f, 0.256f, 1.0f);
    static ImVec4 bg = ImVec4(0.200f, 0.220f, 0.270f, 1.0f);
    static ImVec4 text = ImVec4(0.860f, 0.930f, 0.890f, 1.0f);
    static float high_val = 0.8f;
    static float mid_val = 0.5f;
    static float low_val = 0.3f;
    static float window_offset = -0.2f;

    inline ImVec4 make_high(float alpha) {
        ImVec4 res(0, 0, 0, alpha);
        ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
        res.z = high_val;
        ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
        return res;
    }

    inline ImVec4 make_mid(float alpha) {
        ImVec4 res(0, 0, 0, alpha);
        ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
        res.z = mid_val;
        ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
        return res;
    }

    inline ImVec4 make_low(float alpha) {
        ImVec4 res(0, 0, 0, alpha);
        ImGui::ColorConvertRGBtoHSV(base.x, base.y, base.z, res.x, res.y, res.z);
        res.z = low_val;
        ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
        return res;
    }

    inline ImVec4 make_bg(float alpha, float offset = 0.f) {
        ImVec4 res(0, 0, 0, alpha);
        ImGui::ColorConvertRGBtoHSV(bg.x, bg.y, bg.z, res.x, res.y, res.z);
        res.z += offset;
        ImGui::ColorConvertHSVtoRGB(res.x, res.y, res.z, res.x, res.y, res.z);
        return res;
    }

    inline ImVec4 make_text(float alpha) {
        return ImVec4(text.x, text.y, text.z, alpha);
    }
	void tab_main::tab_settings()
	{
		if (ImGui::BeginTabItem("Settings"))
		{
			ImGui::Text("No settings to be modified as of now");

			ImGui::Separator();

			if (ImGui::Button("Reset cooldown"))
			{
				g_fiber_pool->queue_job([] {
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WON_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_WONTIM"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PUR_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_CHIPS_PURTIM"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_MEM_BONUS"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_0"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_GMBLNG_9"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_0"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_TIME_PLYING_9"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_BAN_TIME"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CASINO_GMBLNG_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_GD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_TRHSLD"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_1"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_2"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_3"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_4"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_5"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_6"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_7"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_GMBLNG_L24_8"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_CUR_GMBLNG_HR"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CAS_24H_GMBLNG_PX"), 0, TRUE);
					STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_CHIPS_COL_TIME"), 0, TRUE);
					});
			}

			ImGui::EndTabItem();
           
		}
	}
}