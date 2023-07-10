#pragma once

namespace big::debug
{
	extern void globals();
	extern void locals();
	extern void logs();
	extern void misc();
	extern void script_events();
	extern void scripts();
	extern void threads();
	extern void animations(std::string* dict = nullptr, std::string* anim = nullptr); // Can be used to retrieve animations

	extern void main();
}