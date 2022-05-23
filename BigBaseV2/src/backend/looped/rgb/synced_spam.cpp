#include "backend/looped/looped.hpp"
#include "script.hpp"

namespace big
{
    void looped::rgb_synced_spasm()
    {
        auto delay = std::chrono::milliseconds(1000 - (g->rgb.speed * 100));

        if (g->rgb.spasm)
        {
            g->rgb.r = rand() % 256;
            g->rgb.g = rand() % 256;
            g->rgb.b = rand() % 256;
        }
        script::get_current()->yield(delay);
    }
}
