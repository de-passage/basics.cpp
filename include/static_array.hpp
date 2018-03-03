#ifndef GUARD_STATIC_ARRAY_HPP__
#define GUARD_STATIC_ARRAY_HPP__

#include <utility>
#include <functional>

namespace dpsg {
	template<class Type, std::size_t Size>
		class StaticArray {
			public:
				// Construct an array from a list of values
				constexpr StaticArray(const std::initializer_list<Type>&);
				constexpr StaticArray(Type[Size]);
			
				// Return the number of elements in the array
				constexpr std::size_t size() const;

				// Return the element at the given index
				constexpr const Type& operator[](std::size_t) const;
				constexpr Type& operator[](std::size_t);

				typedef Type* iterator;
				typedef const Type* const_iterator;

				// Return an iterator to the first element of the array
				constexpr iterator begin();
				constexpr const_iterator begin() const;

				// Return an element past the last element of the array
				constexpr iterator end();
				constexpr const_iterator end() const;

				// Sort the array according to the comparison function given in argument (insertion sort)
				template<class Compare>
				void sort(const Compare& = std::less<Type>());

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

	template<class Type, std::size_t Size>
		template<class Compare>
		void StaticArray<Type, Size>::sort(const Compare& compare) {
			for(std::size_t i = 1; i < size(); ++i) {
				for(std::size_t j = i; j > 0 && compare(_array[j], _array[j -1]); --j) {
					std::swap(_array[j], _array[j - 1]);
				}
			}
		}
}

#endif// GUARD_STATIC_ARRAY_HPP__
