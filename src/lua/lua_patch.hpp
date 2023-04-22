#pragma once

namespace memory
{
	class byte_patch;
}

namespace big
{
	class lua_patch
	{
		memory::byte_patch* m_byte_patch;

	public:
		lua_patch(memory::byte_patch* patch);
		~lua_patch();

		void apply();
		void restore();
	};
}