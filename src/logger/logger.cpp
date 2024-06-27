#include "logger.hpp"

#include "util/is_proton.hpp"

namespace big
{
	template<typename TP>
	std::time_t to_time_t(TP tp)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
		return system_clock::to_time_t(sctp);
	}

	void logger::initialize(const std::string_view console_title, file file, bool attach_console)
	{
		m_console_title = console_title;
		m_file          = file;
		if (is_proton())
		{
			LOG(VERBOSE) << "Using simple logger.";
			m_console_logger = &logger::format_console_simple;
		}

		create_backup();
		m_file_out.open(m_file.get_path(), std::ios_base::out | std::ios_base::trunc);

		Logger::Init();
		Logger::AddSink([this](LogMessagePtr msg) {
			(this->*m_console_logger)(std::move(msg));
		});
		Logger::AddSink([this](LogMessagePtr msg) {
			format_file(std::move(msg));
		});

		toggle_external_console(attach_console);
	}

	void logger::destroy()
	{
		Logger::Destroy();
		m_file_out.close();
		toggle_external_console(false);
	}

	void logger::toggle_external_console(bool toggle)
	{
		if (m_is_console_open == toggle)
		{
			return;
		}
		m_is_console_open = toggle;

		m_console_out.close();
		if (m_did_console_exist)
			SetConsoleMode(m_console_handle, m_original_console_mode);

		if (!m_did_console_exist)
			FreeConsole();

		if (toggle)
		{
			if (m_did_console_exist = ::AttachConsole(GetCurrentProcessId()); !m_did_console_exist)
				AllocConsole();

			if (m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE); m_console_handle != nullptr)
			{
				SetConsoleTitleA(m_console_title.data());
				SetConsoleOutputCP(CP_UTF8);

				DWORD console_mode;
				GetConsoleMode(m_console_handle, &console_mode);
				m_original_console_mode = console_mode;

				// terminal like behaviour enable full color support
				console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

				SetConsoleMode(m_console_handle, console_mode);
			}

			m_console_out.open("CONOUT$", std::ios_base::out | std::ios_base::app);
		}
	}

	void logger::create_backup()
	{
		if (m_file.exists())
		{
			auto file_time  = std::filesystem::last_write_time(m_file.get_path());
			auto time_t     = to_time_t(file_time);
			auto local_time = std::localtime(&time_t);

			m_file.move(std::format("./backup/{:0>2}-{:0>2}-{}-{:0>2}-{:0>2}-{:0>2}_{}",
			    local_time->tm_mon + 1,
			    local_time->tm_mday,
			    local_time->tm_year + 1900,
			    local_time->tm_hour,
			    local_time->tm_min,
			    local_time->tm_sec,
			    m_file.get_path().filename().string().c_str()));
		}
	}

	const LogColor get_color(const eLogLevel level)
	{
		switch (level)
		{
		case VERBOSE: return LogColor::BLUE;
		case INFO: return LogColor::GREEN;
		case WARNING: return LogColor::YELLOW;
		case FATAL: return LogColor::RED;
		}
		return LogColor::WHITE;
	}

	const char* get_level_string(const eLogLevel level)
	{
		constexpr std::array<const char*, 4> levelStrings = {{{"DEBUG"}, {"INFO"}, {"WARN"}, {"FATAL"}}};

		return levelStrings[level];
	}

	void logger::format_console(const LogMessagePtr msg)
	{
		if (!m_is_console_open)
		{
			return;
		}

		const auto color = get_color(msg->Level());

		const auto timestamp = std::format("{0:%H:%M:%S}", msg->Timestamp());
		const auto& location = msg->Location();
		const auto level     = msg->Level();
		const auto stream    = msg->Stream();

		const auto file = std::filesystem::path(location.file_name()).filename().string();

		if (stream)
			m_console_out << "[" << timestamp << "][" << stream->get()->Name() << "]" << ADD_COLOR_TO_STREAM(color) << "[" << get_level_string(level) << "/" << file << ":"
			              << location.line() << "] " << RESET_STREAM_COLOR << msg->Message() << std::flush;
		else
			m_console_out << "[" << timestamp << "]" << ADD_COLOR_TO_STREAM(color) << "[" << get_level_string(level) << "/" << file << ":"
				          << location.line() << "] " << RESET_STREAM_COLOR << msg->Message() << std::flush;
	}

	void logger::format_console_simple(const LogMessagePtr msg)
	{
		if (!m_is_console_open)
		{
			return;
		}

		const auto color = get_color(msg->Level());

		const auto timestamp = std::format("{0:%H:%M:%S}", msg->Timestamp());
		const auto& location = msg->Location();
		const auto level     = msg->Level();
		const auto stream    = msg->Stream();

		const auto file = std::filesystem::path(location.file_name()).filename().string();

		if (stream)
			m_console_out << "[" << timestamp << "][" << stream->get()->Name() << "]"
			                 "[" << get_level_string(level) << "/" << file << ":" << location.line() << "] " << msg->Message() << std::flush;
		else
			m_console_out << "[" << timestamp << "]"
					         "[" << get_level_string(level) << "/" << file << ":" << location.line() << "] " << msg->Message() << std::flush;
	}

	void logger::format_file(const LogMessagePtr msg)
	{
		if (!m_file_out.is_open())
			return;

		const auto timestamp = std::format("{0:%H:%M:%S}", msg->Timestamp());
		const auto& location = msg->Location();
		const auto level     = msg->Level();
		const auto stream    = msg->Stream();

		const auto file = std::filesystem::path(location.file_name()).filename().string();

		if (stream)
			m_file_out << "[" << timestamp << "][" << stream->get()->Name() << "]"
			              "[" << get_level_string(level) << "/" << file << ":" << location.line() << "] " << msg->Message() << std::flush;
		else
			m_file_out << "[" << timestamp << "]"
					      "[" << get_level_string(level) << "/" << file << ":" << location.line() << "] " << msg->Message() << std::flush;
	}
}
