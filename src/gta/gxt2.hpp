#pragma once

struct GXT2_metadata
{
	static constexpr auto header = "2TXG";
};

#pragma pack(push, 1)
struct GXT2_key
{
	rage::joaat_t key_hash       = -1;
	uint32_t file_offset_to_text = -1;
};
static_assert(sizeof(GXT2_key) == 8);
#pragma pack(pop)

struct GXT2_entry
{
	rage::joaat_t hash = -1;
	std::string text;
};
