#pragma once

#include "natives.hpp"
#include "ModelAttachment.h"

namespace big
{
	class persist_teleport
	{
	public:
		static void do_presentation_layer();
	private:
		static void save_location(Vector3 position, float rotation, std::string name);
		static void save_location(Ped ped, std::string name);
		static void load_location(std::string name);
		static void delete_location(std::string name);
		static std::vector<std::string> list_locations();
		static void save(model_attachment::model_attachment attachment, std::string name);
		static void save_json(nlohmann::json json);
		static nlohmann::json get_locations_json();
		static std::filesystem::path get_locations_config();
	};
}