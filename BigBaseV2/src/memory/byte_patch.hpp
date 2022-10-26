#pragma once

namespace memory
{
	class byte_patch
	{
	public:
		virtual ~byte_patch()
		{
			restore();
		}

		void apply() const
		{
			memcpy(m_address, m_value.get(), m_size);
		}

		void restore() const
		{
			memcpy(m_address, m_original_bytes.get(), m_size);
		}

		void remove() const
		{
			if (const auto it = std::find(m_patches.begin(), m_patches.end(), this); it != m_patches.end())
			{
				m_patches.erase(it);
			}
		}

		template <typename TAddr>
		static const std::unique_ptr<byte_patch>& make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			return m_patches.emplace_back(
				std::unique_ptr<byte_patch>(new byte_patch(address, value)));
		}

		static void restore_all()
		{
			m_patches.clear();
		}

	private:
		template <typename TAddr>
		byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
			: m_address(address)
		{
			m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);
			m_original_bytes = std::make_unique<uint8_t[]>(m_size);
			m_value = std::make_unique<uint8_t[]>(m_size);

			memcpy(m_original_bytes.get(), m_address, m_size);
			memcpy(m_value.get(), &value, m_size);
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

	bool operator== (const std::unique_ptr<byte_patch>& a, const byte_patch* b)
	{
		return a->m_address == b->m_address;
	}
}
