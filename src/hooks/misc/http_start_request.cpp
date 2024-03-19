#include "hooking/hooking.hpp"
#include "logger/stack_trace.hpp"
#include "pointers.hpp"
#include "util/string_conversions.hpp"

namespace big
{
    bool hooks::http_start_request(void* request, const char* uri)
    {
        if (strstr(uri, "Bonus"))
        {
            // This is for worst case scenario where a report does slip through the cracks...
            // Lets make it go somewhere it doesn't matter -- don't let the reports reach their servers!
			LOG(WARNING) << "Blocked bonus report!";
            uri = "https://0.0.0.0/";
        }
        return g_hooking->get_original<hooks::http_start_request>()(request, uri);
    }
}