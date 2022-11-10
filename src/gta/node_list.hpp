#pragma once
#include "fwddec.hpp"
#include "base.hpp"

namespace rage
{
	template <typename T, typename Base = datBase>
	class atDNode : public Base
	{
	public:
		T m_data;
		void *m_unk;
		atDNode<T, Base> *m_next;
	};

	template <typename Node>
	class atDList
	{
	public:
		Node *m_head;
		Node *m_tail;
	};
}
