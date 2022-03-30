#pragma once

namespace big::api
{
	class api;

	class vehicle_api final
	{
		api* m_api;

	public:
		vehicle_api(api* api);

		bool create_handling_profile(
			const std::uint32_t handling_hash,
			const std::string_view name,
			const std::string_view descr,
			const nlohmann::json& data,
			nlohmann::json& out) const;
		bool delete_handling_profile(const std::string_view share_code) const;
		bool delete_saved_handling_profile(const std::string_view share_code) const;
		bool get_handling_profile(const std::string_view share_code, nlohmann::json& out) const;
		bool get_my_handling_profiles(const std::uint32_t handling_hash, nlohmann::json& out) const;
		bool get_saved_handling_profiles(const std::uint32_t handling_hash, nlohmann::json& out) const;
		bool update_handling_profile(
			const std::string_view share_code,
			const std::string_view name,
			const std::string_view descr,
			const nlohmann::json& update,
			nlohmann::json& out) const;
		bool update_saved_handling_profile(const std::string_view share_code) const;
	};
}