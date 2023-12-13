#include "handling_profile.hpp"

namespace big
{
	handling_profile::handling_profile(CVehicle* vehicle)
	{
		m_gravity       = vehicle->m_gravity;
		m_handling_data = *vehicle->m_handling_data;

		if (std::isinf(m_handling_data.m_traction_spring_delta_max_ratio))
			m_handling_data.m_traction_spring_delta_max_ratio = 0.f;
	}

	void handling_profile::apply_to(CVehicle* vehicle, bool restore_hash) const
	{
		const auto hash = vehicle->m_handling_data->m_model_hash;

		vehicle->m_gravity = m_gravity;

		// cursed but works perfectly without overriding members that we shouldn't override
		nlohmann::json j = m_handling_data;// exports our binary object so we can apply it field by field instead of copying the whole object
		from_json(j, *vehicle->m_handling_data);// macro is defined in global scope of which CHandlingData is part of

		if (restore_hash)
			vehicle->m_handling_data->m_model_hash = hash;
	}
}