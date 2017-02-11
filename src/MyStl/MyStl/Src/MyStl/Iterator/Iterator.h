#pragma once
#include "Stock.h"

namespace MyStl {
	template<typename T>
	class Iterator
	{
	private:
		Stock * m_CurNode;

		void moveNext()
		{
			if (nullptr != m_CurNode && nullptr != m_CurNode->next)
				m_CurNode = m_CurNode->next;
		}
	public:
		Iterator(Stock * curNode) { m_CurNode = (nullptr != curNode &&nullptr == curNode->prev) ? curNode->next : curNode; }
		bool operator != (const Iterator&rhnd) { return (rhnd.m_CurNode != m_CurNode); }// must required
		void operator++() { moveNext(); } // must required
		Stock&operator *() { return *m_CurNode; } // must required
	};
}