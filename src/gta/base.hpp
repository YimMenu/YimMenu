#pragma once

namespace rage
{
	class datBase
	{
	public:
		virtual ~datBase() = default;
	};

	class pgBase
	{
	public:
		virtual ~pgBase() = default;
	private:
		void *m_pgunk;
	};
}
