#include "wren_vector3.hpp"

namespace big
{
    void wren_vector3::allocate(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector3));
        vec->x = (float)wrenGetSlotDouble(vm, 1);
        vec->y = (float)wrenGetSlotDouble(vm, 2);
        vec->z = (float)wrenGetSlotDouble(vm, 3);
    }

    void wren_vector3::get_x(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->x);
    }

    void wren_vector3::get_y(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->y);
    }

    void wren_vector3::get_z(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->z);
    }

    void wren_vector3::set_x(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->x = (float)wrenGetSlotDouble(vm, 1);
    }

    void wren_vector3::set_y(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->y = (float)wrenGetSlotDouble(vm, 1);
    }

    void wren_vector3::set_z(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->z = (float)wrenGetSlotDouble(vm, 1);
    }

    WrenForeignMethodFn wren_vector3::bind_foreign_method(const char* class_name, const char* signature)
    {
        if (strcmp(class_name, wren_vector3::class_name) == 0)
        {
            if (strcmp(signature, get_x_method_name) == 0)
            {
                return get_x;
            }
            else if (strcmp(signature, get_y_method_name) == 0)
            {
                return get_y;
            }
            else if (strcmp(signature, get_z_method_name) == 0)
            {
                return get_z;
            }
            else if (strcmp(signature, set_x_method_name) == 0)
            {
                return set_x;
            }
            else if (strcmp(signature, set_y_method_name) == 0)
            {
                return set_y;
            }
            else if (strcmp(signature, set_z_method_name) == 0)
            {
                return set_z;
            }
        }

        return nullptr;
    }
}
