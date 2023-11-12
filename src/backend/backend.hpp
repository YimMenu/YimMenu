#pragma once

namespace big
{
	class backend
	{
	public:
		static void loop();
		static void vehicles_loop();
		static void misc_loop();
		static void remote_loop();
		static void disable_control_action_loop();
		static void world_loop();
		static void tunables_script();
	};
}
