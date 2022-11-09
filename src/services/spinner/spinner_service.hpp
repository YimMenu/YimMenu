#pragma once
namespace big
{
	enum eBusySpinnerType
	{
		BUSY_SPINNER_LEFT,
		BUSY_SPINNER_LEFT_2,
		BUSY_SPINNER_LEFT_3,
		BUSY_SPINNER_SAVE,
		BUSY_SPINNER_RIGHT,
	};

	class spinner_service final
	{
		struct BusySpinner
		{
			bool active;
			eBusySpinnerType type;
			std::string text;
			bool progress_bar;
			float progress;
		};

	public:
		spinner_service();
		virtual ~spinner_service();

		BusySpinner spinner{};

		void push(BusySpinner);
		void push(bool active, std::string text, bool progress_bar = false, float progress = 0.f);
		void push_online(bool active, std::string text, bool progress_bar = false, float progress = 0.f);

		std::map<eBusySpinnerType, ImColor> spinner_colors = {
			{eBusySpinnerType::BUSY_SPINNER_LEFT, ImColor(181.f, 181.f, 181.f, 255.f)},
			{eBusySpinnerType::BUSY_SPINNER_LEFT_2, ImColor(0.29f, 0.69f, 0.34f, 255.f)},
			{eBusySpinnerType::BUSY_SPINNER_LEFT_3, ImColor(0.69f ,0.49f, 0.29f, 255.f) },
			{eBusySpinnerType::BUSY_SPINNER_SAVE, ImColor(0.69f, 0.29f , 0.29f, 255.f)},
			{eBusySpinnerType::BUSY_SPINNER_RIGHT, ImColor(222, 204, 23, 255)},
		};

	};

	inline spinner_service* g_spinner_service{};
}