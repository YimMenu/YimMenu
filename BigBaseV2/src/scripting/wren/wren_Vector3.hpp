#pragma once
#include "wren.hpp"

namespace big
{
    class wren_Vector3
    {
    public:
        static void allocate(WrenVM* vm);

        static void get_x(WrenVM* vm);
        static void get_y(WrenVM* vm);
        static void get_z(WrenVM* vm);

        static void set_x(WrenVM* vm);
        static void set_y(WrenVM* vm);
        static void set_z(WrenVM* vm);
    };
}
