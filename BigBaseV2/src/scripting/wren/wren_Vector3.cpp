#include "wren_Vector3.hpp"

namespace big
{
    void wren_Vector3::allocate(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector3));
        vec->x = (float)wrenGetSlotDouble(vm, 1);
        vec->y = (float)wrenGetSlotDouble(vm, 2);
        vec->z = (float)wrenGetSlotDouble(vm, 3);
    }

    void wren_Vector3::get_x(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->x);
    }

    void wren_Vector3::get_y(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->y);
    }

    void wren_Vector3::get_z(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        wrenSetSlotDouble(vm, 0, (double)vec->z);
    }

    void wren_Vector3::set_x(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->x = (float)wrenGetSlotDouble(vm, 1);
    }

    void wren_Vector3::set_y(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->y = (float)wrenGetSlotDouble(vm, 1);
    }

    void wren_Vector3::set_z(WrenVM* vm)
    {
        Vector3* vec = (Vector3*)wrenGetSlotForeign(vm, 0);
        vec->z = (float)wrenGetSlotDouble(vm, 1);
    }
}
