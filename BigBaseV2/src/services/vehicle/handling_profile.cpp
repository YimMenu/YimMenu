#include "handling_profile.hpp"

namespace big
{
	handling_profile::handling_profile(CVehicle* vehicle)
	{
		m_gravity = vehicle->m_gravity;
		m_handling_data = *vehicle->m_handling_data;
	}

	void handling_profile::apply_to(CVehicle* vehicle, bool restore_hash) const
	{
		const auto hash = vehicle->m_handling_data->m_model_hash;

		vehicle->m_gravity = m_gravity;
		*vehicle->m_handling_data = m_handling_data;

		if (restore_hash)
			vehicle->m_handling_data->m_model_hash = hash;
	}
}