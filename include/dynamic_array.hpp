#ifndef GUARD_DYNAMIC_ARRAY_HPP__
#define GUARD_DYNAMIC_ARRAY_HPP__

#include <initializer_list>
#include <utility>
#include <stdexcept>
#include <sstream>

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
		template<class Function = std::less<Type>>
			void sort(const Function& = std::less<Type>());

		typedef Type* iterator;
		typedef const iterator const_iterator;

		// Return an iterator to the first element
		iterator begin();
		const_iterator begin() const;

		// Return an iterator past the last element
		iterator end();
		const_iterator end() const;


	private:
		std::size_t _size;
		std::size_t _capacity;
		Type* _array;

		template<class Function>
			void _sort(const Function&, std::size_t, std::size_t);
		template<class Function>
			std::size_t _partition(const Function&, std::size_t, std::size_t);
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
	if(_size >= _capacity) {
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
	return _capacity;
}

template<class Type>
void DynamicArray<Type>::resize(std::size_t new_capacity) {
	Type* tmp = new Type[new_capacity];

	std::size_t max_bound = std::min(new_capacity, _size);

	for(std::size_t i = 0; i < max_bound; ++i)
		tmp[i] = std::move(_array[i]);

	std::swap(tmp, _array);
	delete[] tmp;

	_capacity = new_capacity;
}

template<class Type>
typename DynamicArray<Type>::iterator DynamicArray<Type>::begin() {
	return _array;
}

template<class Type>
typename DynamicArray<Type>::const_iterator DynamicArray<Type>::begin() const {
	return _array;
}

template<class Type>
typename DynamicArray<Type>::iterator DynamicArray<Type>::end() {
	return _array + size();
}

template<class Type>
typename DynamicArray<Type>::const_iterator DynamicArray<Type>::end() const {
	return _array + size();
}

template<class Type>
template<class Function>
void DynamicArray<Type>::sort(const Function& compare) {
	_sort(compare, 0, size() - 1);
}

namespace details {
	static inline std::size_t median_of_three(std::size_t top, std::size_t middle, std::size_t bottom) { 

		return std::max(std::min(top, middle), std::min(std::max(top, middle), bottom)); // Simplified

		/* Sorting network returning the middle element
		 * Sorts the 3 values by checking every possible swap

		 std::size_t ntop = std::min(top, middle); // inverting middle and top if needed
		 std::size_t nmid = std::max(top, middle);

		 std::size_t nnmid = std::min(nmid, bottom); //  inverting middle and bottom if needed

		// The next operations complete the sort but are not needed here
		std::size_t nbot = std::max(nmid, bottom);

		std::size_t nntop = std::min(ntop, nbot); // inverting top and bottom if needed
		std::size_t nnbot = std::max(ntop, nbot);

		return nnmid;
		*/
	}
}

template<class Type>
template<class Function>
void DynamicArray<Type>::_sort(const Function& compare, std::size_t beg, std::size_t end) {
	if(beg < end) {
		std::size_t p = _partition(compare, beg, end);
		_sort(compare, beg, p);
		_sort(compare, p + 1, end);
	}
}

template<class Type>
template<class Function>
std::size_t DynamicArray<Type>::_partition(const Function& compare, std::size_t beg, std::size_t end) {
	// if beg + end overflows, the position will not be exactly right but size_t is unsigned, garanteeing a value btw 0 and end, so the result won't cause a segfault
	std::size_t pivot = details::median_of_three(_array[beg], _array[end], _array[(beg + end) / 2]);

	std::size_t i = beg;
	std::size_t j = end;

	while(true) {
		while( compare(_array[i], pivot) ){ // Find the first element from the begining which is not in place compared with the pivot
			++i; 
		}

		while( compare(pivot, _array[j]) ){ // Find the first element from the end which is not in place.
			--j;
		}

		// if i >= j then all elements are on the right side of the pivot. return the position of the pivot
		if(i >= j) return j;
		// swap the out of place elements.
		std::swap(_array[i], _array[j]);
	}
}

#endif // GUARD_DYNAMIC_ARRAY_HPP__

