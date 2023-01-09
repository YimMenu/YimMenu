#pragma once
#include "services/players/player_service.hpp"
#include "file_manager/file.hpp"

namespace
{
	static const char* spam_texts[] =
	{
		"QQ",
		"WWW.",
		"www.",
		".cn",
		".CN",
		".TOP",
		".COM",
		".top",
		"\xE3\x80\x90",
		"/Menu",
		"Money/",
		"Money\\\\",
		"Money\\",
		".gg",
		"--->",
		"shopgta5",
		"doit#",
		"krutka#",
		"<b>",
		"\xD0\xBC\xD0\xB5", // Cyrillic "me"
		"P888",
		"gtacash",
		"\xE6\x89\xA3\xE6\x89\xA3", // no clue what this is
		"\xE5\xBE\xAE\xE4\xBF\xA1", // "wechat" in Chinese
		".cc",
		"<font s",
		"sellix.io",
		"ezcars",
		"PLANO INICIAL", // "initial plan"
		"REP +",
		"20R$", // Brazil currency?
		"l55.me"
	};
}

namespace big::spam
{
	inline bool is_text_spam(const char* text)
	{
		for (auto e : spam_texts)
			if (strstr(text, e) != 0)
				return true;

		return false;
	}

	inline void log_chat(char* msg, player_ptr player, bool is_spam)
	{
		std::ofstream spam_log(g_file_manager->get_project_file(is_spam ? "./spam.log" : "./chat.log").get_path(), std::ios::app);

		auto& plData = *player->get_net_data();

		spam_log << player->get_name() << " (" << plData.m_gamer_handle_2.m_rockstar_id << ") <"
			<< (int)plData.m_external_ip.m_field1 << "." << (int)plData.m_external_ip.m_field2 << "." << (int)plData.m_external_ip.m_field3 << "." << (int)plData.m_external_ip.m_field4 <<
			">: " << msg <<
			std::endl;

		spam_log.close();
	}
}