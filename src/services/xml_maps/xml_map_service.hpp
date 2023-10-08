#include "pugixml.hpp"
#include <filesystem>
#include <iostream>


namespace big
{
    class xml_map_service
    {
    public:
        xml_map_service();
        ~xml_map_service();
        std::map<std::string, pugi::xml_document> m_all_xml_maps;

        void fetch_xml_files();
        void spawn_from_xml(pugi::xml_document&);
    };

    inline xml_map_service* g_xml_map_service;
}