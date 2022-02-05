#pragma once

namespace rage
{
    template<typename T>
    union vector3
    {
        T data[3];
        struct { T x, y, z; };
    };

    typedef vector3<float> fvector3;
}
