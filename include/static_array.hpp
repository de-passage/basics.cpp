#ifndef GUARD_STATIC_ARRAY_HPP__
#define GUARD_STATIC_ARRAY_HPP__

#include <utility>
#include <functional>

#include <stdexcept>

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
		template<class Compare = std::less<Type>>
			void sort(const Compare& = Compare());

	private:
		Type _array[Size];

		template<class Compare>
			void _turn_to_heap(const Compare&);
		template<class Compare>
			void _sift_down(std::size_t, std::size_t, const Compare&);
};

template<class Type, std::size_t Size>
constexpr StaticArray<Type, Size>::StaticArray(const std::initializer_list<Type>& list) : _array() {
	if(size() != list.size()) throw std::invalid_argument("StaticArray error: initialization from initializer_list of different lenght forbidden");
	std::size_t i = 0;
	for(auto it = list.begin(); it != list.end(); ++it, ++i) {
		_array[i] = *it;
	}
}

template<class Type, std::size_t Size>
constexpr StaticArray<Type, Size>::StaticArray(Type arr[Size]) : _array() {
	for(std::size_t i = 0; i < size(); ++i)
		_array[i] = arr[i];
}

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
	_turn_to_heap(compare);

	for(std::size_t i = size() - 1; i > 0; --i) {
		std::swap(_array[i], _array[0]);
		_sift_down(0, i - 1, compare);
	}

}

namespace details {
	// Utility functions to calculate position of 'nodes' in the array
	inline static std::size_t heap_node_parent(std::size_t i) { return (i - 1) / 2; }
	inline static std::size_t heap_node_left_child(std::size_t i) { return 2 * i + 1; }
}

template<class Type, std::size_t Size>
template<class Compare>
void StaticArray<Type, Size>::_turn_to_heap(const Compare& compare) {
	for(std::size_t i = size() - 1; i > 0; --i) {
		_sift_down(i, size() - 1, compare);
	}
	_sift_down(0, size() - 1, compare); // Could be in the loop but std::size_t is unsigned, so --0 == max_value<size_t>.
	// Using any other type would require some metaprogramming to garantee to avoid overflow in big arrays on any platform
}
template<class Type, std::size_t Size>
template<class Compare>
void StaticArray<Type, Size>::_sift_down(std::size_t root, std::size_t end, const Compare& compare) {
	std::size_t child, swap;
	while((child = details::heap_node_left_child(root)) <= end) {
		swap = root;
		if(compare(_array[swap], _array[child])) {
			swap = child;
		}
		if(child < end && compare(_array[swap], _array[child + 1]))
			swap = child + 1;
		if(swap == root)
			return;
		else {
			std::swap(_array[root], _array[swap]);
			root = swap;
		}

	}
}

#endif// GUARD_STATIC_ARRAY_HPP__
