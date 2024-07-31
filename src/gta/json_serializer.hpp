#pragma once

namespace rage
{
    #pragma pack(push, 1)
    class json_serializer
    {
        uint32_t unk0;   // 0x00
        uint32_t unk1;   // 0x00
        char* buffer;    // 0x08
        uint32_t curlen; // 0x10
        uint32_t maxlen; // 0x14
        uint32_t unk4;   // 0x18
        uint32_t unk5; // 0x1C
        uint8_t flags; // 0x20

    public:
        json_serializer(char* _buffer, uint32_t _length) :
            buffer(_buffer),
            maxlen(_length)
        {
            unk0 = 0;
            unk1   = 0;
            curlen = 0;
            unk4   = 1;
            unk5   = 0;
            flags  = 0;
        }

        inline char* get_string() const
        {
            return buffer;
        }
    };
    static_assert(sizeof(json_serializer) == 0x21); // size is actually 0x28
    #pragma pack(pop)
}