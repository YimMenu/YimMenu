#include "hooking.hpp"
#include "rage/rlMetric.hpp"

namespace big
{
#pragma pack(push, 1)
	class json_serializer
	{
		uint32_t unk0;  // 0x00
		uint32_t unk1;  // 0x00
		char* buffer;   // 0x08
		uint32_t curlen;// 0x10
		uint32_t maxlen;// 0x14
		uint32_t unk4;  // 0x18
		uint8_t flags;  // 0x1C

	public:
		json_serializer(char* _buffer, uint32_t _length) :
		    buffer(_buffer),
		    maxlen(_length)
		{
			unk0
				= 0;
				unk1   = 0;
				curlen = 0;
				unk4   = 1;
				flags  = 0;
		}

		inline char* get_string() const
		{
			return buffer;
		}
	};
	static_assert(sizeof(json_serializer) == 0x1D);// size is actually 0x20
#pragma pack(pop)

	void hooks::prepare_metric_for_sending(rage::datBitBuffer* bit_buffer, int unk, int time, rage::rlMetric* metric)
	{
		if (g.debug.logs.metric_logs)
		{
			char buffer[256]{};
			json_serializer serializer(buffer, sizeof(buffer));

			metric->serialize(&serializer);

			LOG(INFO) << "METRIC: " << metric->get_name() << "; DATA: " << serializer.get_string();
		}
	}
}
