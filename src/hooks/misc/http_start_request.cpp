#include "hooking.hpp"
#include "logger/stack_trace.hpp"
#include "pointers.hpp"
#include "util/string_conversions.hpp"

namespace big
{
    bool hooks::http_start_request(void* request, const char* uri)
    {
        if(strstr(uri, "Bonus"))
        {
            // This is for worst case scenario where a report does slip through the cracks...
            // Lets make it go somewhere it doesn't matter -- don't let the reports reach their servers!
            uri = "https://www.google.com";
        }
        return g_hooking->get_original<hooks::http_start_request>()(request, uri);
    }
}