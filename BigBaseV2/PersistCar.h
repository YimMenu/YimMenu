#pragma once

#include "natives.hpp"
#include "ModelAttachment.h"

namespace big
{
	class persist_car
	{
	public:
		static void save_vehicle(Vehicle vehicle, std::string file_name);
		static Vehicle load_vehicle(std::string file_name);
		static std::vector<std::string> list_files();
		static Vehicle clone_ped_car(Ped ped, Vehicle vehicle);
		static void do_presentation_layer();
	private:
		static Vehicle spawn_vehicle_full(nlohmann::json vehicle_json, Ped ped);
		static Vehicle spawn_vehicle(nlohmann::json vehicle_json, Ped ped);
		static Vehicle spawn_vehicle_json(nlohmann::json vehicle_json, Ped ped);
		static nlohmann::json get_full_vehicle_json(Vehicle vehicle);
		static model_attachment::model_attachment get_model_attachment(Vehicle vehicle, Object object);
		static nlohmann::json get_model_attachments(Vehicle vehicle, bool is_towed_vehicle = false);
		static nlohmann::json get_vehicle_attachents(Vehicle vehicle);
		static nlohmann::json get_vehicle_json(Vehicle vehicle);
		static std::filesystem::path check_vehicle_folder();
		static void do_save_vehicle(char* vehicle_file_name_input);
		static void do_load_vehicle(std::string& selected_vehicle_file);
	};
}

enum VehicleModType
{
	MOD_SPOILERS,
	MOD_FRONTBUMPER,
	MOD_REARBUMPER,
	MOD_SIDESKIRT,
	MOD_EXHAUST,
	MOD_FRAME,
	MOD_GRILLE,
	MOD_HOOD,
	MOD_FENDER,
	MOD_RIGHTFENDER,
	MOD_ROOF,
	MOD_ENGINE,
	MOD_BRAKES,
	MOD_TRANSMISSION,
	MOD_HORNS,
	MOD_SUSPENSION,
	MOD_ARMOR,
	MOD_FRONTWHEEL = 23,
	MOD_REARWHEEL,
	MOD_PLATEHOLDER,
	MOD_VANITYPLATES,
	MOD_TRIMDESIGN,
	MOD_ORNAMENTS,
	MOD_DASHBOARD,
	MOD_DIALDESIGN,
	MOD_DOORSPEAKERS,
	MOD_SEATS,
	MOD_STEERINGWHEELS,
	MOD_COLUMNSHIFTERLEVERS,
	MOD_PLAQUES,
	MOD_SPEAKERS,
	MOD_TRUNK,
	MOD_HYDRAULICS,
	MOD_ENGINEBLOCK,
	MOD_AIRFILTER,
	MOD_STRUTS,
	MOD_ARCHCOVER,
	MOD_AERIALS,
	MOD_TRIM,
	MOD_TANK,
	MOD_WINDOWS,
	MOD_DOORS,
	MOD_LIVERY
};

static const char* mod_names[] = { "MOD_SPOILERS", "MOD_FRONTBUMPER", "MOD_REARBUMPER", "MOD_SIDESKIRT", "MOD_EXHAUST", "MOD_FRAME", "MOD_GRILLE", "MOD_HOOD", "MOD_FENDER", "MOD_RIGHTFENDER", "MOD_ROOF", "MOD_ENGINE", "MOD_BRAKES", "MOD_TRANSMISSION", "MOD_HORNS", "MOD_SUSPENSION", "MOD_ARMOR", "", "MOD_TURBO", "", "MOD_TIRESMOKE", "", "MOD_XENONHEADLIGHTS", "MOD_FRONTWHEEL", "MOD_REARWHEEL", "MOD_PLATEHOLDER", "MOD_VANITYPLATES", "MOD_TRIMDESIGN", "MOD_ORNAMENTS", "MOD_DASHBOARD", "MOD_DIALDESIGN", "MOD_DOORSPEAKERS", "MOD_SEATS", "MOD_STEERINGWHEELS", "MOD_COLUMNSHIFTERLEVERS", "MOD_PLAQUES", "MOD_SPEAKERS", "MOD_TRUNK", "MOD_HYDRAULICS", "MOD_ENGINEBLOCK", "MOD_AIRFILTER", "MOD_STRUTS", "MOD_ARCHCOVER", "MOD_AERIALS", "MOD_TRIM", "MOD_TANK", "MOD_WINDOWS", "", "MOD_LIVERY" };

enum VehicleToggleModType
{
	MOD_TURBO = 18,
	MOD_TIRESMOKE = 20,
	MOD_XENONHEADLIGHTS = 22
};

enum VehicleModHorns
{
	HORN_STOCK = -1,
	HORN_TRUCK,
	HORN_POLICE,
	HORN_CLOWN,
	HORN_MUSICAL1,
	HORN_MUSICAL2,
	HORN_MUSICAL3,
	HORN_MUSICAL4,
	HORN_MUSICAL5,
	HORN_SADTROMBONE,
	HORN_CLASSICAL1,
	HORN_CLASSICAL2,
	HORN_CLASSICAL3,
	HORN_CLASSICAL4,
	HORN_CLASSICAL5,
	HORN_CLASSICAL6,
	HORN_CLASSICAL7,
	HORN_SCALEDO,
	HORN_SCALERE,
	HORN_SCALEMI,
	HORN_SCALEFA,
	HORN_SCALESOL,
	HORN_SCALELA,
	HORN_SCALETI,
	HORN_SCALEDO_HIGH,
	HORN_JAZZ1,
	HORN_JAZZ2,
	HORN_JAZZ3,
	HORN_JAZZLOOP,
	HORN_STARSPANGBAN1,
	HORN_STARSPANGBAN2,
	HORN_STARSPANGBAN3,
	HORN_STARSPANGBAN4,
	HORN_CLASSICAL_LOOP,
	HORN_CLASSICAL,
	HORN_CLASSICAL_LOOP2,
	HORN_CLASSICAL_HORN_LOOP,
	HORN_CLASSICAL_HORN_LOOP2,
	HORN_CLASSICAL_HORN_LOOP3,
	HORN_HALLOWEEN_LOOP,
	HORN_HALLOWEEN,
	HORN_HALLOWEEN2_LOOP,
	HORN_HALLOWEEN2,
	HORN_SANANDREAS_LOOP,
	HORN_SANANDREAS,
	HORN_LIBERTYCITY_LOOP,
	HORN_LIBERTYCITY,
	HORN_XMAS,
	HORN_XMAS_BACKGROUND,
	HORN_XMAS2,
	HORN_XMAS2_BACKGROUND,
	HORN_XMAS3,
	HORN_XMAS3_BACKGROUND
};

enum VehicleAddonLevel
{
	MOD_INDEX_OFF = -1,
	MOD_INDEX_ONE, //To determine mod index, look at the mod menu in LSC, the first item is MOD_INDEX_ONE. Count down to the item you want. Stock counts as OFF.
	MOD_INDEX_TWO,
	MOD_INDEX_THREE,
	MOD_INDEX_FOUR,
	MOD_INDEX_FIVE,
	MOD_INDEX_SIX,
	MOD_INDEX_SEVEN,
	MOD_INDEX_EIGHT,
	MOD_INDEX_NINE
};

enum NeonLightLocations
{
	NEON_LEFT,
	NEON_RIGHT,
	NEON_FRONT,
	NEON_BACK
};