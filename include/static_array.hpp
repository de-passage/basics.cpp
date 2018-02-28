#ifndef GUARD_STATIC_ARRAY_HPP__
#define GUARD_STATIC_ARRAY_HPP__

#include <utility>

namespace dpsg {
	template<class Type, std::size_t Size>
		class StaticArray {
			public:
				constexpr StaticArray(const std::initializer_list<Type>&);
				constexpr StaticArray(Type[Size]);
				constexpr std::size_t size() const;

				constexpr const Type& operator[](std::size_t) const;
				constexpr Type& operator[](std::size_t);

				typedef Type* iterator;
				typedef const Type* const_iterator;

				constexpr iterator begin();
				constexpr const_iterator begin() const;

				constexpr iterator end();
				constexpr const_iterator end() const;

			private:
				Type _array[Size];
		};

	template<class Type, std::size_t Size>
		constexpr StaticArray<Type, Size>::StaticArray(const std::initializer_list<Type>& list) : _array(list) {}

	template<class Type, std::size_t Size>
		constexpr StaticArray<Type, Size>::StaticArray(Type arr[Size]) : _array(arr) {}

	template<class Type, std::size_t Size>
		constexpr std::size_t StaticArray<Type, Size>::size() const {
			return Size;
		}

	template<class Type, std::size_t Size>
		constexpr const Type& StaticArray<Type, Size>::operator[](std::size_t pos) const {
			return _array[pos];
		}
	template<class Type, std::size_t Size>
		constexpr Type& StaticArray<Type, Size>::operator[](std::size_t pos) {
			return _array[pos];
		}

	template<class Type, std::size_t Size>
		constexpr typename StaticArray<Type, Size>::iterator StaticArray<Type, Size>::begin() {
			return _array;
		}

	template<class Type, std::size_t Size>
		constexpr typename StaticArray<Type, Size>::const_iterator StaticArray<Type, Size>::begin() const {
			return _array;
		}

	template<class Type, std::size_t Size>
		constexpr typename StaticArray<Type, Size>::iterator StaticArray<Type, Size>::end() {
			return _array + Size;
		}

	template<class Type, std::size_t Size>
		constexpr typename StaticArray<Type, Size>::const_iterator StaticArray<Type, Size>::end() const {
			return _array + Size;
		}
}

#endif// GUARD_STATIC_ARRAY_HPP__
