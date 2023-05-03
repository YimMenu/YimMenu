#include "backend/bool_command.hpp"

namespace big::cmd
{
	inline bool_command g_super_jump("superjump", "Super Jump", "Jump really high", g.self.super_jump);
}
