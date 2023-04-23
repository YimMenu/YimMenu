#pragma once
#include "common.hpp"

namespace big
{
	class exception_handler final
	{
	public:
		exception_handler();
		virtual ~exception_handler();

	private:
		void* m_exception_handler;
		std::uint32_t m_old_error_mode;
	};

	extern LONG vectored_exception_handler(EXCEPTION_POINTERS* exception_info);
}