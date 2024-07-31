#include "translation_service.hpp"

#include "core/data/block_join_reasons.hpp"
#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "http_client/http_client.hpp"
#include "pointers.hpp"
#include "renderer/renderer.hpp"
#include "thread_pool.hpp"

namespace big
{
	translation_service::translation_service() :
	    m_url("https://raw.githubusercontent.com/YimMenu/Translations/master"),
	    m_fallback_url("https://cdn.jsdelivr.net/gh/YimMenu/Translations@master")
	{
	}

	void translation_service::init()
	{
		m_translation_directory = std::make_unique<folder>(g_file_manager.get_project_folder("./translations").get_path());

		bool loaded_remote_index = false;
		for (size_t i = 0; i < 5 && !loaded_remote_index; i++)
		{
			if (i)
				LOG(WARNING) << "Failed to download remote index, trying again... (" << i << ")";
			loaded_remote_index = download_index();
		}

		if (load_local_index())
		{
			if (!loaded_remote_index)
			{
				LOG(WARNING) << "Failed to load remote index, attempting to use fallback.";
				use_fallback_remote();
			}
			else if (m_local_index.version < m_remote_index.version)
			{
				LOG(INFO) << "Languages outdated, downloading new translations.";

				update_language_packs();
				m_local_index.version = m_remote_index.version;
			}

			load_translations();

			if (loaded_remote_index)
				try_set_default_language();

			return;
		}

		if (!loaded_remote_index)
		{
			LOG(WARNING) << "Failed to load remote index, unable to load translations.";
			return;
		}

		LOG(INFO) << "Downloading translations...";

		m_local_index.fallback_default_language = m_remote_index.default_lang;
		m_local_index.selected_language         = m_remote_index.default_lang;
		m_local_index.version                   = m_remote_index.version;

		load_translations();
		try_set_default_language();
	}

	std::string_view translation_service::get_translation(const std::string_view translation_key) const
	{
		return get_translation(rage::joaat(translation_key), translation_key);
	}


	std::string_view translation_service::get_translation(const rage::joaat_t translation_key, const std::string_view fallback) const
	{
		if (auto it = m_translations.find(translation_key); it != m_translations.end())
			return it->second.c_str();

		return fallback;
	}

	std::map<std::string, translation_entry>& translation_service::available_translations()
	{
		return m_remote_index.translations;
	}

	const std::string& translation_service::current_language_pack()
	{
		return m_local_index.selected_language;
	}

	void translation_service::select_language_pack(const std::string& pack_id)
	{
		g_thread_pool->push([this, &pack_id] {
			m_local_index.selected_language = pack_id;
			load_translations();
		});
	}

	void translation_service::update_language_packs()
	{
		for (auto item : std::filesystem::directory_iterator(m_translation_directory->get_path()))
		{
			const auto path = item.path();
			const auto stem = path.stem().string();
			if (stem == "index" || item.path().extension() != ".json")
				continue;

			if (!download_language_pack(stem))
			{
				LOG(WARNING) << "Failed to update '" << stem << "' language pack";
			}
		}
	}

	void translation_service::update_n_reload_language_packs()
	{
		update_language_packs();
		load_translations();
	}

	void translation_service::load_translations()
	{
		m_translations.clear();

		// load default lang first to make sure there are fallback keys if another language pack doesn't have a certain key
		auto j = load_translation(m_remote_index.default_lang);
		for (auto& [key, value] : j.items())
		{
			m_translations.insert({rage::joaat(key), value.get<std::string>()});
		}

		// Don't load selected language if it's the same as default
		if (m_local_index.selected_language != m_remote_index.default_lang)
		{
			auto j = load_translation(m_local_index.selected_language);
			for (auto& [key, value] : j.items())
			{
				m_translations[rage::joaat(key)] = value;
			}
		}

		// local index is saved below so this is prime location to update a value and be sure to have it persisted!
		m_local_index.alphabet_type = m_remote_index.translations[m_local_index.selected_language].alphabet_type;
		g_renderer.get_font_mgr().update_required_alphabet_type(m_local_index.alphabet_type);

		save_local_index();
	}

	bool translation_service::does_language_exist(const std::string_view language)
	{
		auto file = m_translation_directory->get_file(std::format("./{}.json", language));
		if (file.exists())
			return true;

		if (auto it = m_remote_index.translations.find(language.data()); it != m_remote_index.translations.end())
			return true;

		return false;
	}

	nlohmann::json translation_service::load_translation(const std::string_view pack_id)
	{
		auto file = m_translation_directory->get_file(std::format("./{}.json", pack_id));
		if (!file.exists())
		{
			LOG(INFO) << "Translations for '" << pack_id << "' does not exist, downloading from " << m_url;
			if (!download_language_pack(pack_id))
			{
				LOG(WARNING) << "Failed to download language pack, can't recover...";
				return {};
			}
			// make a copy available
			m_local_index.fallback_languages[pack_id.data()] = m_remote_index.translations[pack_id.data()];
		}

		try
		{
			return nlohmann::json::parse(std::ifstream(file.get_path(), std::ios::binary));
		}
		catch (std::exception& e)
		{
			LOG(WARNING) << "Failed to parse language pack. " << e.what();

			if (auto it = m_remote_index.translations.find(pack_id.data()); it != m_remote_index.translations.end()) // ensure that local language files are not removed
				std::filesystem::remove(file.get_path());

			return {};
		}
	}

	bool translation_service::download_language_pack(const std::string_view pack_id)
	{
		if (auto it = m_remote_index.translations.find(pack_id.data()); it != m_remote_index.translations.end())
		{
			const auto response = download_file("/" + it->second.file);
			if (response.status_code == 200)
			{
				try
				{
					auto json      = nlohmann::json::parse(response.text);
					auto lang_file = m_translation_directory->get_file("./" + it->second.file);

					auto out_file = std::ofstream(lang_file.get_path(), std::ios::binary | std::ios::trunc);
					out_file << json.dump(4);
					out_file.close();
				}
				catch (std::exception& e)
				{
					LOG(WARNING) << "Failed to parse language pack. " << e.what();
					return false;
				}

				return true;
			}
		}
		return false;
	}

	bool translation_service::download_index()
	{
		const auto response = download_file("/index.json");
		if (response.status_code == 200)
		{
			try
			{
				m_remote_index = nlohmann::json::parse(response.text);
			}
			catch (std::exception& e)
			{
				LOG(WARNING) << "Failed to load remote index. " << e.what();
				return false;
			}

			return true;
		}
		return false;
	}

	bool translation_service::load_local_index()
	{
		const auto local_index = m_translation_directory->get_file("./index.json");
		if (local_index.exists())
		{
			try
			{
				const auto path = local_index.get_path();
				m_local_index   = nlohmann::json::parse(std::ifstream(path, std::ios::binary));
			}
			catch (std::exception& e)
			{
				LOG(WARNING) << "Failed to load local index. " << e.what();
				return false;
			}

			return true;
		}
		return false;
	}

	void translation_service::save_local_index()
	{
		nlohmann::json j = m_local_index;

		const auto local_index = m_translation_directory->get_file("./index.json");

		auto os = std::ofstream(local_index.get_path(), std::ios::binary | std::ios::trunc);
		os << j.dump(4);
		os.close();
	}

	void translation_service::use_fallback_remote()
	{
		m_remote_index.default_lang = m_local_index.fallback_default_language;
		m_remote_index.translations = m_local_index.fallback_languages;
	}

	cpr::Response translation_service::download_file(const std::string& filename)
	{
		auto response = g_http_client.get(m_url + filename);
		if (response.status_code != 200)
			response = g_http_client.get(m_fallback_url + filename);
		return response;
	}

	void translation_service::try_set_default_language()
	{
		if (!m_local_index.default_language_set)
		{
			g_fiber_pool->queue_job([this] {
				std::string preferred_lang = "en_US";
				auto game_lang             = *g_pointers->m_gta.m_language;

				switch (game_lang)
				{
				case eGameLanguage::FRENCH: preferred_lang = "fr_FR"; break;
				case eGameLanguage::GERMAN: preferred_lang = "de_DE"; break;
				case eGameLanguage::ITALIAN: preferred_lang = "it_IT"; break;
				case eGameLanguage::SPANISH:
				case eGameLanguage::MEXICAN_SPANISH: preferred_lang = "es_ES"; break;
				case eGameLanguage::BRAZILIAN_PORTUGUESE: preferred_lang = "pt_BR"; break;
				case eGameLanguage::POLISH: preferred_lang = "pl_PL"; break;
				case eGameLanguage::RUSSIAN: preferred_lang = "ru_RU"; break;
				case eGameLanguage::KOREAN: preferred_lang = "ko_KR"; break;
				case eGameLanguage::TRADITIONAL_CHINESE: preferred_lang = "zh_TW"; break;
				case eGameLanguage::JAPANESE: preferred_lang = "ja_JP"; break;
				case eGameLanguage::SIMPLIFIED_CHINESE: preferred_lang = "zh_CN"; break;
				}

				if (game_lang == eGameLanguage::SIMPLIFIED_CHINESE || game_lang == eGameLanguage::TRADITIONAL_CHINESE)
				{
					// Tweaks to make it easier for people playing in the China region
					g.session_browser.filter_multiplexed_sessions = true;
					g.reactions.chat_spam.block_joins             = true;
					g.reactions.chat_spam.block_join_reason       = block_join_reason_t::BadReputation;
				}

				if (does_language_exist(preferred_lang))
				{
					m_local_index.selected_language = preferred_lang;
					save_local_index();
				}

				m_local_index.default_language_set = true;
				load_translations();
			});
		}
	}
}
