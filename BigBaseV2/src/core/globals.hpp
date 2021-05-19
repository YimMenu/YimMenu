#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

struct globals {
	struct self {
		bool noclip = false;
	};

	self self{};
};

extern struct globals g;
#endif // !GLOBALS_H