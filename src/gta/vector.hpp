#pragma once

namespace rage
{
#pragma pack(push, 1)
	class scrVector
	{
	public:
		scrVector() = default;

		scrVector(float x, float y, float z) :
			x(x), y(y), z(z)
		{}

		scrVector operator+(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x + other.x;
			vec.y = this->y + other.y;
			vec.z = this->z + other.z;
			return vec;
		}

		scrVector operator-(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x - other.x;
			vec.y = this->y - other.y;
			vec.z = this->z - other.z;
			return vec;
		}

		scrVector operator*(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x * other.x;
			vec.y = this->y * other.y;
			vec.z = this->z * other.z;
			return vec;
		}

		scrVector operator*(const float& other)
		{
			scrVector vec;
			vec.x = this->x * other;
			vec.y = this->y * other;
			vec.z = this->z * other;
			return vec;
		}
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

class Vector2 final
{
public:
	Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y)
	{}

public:
	float x, y;
};

class Vector4 final
{
public:
	Vector4() = default;

	Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

public:
	float x, y, z, w;
};
