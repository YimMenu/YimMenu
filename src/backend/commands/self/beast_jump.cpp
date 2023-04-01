#include "backend/bool_command.hpp"

namespace big
{
	bool_command g_beastjump("beastjump", "Beast Jump", "Allows you to jump as if you were the beast like in the Hunt the Beast event",
	    g.self.beast_jump);
}
