#pragma once

#include "backend/bool_command.hpp"

namespace big
{
	class orbital_drone
	{
	private:
		Cam m_cam;
		bool m_lock;
		Entity m_lock_ent;

		Vector3 m_ground_pos;
		Vector3 m_start_pos;

		int m_scaleform;

		bool m_should_tp;
		bool m_initialized;

	public:
		void init();
		void destroy();
		void tick();

		bool initialized()
		{
			return m_initialized;
		};

	private:
		void cam_nav();
		void detect_player(Entity ent);
		void orbital_cannon_explosion();
	};

	inline orbital_drone g_orbital_drone_service;

	namespace cmd
	{
		inline bool_command g_orbital_drone("orbitaldrone", "Toggle Orbital Drone", "Enables/Disables the orbital drone",
		    g.world.orbital_drone.enabled);
	}
}
