#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

struct globals {
	struct self {
		bool noclip = false;
	};

	struct weapons {
		int custom_weapon = -1;
	};

	self self{};
	weapons weapons{};
};

extern struct globals g;
#endif // !GLOBALS_H