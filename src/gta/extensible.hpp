#pragma once
#include <cstdint>
#include "ref_aware.hpp"

namespace rage
{
	class fwExtension
	{
	public:
		virtual ~fwExtension() = default;
		virtual void unk_0x08() = 0;
		virtual void unk_0x10() = 0;
		virtual std::uint32_t get_id() = 0;
	};

	class fwExtensionContainer
	{
	public:
		fwExtension *m_entry;
		fwExtensionContainer* m_next;
	};

	class fwExtensibleBase : public fwRefAwareBase
	{
	public:
		virtual bool is_of_type(std::uint32_t hash) = 0;
		virtual std::uint32_t const &get_type() = 0;
	public:
		fwExtensionContainer* m_extension_container; // 0x10
	private:
		void *m_extensible_unk;                      // 0x18
	public:
		template <typename T>
		bool is_of_type()
		{
			static auto name = (typeid(T).name()) + 6; // Skip "class "
			static auto name_hash = util::joaat(name);

			return is_of_type(name_hash);
		}
	};

	static_assert(sizeof(fwExtensibleBase) == 0x20);
}
