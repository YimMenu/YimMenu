#pragma once

namespace rage
{
    class fwDrawData
    {
    public:
        char pad_0000[904]; //0x0000
        uint8_t m_primary_color; //0x0388
        char pad_0389[3]; //0x0389
        uint8_t m_pearlescent; //0x038C
        char pad_038D[3]; //0x038D
        uint8_t m_secondary_color; //0x0390
        char pad_0391[15]; //0x0391
        uint8_t m_neon_blue; //0x03A0
        uint8_t m_neon_green; //0x03A1
        uint8_t m_neon_red; //0x03A2
        char pad_03A3[15]; //0x03A3
        uint8_t m_spoiler; //0x03B2
        uint8_t m_bumper_front; //0x03B3
        uint8_t m_bumper_rear; //0x03B4
        uint8_t m_sideskirts; //0x03B5
        uint8_t m_exhaust; //0x03B6
        uint8_t m_frame; //0x03B7
        uint8_t m_grille; //0x03B8
        uint8_t m_hood; //0x03B9
        uint8_t m_fenders; //0x03BA
        uint8_t m_bullbars; //0x03BB
        uint8_t m_roof; //0x03BC
        char pad_03BD[3]; //0x03BD
        uint8_t m_ornaments; //0x03C0
        char pad_03C1[1]; //0x03C1
        uint8_t m_dail_design; //0x03C2
        uint8_t m_sunstrips; //0x03C3
        uint8_t m_seats; //0x03C4
        uint8_t m_steering_wheel; //0x03C5
        uint8_t m_column_shifter_levers; //0x03C6
        char pad_03C7[2]; //0x03C7
        uint8_t m_truck_beds; //0x03C9
        char pad_03CA[4]; //0x03CA
        uint8_t m_roll_cages; //0x03CE
        uint8_t m_skid_plate; //0x03CF
        uint8_t m_secondary_light_surrounds; //0x03D0
        uint8_t m_hood_accessories; //0x03D1
        uint8_t m_doors; //0x03D2
        uint8_t m_snorkel; //0x03D3
        uint8_t m_livery; //0x03D4
        char pad_03D5[1]; //0x03D5
        uint8_t m_engine; //0x03D6
        uint8_t m_brakes; //0x03D7
        uint8_t m_transmission; //0x03D8
        uint8_t m_horn; //0x03D9
        uint8_t m_suspension; //0x03DA
        uint8_t m_armor; //0x03DB
        char pad_03DC[1]; //0x03DC
        uint8_t m_turbo; //0x03DD
        char pad_03DE[3]; //0x03DE
        uint8_t m_xenon; //0x03E1
        uint8_t m_tire_design; //0x03E2
        char pad_03E3[16]; //0x03E3
        uint8_t m_truck_bed; //0x03F3
        char pad_03F4[5]; //0x03F4
        uint8_t m_wheel_color; //0x03F9
        char pad_03FA[5]; //0x03FA
        uint8_t m_window; //0x03FF
        char pad_0400[2]; //0x0400
        uint8_t m_neon_left; //0x0402
        uint8_t m_neon_right; //0x0403
        uint8_t m_neon_front; //0x0404
        uint8_t m_neon_rear; //0x0405
    }; //Size: 0x0406
    static_assert(sizeof(fwDrawData) == 0x406);
}
