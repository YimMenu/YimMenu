#pragma once
#include "common.hpp"
#include "file_manager.hpp"

#include <AsyncLogger/Logger.hpp>
using namespace al;

namespace big
{
#define ADD_COLOR_TO_STREAM(color) "\x1b[" << int(color) << "m"
#define RESET_STREAM_COLOR "\x1b[" << int(LogColor::RESET) << "m"
#define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase

	enum class LogColor
	{
		RESET,
		WHITE   = 97,
		CYAN    = 36,
		MAGENTA = 35,
		BLUE    = 34,
		GREEN   = 32,
		YELLOW  = 33,
		RED     = 31,
		BLACK   = 30
	};

	class logger final
	{
	public:
		logger(std::string_view console_title, file file, bool attach_console = true);
		virtual ~logger();

		void initialize();
		void destroy();

	private:
		void create_backup();

		void open_outstreams();
		void close_outstreams();

		void format_console(const LogMessagePtr msg);
		void format_console_simple(const LogMessagePtr msg);
		void format_file(const LogMessagePtr msg);

	private:
		bool m_attach_console;
		bool m_did_console_exist;

		void (logger::*m_console_logger)(const LogMessagePtr msg);

		std::string_view m_console_title;
		DWORD m_original_console_mode;
		HANDLE m_console_handle;

		std::ofstream m_console_out;
		std::ofstream m_file_out;

		file m_file;
	};

	inline logger* g_log = nullptr;
}