#pragma once
#include "file_manager/folder.hpp"
#include "gta/joaat.hpp"
#include "local_index.hpp"
#include "remote_index.hpp"

namespace big
{
	using translation_map = std::unordered_map<rage::joaat_t, std::string>;

	class translation_service
	{
	public:
		translation_service();
		virtual ~translation_service()                                 = default;
		translation_service(const translation_service&)                = delete;
		translation_service(translation_service&&) noexcept            = delete;
		translation_service& operator=(const translation_service&)     = delete;
		translation_service& operator=(translation_service&&) noexcept = delete;

		void init();

		std::string_view get_translation(const std::string_view translation_key) const;
		std::string_view get_translation(const rage::joaat_t translation_key) const;

		std::map<std::string, translation_entry>& available_translations();
		const std::string& current_language_pack();
		void select_language_pack(const std::string& pack_id);

	private:
		void load_translations();
		nlohmann::json load_translation(const std::string_view pack_id);

		bool download_language_pack(const std::string_view pack_id);
		void update_language_packs();

		/**
         * @brief Downloads the remote index to compare with our local index
         * 
         * @return true 
         * @return false 
         */
		bool download_index();
		bool load_local_index();
		void save_local_index();
		/**
         * @brief Attempts to load the remote from the local index fallback
         */
		void use_fallback_remote();

	private:
		const std::string m_url;
		std::unique_ptr<folder> m_translation_directory;
		local_index m_local_index;
		remote_index m_remote_index;

		translation_map m_translations;
	};

	inline auto g_translation_service = translation_service();

	template<std::size_t N>
	struct TranslationLiteral
	{
		rage::joaat_t m_hash;
		char m_key[N]{};

		consteval TranslationLiteral(char const (&pp)[N])
		{
			std::ranges::copy(pp, m_key);
			m_hash = rage::joaat(pp);
		};

		const std::string_view translation() const
		{
			if (const auto translation = g_translation_service.get_translation(m_hash); translation.length())
				return translation;
			return m_key;
		}
	};

	template<TranslationLiteral T>
	constexpr auto operator"" _T()
	{
		return T.translation();
	}
}