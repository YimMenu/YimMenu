#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class free_cam : public looped_command
	{
		using looped_command::looped_command;

		float speed = 0.5f;
		float mult  = 0.f;

		Cam camera = -1;
		Vector3 position;
		Vector3 rotation;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline free_cam g_free_cam("freecam", "Freecam", "Allows you to move your camera freely?", g.self.free_cam);
	}
}
