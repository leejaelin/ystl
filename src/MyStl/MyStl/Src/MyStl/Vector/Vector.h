#pragma once

namespace MyStl
{
	template<typename T>
	class Vector
	{
	private:
		size_t length;
		size_t capacity_length;
		T* arr;

	public:
		typedef T value_type;

		Vector()
		{
			_init();
		}
		Vector(size_t size)
		{
			_init();
			_allocator(size);
		}
		Vector(std::initializer_list<T> init_list)
		{
			_init();
			if (nullptr != _allocator(init_list.size()))
			{
				size_t idx = 0;
				for (const auto& val : init_list)
					push_back(val);
			}
		}
		virtual ~Vector()
		{
			_init();
		}
	
		size_t size() const
		{
			return length;
		}
		
		void resize(size_t size, const T& value = 0)
		{
			if (size <= length) return;
			T* oldArr = arr;
			size_t oldLength = length;
			if (nullptr != _allocator(size))
			{
				memset(arr + oldLength, value, sizeof(T) * (size - oldLength));
				memcpy_s(arr, sizeof(T) * size, oldArr, sizeof(T) * oldLength);
				delete[] oldArr;
			}		
		}

		size_t capacity() const
		{
			return capacity_length;
		}

		bool empty() const
		{
			return size > 0;
		}

		void reserve(const size_t& size)
		{
			if (capacity_length >= size) return;
			T* oldArr = arr;
			size_t oldLength = length;
			if (nullptr != _allocator(size))
			{
				memcpy_s(arr, sizeof(T) * size, oldArr, sizeof(T) * oldLength);
				length = oldLength;
				delete[] oldArr;
			}
		}

		void shrink_to_fit()
		{
			if (length >= capacity_length) return;
			T* oldArr = arr;
			if (nullptr != _allocator(length))
			{
				memcpy_s(arr, sizeof(T) * length, oldArr, sizeof(T) * length);
				capacity_length = length;
				delete[] oldArr;
			}
		}

		void push_back(const T& value)
		{
			if (length >= capacity_length)
				_reallocator(length * 2);

			arr[length++] = value;
			capacity_length = (capacity_length < length) ? length : capacity_length;
		}

		void push_back(T&& value)
		{
			push_back(value);
		}

		void emplace_back()
		{
			// Todo...
		}

	private:
		inline void _init()
		{
			delete[] arr;
			arr = nullptr;
			length = 0;
			capacity_length = 0;
		}

		inline T* _allocator(size_t size = 1)
		{
			if (1 > size) return nullptr;
			arr = new T[size];
			length = size;
			capacity_length = (capacity_length > length) ? capacity_length : length;
			return arr;
		}

		inline T* _reallocator(size_t size = 1)
		{
			if (size < length) return nullptr;
			
			const size_t resize = (0 < size) ? size : 1;
			T* tmpArr = new T[resize * 2];
			capacity_length = resize * 2;
			memcpy(tmpArr, arr, length);
			delete[] arr;
			return arr = tmpArr;
		}
	};

} /* MyStl */