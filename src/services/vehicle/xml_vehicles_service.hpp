#include "pugixml.hpp"

#include <filesystem>
#include <iostream>

namespace big
{
	class xml_vehicles_service
	{
	public:
		xml_vehicles_service();
		~xml_vehicles_service();
		std::map<std::string, pugi::xml_document> m_all_xml_vehicles;

		void fetch_xml_files();
		Vehicle spawn_from_xml(pugi::xml_document&, Vector3);
	};

	inline xml_vehicles_service* g_xml_vehicles_service;
}
