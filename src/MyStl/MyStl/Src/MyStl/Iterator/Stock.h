#pragma once

namespace MyStl {
	template<typename T>
	struct Stock
	{
	public:
		Stock()
		{
			init();
		}
		Stock(T &t)
		{
			init();
			value = t;
		}
		Stock * prev;
		Stock * next;
		T value;

	private:
		void init()
		{
			prev = nullptr;
			next = nullptr;
		}
	};
}