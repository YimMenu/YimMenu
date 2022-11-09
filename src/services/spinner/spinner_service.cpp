#include "spinner_service.hpp"

namespace big
{
	spinner_service::spinner_service()
	{
		g_spinner_service = this;
	}

	spinner_service::~spinner_service()
	{
		g_spinner_service = nullptr;
	}

	void spinner_service::push(BusySpinner n)
	{
		this->spinner = n;
	}

	void spinner_service::push(bool active, std::string text, bool progress_bar, float progress)
	{
		this->push({ active, eBusySpinnerType::BUSY_SPINNER_LEFT, text, progress_bar, progress });
	}

	void spinner_service::push_online(bool active, std::string text, bool progress_bar, float progress)
	{
		this->push({ active, eBusySpinnerType::BUSY_SPINNER_SAVE, text, progress_bar, progress });
	}
}