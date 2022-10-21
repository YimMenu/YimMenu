#pragma once

namespace memory
{
	class byte_patch
	{
	public:
		virtual ~byte_patch()
		{
			memcpy(m_address, m_original_bytes.data(), m_original_bytes.size());
		}

		/// <summary>
		/// To guarantee proper restoration of bytes all shared_ptr instances will be invalidated that point to this object.
		/// </summary>
		void restore() const
		{
			if (const auto it = std::find(m_patches.begin(), m_patches.end(), this); it != m_patches.end())
			{
				it->reset();
				m_patches.erase(it);
			}
		}

		template <typename TAddr>
		static std::shared_ptr<byte_patch> make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			auto patch = std::shared_ptr<byte_patch>(new byte_patch(address, value));
			m_patches.emplace_back(patch);
			return patch;
		}

		static void restore_all()
		{
			for (const auto& patch : m_patches)
			{
				patch->restore();
			}
		}

	private:
		template <typename TAddr>
		byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
			: m_address(address)
		{
			constexpr auto size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);
			m_original_bytes.resize(size);
			memcpy(m_original_bytes.data(), m_address, size);

			*address = value;
		}

	protected:
		static inline std::vector<std::shared_ptr<byte_patch>> m_patches;

	private:
		void* m_address;
		std::vector<uint8_t> m_original_bytes;

		friend bool operator== (const std::shared_ptr<byte_patch> a, const byte_patch* b);
	};

	bool operator== (const std::shared_ptr<byte_patch> a, const byte_patch* b)
	{
		return a->m_address == b->m_address;
	}
}
