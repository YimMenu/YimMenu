#pragma once

namespace memory
{
	class byte_patch;
}

namespace big
{
	// Lua API: Class
	// Name: lua_patch
	// Class representing a in-memory patch.
	class lua_patch
	{
		memory::byte_patch* m_byte_patch;

	public:
		lua_patch(memory::byte_patch* patch);
		~lua_patch();

		// Lua API: Function
		// Class: lua_patch
		// Name: apply
		// Apply the modified value.
		void apply();

		// Lua API: Function
		// Class: lua_patch
		// Name: restore
		// Restore the original value.
		void restore();
	};
}