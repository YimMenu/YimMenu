#pragma once

namespace big
{
    class local_index
    {
    public:
        int version = -1;
        std::string selected_language;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(local_index, version, selected_language)
    
        
    };

}