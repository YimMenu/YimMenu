#include "file_manager.hpp"
#include "util/teleport.hpp"

namespace big
{
	struct telelocation
	{
		std::string name;
		float x, y, z;
		float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(telelocation, name, x, y, z, yaw, pitch, roll);

	class custom_teleport_service
	{
	public:
		std::map<std::string, std::vector<telelocation>> all_saved_locations;
		bool fetch_saved_locations();
		bool save_new_location(const std::string& category, telelocation t);
		bool delete_saved_location(const std::string& category, const std::string& location_name);
		telelocation* get_saved_location_by_name(std::string);
		std::vector<telelocation> saved_locations_filtered_list(std::string filter = "");

	private:
		std::filesystem::path get_telelocations_file_path();
	};

	inline custom_teleport_service g_custom_teleport_service;
}