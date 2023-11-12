#pragma once

namespace big
{
	class custom_chat_buffer
	{
		int len = 0;

	public:
		char buf[4096] = {'\0'};

		inline void reset_buf()
		{
			strcpy(buf, "");
			len = 0;
		}

		void append_msg(const char* player_name, char* msg)
		{
			char new_msg[320]         = {'\0'};
			std::string formatted_str = std::format("{} : {}\n", player_name, msg);
			strcpy(new_msg, formatted_str.c_str());

			auto msg_len              = strlen(new_msg);
			constexpr int content_len = sizeof(buf) - 1;
			size_t availableSpace     = content_len - len;

			if (availableSpace >= msg_len)
				len += msg_len;
			else
			{
				// memmove(buf, buf + msg_len, content_len - msg_len);
				// buf[content_len - msg_len] = '\0';
				reset_buf();
			}
			strcat(buf, new_msg);
		}
	};

	inline custom_chat_buffer g_custom_chat_buffer;
}