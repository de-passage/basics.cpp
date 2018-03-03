#ifndef GUARD_DYNAMIC_ARRAY_HPP__
#define GUARD_DYNAMIC_ARRAY_HPP__

#include <initializer_list>
#include <utility>
#include <stdexcept>
#include <sstream>

namespace dpsg {
	template<class Type>
		class DynamicArray {
			public:
				// Constructs an empty array of size 0
				constexpr DynamicArray();

				// Create an empty array with the given size
				constexpr DynamicArray(std::size_t);

				// Create an array containing the given elements
				constexpr DynamicArray(const std::initializer_list<Type>& list);
				~DynamicArray();

				// Add an element at the end of the array
				void push_back(const Type&);

				// Remove the last element in the array
				void pop();

				// Return the element at the given index
				// If the index is out of bound, the behavior is undefined
				constexpr const Type& operator[](std::size_t) const;
				constexpr Type& operator[](std::size_t);

				// Return the element at the given index
				// If the index is out of bound, throw a std::out_of_range exception
				const Type& at(std::size_t) const;
				Type& at(std::size_t);

				// Return the number of elements in the array
				constexpr std::size_t size() const;

				// Return the size of the array in memory
				constexpr std::size_t capacity() const;

				// Change the capacity of the array
				void resize(std::size_t);

				// Sort the elements in the array according to the comparison function given in argument (quicksort)
				template<class Function>
					void sort(const Function&);


			private:
				std::size_t _size;
				std::size_t _capacity;
				Type* _array;

		};


	template<class Type>
		constexpr DynamicArray<Type>::DynamicArray() : _size(0), _capacity(0), _array(nullptr) {}

	template<class Type>
		constexpr DynamicArray<Type>::DynamicArray(std::size_t size) :
			_size(size), _capacity(_capacity), _array(new Type[size]) {}

	template<class Type>
		constexpr DynamicArray<Type>::DynamicArray(const std::initializer_list<Type>& list) :
			_size(list.size()), _capacity(list.size()), _array(new Type[list.size()]) {
				std::size_t i = 0;
				for(auto it = list.begin(); it < list.end(); ++it, ++i)
					_array[i] = *it;
			}
	template<class Type>
		DynamicArray<Type>::~DynamicArray() {
			if(_array != nullptr)
				delete[] _array;
		}

	template<class Type>
		void DynamicArray<Type>::push_back(const Type& t) {
			if(_size == _capacity) {
				resize((_capacity + 1) * 2);
			}
			_array[_size++] = t;
		}

	template<class Type>
		void DynamicArray<Type>::pop() {
			--_size;
		}

	template<class Type>
		constexpr const Type& DynamicArray<Type>::operator[](std::size_t pos) const {
			return _array[pos];
		}
	template<class Type>
		constexpr Type& DynamicArray<Type>::operator[](std::size_t pos) {
			return _array[pos];
		}
	template<class Type>
		const Type& DynamicArray<Type>::at(std::size_t pos) const {
			return const_cast<DynamicArray<Type>*>(this)->at(pos);
		}
	template<class Type>
		Type& DynamicArray<Type>::at(std::size_t pos) {
			if(pos >= _size) {
				std::ostringstream oss;
				oss << "DynamicArray::at() called out of range: index '"  << pos << "' queried but size is " << _size << ".";
				throw std::out_of_range(oss.str());
			} else
				return (*this)[pos];
		}


	template<class Type>
		inline constexpr std::size_t DynamicArray<Type>::size() const {
			return _size;
		}
	template<class Type>
		inline constexpr std::size_t DynamicArray<Type>::capacity() const {
			return _size;
		}
	template<class Type>
		void DynamicArray<Type>::resize(std::size_t new_size) {
			Type* tmp = new Type[new_size];
			std::size_t max_bound = std::min(new_size, _size);
			for(std::size_t i = 0; i < max_bound; ++i)
				tmp[i] = std::move(_array[i]);
			std::swap(tmp, _array);
			delete tmp[_size];
			_size = new_size;
		}

	template<class Type>
		template<class Function>
		void DynamicArray<Type>::sort(const Function& compare) {
		}


}
#endif // GUARD_DYNAMIC_ARRAY_HPP__

