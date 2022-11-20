#pragma once

namespace memory
{
	class byte_patch
	{
	public:
		virtual ~byte_patch();

		void apply() const;

		void restore() const;

		void remove() const;

		static const std::unique_ptr<byte_patch>& make(void* address, const char* bytes, size_t len)
		{
			return m_patches.emplace_back(
				std::unique_ptr<byte_patch>(new byte_patch(address, bytes, len)));
		}

		static const std::unique_ptr<byte_patch>& make(void* address, std::vector<byte> bytes)
		{
			return m_patches.emplace_back(
				std::unique_ptr<byte_patch>(new byte_patch(address, bytes)));
		}

		static void restore_all();

	private:
		byte_patch(void* address, const char* bytes, size_t len)
			: m_address(address), m_size(len)
		{
			m_original_bytes = std::make_unique<uint8_t[]>(m_size);
			m_value = std::make_unique<uint8_t[]>(m_size);

			memcpy(m_original_bytes.get(), m_address, m_size);
			memcpy(m_value.get(), bytes, m_size);
		}

		inline byte_patch(void* address, std::vector<byte> bytes)
			: m_address(address), m_size(bytes.size())
		{
			m_original_bytes = std::make_unique<uint8_t[]>(m_size);
			m_value = std::make_unique<uint8_t[]>(m_size);

			memcpy(m_original_bytes.get(), m_address, m_size);
			memcpy(m_value.get(), bytes.data(), m_size);
		}

	protected:
		static inline std::vector<std::unique_ptr<byte_patch>> m_patches;

	private:
		void* m_address;
		std::unique_ptr<uint8_t[]> m_value;
		std::unique_ptr<uint8_t[]> m_original_bytes;
		std::size_t m_size;

		friend bool operator== (const std::unique_ptr<byte_patch>& a, const byte_patch* b);
	};
}
