#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	static std::vector<float> original_heights;

	struct quad_info
	{
		uint64_t m_quad_pool;
		short m_quad_count;
	};

	struct ocean_quad
	{
	private:
		char pad_0[0x8];

	public:
		int m_opacity;

	private:
		char pad_1[0x8];

	public:
		float m_height;
	};

	class modify_ocean : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			if (auto ocean_quads = reinterpret_cast<quad_info*>(g_pointers->m_gta.m_ocean_quads))
			{
				for (uint64_t i = 0; i < ocean_quads->m_quad_count; i++)
				{
					const auto index = ocean_quads->m_quad_pool + (i * 0x1C);
					const auto quad  = reinterpret_cast<ocean_quad*>(index);

					original_heights.push_back(quad->m_height);
				}
			}
		}

		virtual void on_tick() override
		{
			if (auto ocean_quads = reinterpret_cast<quad_info*>(g_pointers->m_gta.m_ocean_quads))
			{
				for (uint64_t i = 0; i < ocean_quads->m_quad_count; i++)
				{
					const auto index = ocean_quads->m_quad_pool + (i * 0x1C);
					const auto quad  = reinterpret_cast<ocean_quad*>(index);

					// Disable ocean by lowering its height
					if (g.world.ocean.disable_ocean)
						quad->m_height = -10000.f;
					else
						quad->m_height = original_heights[i];

					// Change the ocean's opacity (alpha)
					if (g.world.ocean.ocean_opacity == 100)
						quad->m_opacity = 0x1A1A1A1A;
					else if (!g.world.ocean.ocean_opacity)
						quad->m_opacity = 0x01010101;
					else
						quad->m_opacity = (int)(255 * (float)(g.world.ocean.ocean_opacity / 100.f));
				}
			}
		}

		virtual void on_disable() override
		{
			if (auto ocean_quads = reinterpret_cast<quad_info*>(g_pointers->m_gta.m_ocean_quads))
			{
				for (uint64_t i = 0; i < ocean_quads->m_quad_count; i++)
				{
					const auto index = ocean_quads->m_quad_pool + (i * 0x1C);
					const auto quad  = reinterpret_cast<ocean_quad*>(index);

					quad->m_height  = original_heights[i];
					quad->m_opacity = 0x1A1A1A1A;
				}
			}

			original_heights.clear();
		}
	};

	modify_ocean g_modify_ocean("modifyocean", "BACKEND_LOOPED_WORLD_MODIFY_OCEAN", "BACKEND_LOOPED_WORLD_MODIFY_OCEAN_DESC", g.world.ocean.modify_ocean);
	bool_command g_disable_ocean("disableocean", "BACKEND_LOOPED_WORLD_DISABLE_OCEAN", "BACKEND_LOOPED_WORLD_DISABLE_OCEAN_DESC", g.world.ocean.disable_ocean);
}