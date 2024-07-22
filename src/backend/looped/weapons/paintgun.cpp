#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_paint_gun()
	{
		static Vector3 col = {0, 0, 0};
		static float red = 255.f, green = 0.f, blue = 0.f;

		if (g.weapons.paintgun.rainbow)
		{
			if (red > 0 && blue == 0)
			{
				green += red;
				red -= g.weapons.paintgun.speed;
			}
			if (green > 0 && red == 0)
			{
				blue += g.weapons.paintgun.speed;
				green -= g.weapons.paintgun.speed;
			}
			if (blue > 0 && green == 0)
			{
				red += g.weapons.paintgun.speed;
				blue -= g.weapons.paintgun.speed;
			}
			red   = std::clamp(red, 0.f, 255.f);
			green = std::clamp(green, 0.f, 255.f);
			blue  = std::clamp(blue, 0.f, 255.f);

		}

		if (g.weapons.paintgun.rainbow)
			col = {red, green, blue};
		else
			col = {g.weapons.paintgun.col[0], g.weapons.paintgun.col[1], g.weapons.paintgun.col[2]};

		if (g.weapons.custom_weapon == CustomWeapon::PAINT_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			Vector3 c; entity::raycast(&c);

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					GRAPHICS::ADD_DECAL((int)DecalTypes::splatters_paint,
					    c.x,
					    c.y,
					    c.z,
					    0,  //true
					    0,  //true
					    -1, //true
					    0,
					    1.f,
					    0.f, // always 0
					    0.5f, //size x
					    0.4f, //size y
					    col.x,
					    col.y,
					    col.z,
					    g.weapons.paintgun.col[3],
					    -1,
					    true,
					    false,
					    false);
				}
			}
		}
	}
}