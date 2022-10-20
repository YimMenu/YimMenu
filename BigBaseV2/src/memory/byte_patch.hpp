#pragma once

namespace memory
{
	struct byte_patch
	{
		void* address;
		std::vector<uint8_t> original_bytes;

		template <typename TAddr>
		static byte_patch make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			byte_patch p;

			p.address = address;

			constexpr size_t size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

			p.original_bytes.resize(size);
			memcpy(p.original_bytes.data(), p.address, size);

			*address = value;

			return p;
		}

		inline void restore() const
		{
			memcpy(address, original_bytes.data(), original_bytes.size());
		}
	};
}
