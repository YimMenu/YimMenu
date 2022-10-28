#pragma once
#include "vehicle/CVehicle.hpp"

namespace big
{
	class handling_profile final
	{
	public:
		handling_profile(CVehicle* vehicle);
		handling_profile() = default;

		void apply_to(CVehicle* vehicle, bool restore_hash = true) const;

	private:
		float m_gravity;
		CHandlingData m_handling_data;

	};
}