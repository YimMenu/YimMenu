#pragma once

namespace big
{

	class outfit_service
	{
	public:
		struct head_blend_data 
		{
		public:
			alignas(8) int shape_first_id  = -1;
			alignas(8) int shape_second_id = -1;
			alignas(8) int shape_third_id  = -1;
			alignas(8) int skin_first_id   = -1;
			alignas(8) int skin_second_id  = -1;
			alignas(8) int skin_third_id   = -1;
			alignas(8) float shape_mix     = FLT_MAX;
			alignas(8) float skin_mix      = FLT_MAX;
			alignas(8) float third_mix     = FLT_MAX;
			alignas(8) BOOL is_parent      = FALSE;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(head_blend_data, shape_first_id, shape_second_id, shape_third_id, skin_first_id, skin_second_id, skin_third_id, shape_mix, skin_mix, third_mix, is_parent);
		};
		static_assert(sizeof(head_blend_data) == 0x50, "head_blend_data is not sized properly.");

		static void apply_outfit(nlohmann::json, bool);
		static void save_outfit(std::string);
	};
}