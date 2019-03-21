#pragma once

namespace rage
{
	struct vector2
	{
		float x{};
		float y{};
	};

	struct vector3
	{
		float x{};
		float y{};
		float z{};
	};

	struct vector4
	{
		float x{};
		float y{};
		float z{};
		float w{};
	};

#pragma pack(push, 1)
	class scrVector
	{
	public:
		scrVector() = default;

		scrVector(float x, float y, float z) :
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char m_padding1[0x04];
	public:
		float y{};
	private:
		char m_padding2[0x04];
	public:
		float z{};
	private:
		char m_padding3[0x04];
	};
#pragma pack(pop)
}
