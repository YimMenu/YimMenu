#pragma once
#include "wren.hpp"

namespace big
{
    class wren_vector3
    {
        static constexpr auto get_x_method_name = "x";
        static void get_x(WrenVM* vm);

        static constexpr auto get_y_method_name = "y";
        static void get_y(WrenVM* vm);

        static constexpr auto get_z_method_name = "z";
        static void get_z(WrenVM* vm);

        static constexpr auto set_x_method_name = "x=(_)";
        static void set_x(WrenVM* vm);

        static constexpr auto set_y_method_name = "y=(_)";
        static void set_y(WrenVM* vm);

        static constexpr auto set_z_method_name = "z=(_)";
        static void set_z(WrenVM* vm);

    public:
        static constexpr auto class_name = "Vector3";

        static void allocate(WrenVM* vm);

        static WrenForeignMethodFn bind_foreign_method(const char* class_name, const char* signature);
    };
}
