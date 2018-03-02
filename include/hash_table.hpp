#ifndef GUARD_HASH_TABLE_HPP__
#define GUARD_HASH_TABLE_HPP__

#include <type_traits>
#include <string>
#include <stdexcept>
#include "single_linked_list.hpp"
#include "details/hash.hpp"

template<class Type, class HashFunctor = hash<Type>>
struct HashTable {
	// Constructs an empty hash table
	HashTable();
	// Constructs a hash table initialized with the list of parameters
	HashTable(const std::initializer_list<Type>&);

	~HashTable();

	// Insert a new value into the table
	void insert(const Type&);

	// Remove the given value from the table
	void erase(const Type&);

	// Return the value matching the argument.
	// Throw a std::runtime_error if the value is not in the table
	Type operator[](const Type&) const;
	Type& operator[](const Type&);

	private:
	std::size_t _size, _capacity;
	SingleLinkedList<Type>* _storage;

	void _resize();
	SingleLinkedList<Type>& _store_for(const Type&);
	const SingleLinkedList<Type>& _store_for(const Type&)const;

	public:
	// Structure that may contain a value or not
	template<class T>
		struct Maybe {
			constexpr Maybe(T* = nullptr);
			template<class U>
				constexpr Maybe(const Maybe<U>&);

			// Return the contained value if it exists. Throw otherwise
			const T& operator*() const;
			const T* operator->() const;
			T& operator*();
			T* operator->();

			// Evaluate to true a value is contained, false otherwise
			operator bool() const;
			private:
			friend Maybe<std::add_const_t<T>>;
			T* _pointer;
		};

	// Returns a dereferenceable structure that may contain the searched value
	// Implicitely convertible to bool with true value if the searched value is contained, false value if the value is not contained
	Maybe<const Type> find(const Type&) const;
	Maybe<Type> find(const Type&);

	// Return true if the value is in the table, false otherwise
	bool contains(const Type&) const;
};

template<class T, class H>
HashTable<T, H>::HashTable() : _size(0), _capacity(2), _storage(new SingleLinkedList<T>[2]) {}

template<class T, class H>
HashTable<T, H>::HashTable(const std::initializer_list<T>& list) : _size(list.size()), _capacity(2), _storage(new SingleLinkedList<T>[_capacity]) {}

template<class T, class H>
void HashTable<T, H>::insert(const T& val) {
	//Hash the value then find the associated address
	std::size_t h = H()(val);
	std::size_t pos = h % _capacity;
	SingleLinkedList<T>& store = _storage[pos];

	// Throw if the value is already in the table
	for(auto it = store.begin(); it != store.end(); ++it)
		if(*it == val)
			throw std::runtime_error("HashTable insertion error: an element with the same value exists already");
	_size++;

	// Resize and adjust the position if needed
	// note that the comparison is completely arbitrary, benchmarking would be required to determine the optimal
	// point at which the array needs resizing
	if(_size >= _capacity) {
		_resize();
		pos = h % _capacity;
	}

	// Push in the list at the right position, done
	_storage[pos].push_front(val);
}

template<class T, class H>
void HashTable<T, H>::erase(const T& val) {
	SingleLinkedList<T>& store = _store_for(val);

	auto it = store.find(val);
	if(it != store.end())
		store.erase(it);
}

template<class T, class H>
HashTable<T, H>::Maybe<const T> HashTable<T, H>::find(const T& value) const {
	return const_cast<HashTable<T, H>*>(this)->find(value);
}

template<class T, class H>
HashTable<T, H>::Maybe<T> HashTable<T, H>::find(const T& value) {
	auto& store = _store_for(value);
	auto it = store.find(value);
	return Maybe<T>(it == store.end() ? nullptr : &*it);
}

template<class T, class H>
T HashTable<T, H>::operator[](const T& val) const {
	return const_cast<HashTable<T, H>*>(this)->operator[](val);
}

template<class T, class H>
T& HashTable<T, H>::operator[](const T& value) {
	auto maybe = find(value);
	if(!maybe)
		throw std::out_of_range("HashTable::operator[] : the given key is not in the table");
	return *maybe;
}

template<class T, class H>
bool HashTable<T, H>::contains(const T& value) const {
	return find(value);
}

template<class T, class H>
HashTable<T, H>::~HashTable() {
	delete[] _storage;
}

template<class T, class H>
void HashTable<T,H>::_resize() {

	std::size_t old_capacity = _capacity;
	_capacity *= 2; // arbitrary and most likely inefficient


	SingleLinkedList<T>* new_array = new SingleLinkedList<T>[_capacity];
	// recalculate every position of the existing elements, then insert them in the new array
	for(std::size_t i = 0; i < old_capacity; ++i) {
		for(auto it = _storage[i].begin(); it != _storage[i].end(); ++it) {
			new_array[H()(*it) % _capacity].push_front(*it);
		}
	}

	std::swap(new_array, _storage);
	delete[] new_array;
}


template<class Type, class H>
SingleLinkedList<Type>& HashTable<Type, H>::_store_for(const Type& val) {
	std::size_t h = H()(val);
	std::size_t pos = h % _capacity;
	return _storage[pos];
}

template<class Type, class H>
const SingleLinkedList<Type>& HashTable<Type, H>::_store_for(const Type& val) const {
	return const_cast<HashTable<Type, H>*>(this)->_store_for(val);
}

template<class Type, class H>
template<class T>
constexpr HashTable<Type, H>::Maybe<T>::Maybe(T* pointer) : _pointer(pointer) {}

template<class Type, class H>
template<class T>
template<class U>
constexpr HashTable<Type, H>::Maybe<T>::Maybe(const Maybe<U>& mb) : _pointer(mb._pointer) {}

template<class Type, class H>
template<class T>
const T& HashTable<Type, H>::Maybe<T>::operator*() const {
	return const_cast<Maybe<T>*>(this)->operator*();
}

template<class Type, class H>
template<class T>
const T* HashTable<Type, H>::Maybe<T>::operator->() const {
	return const_cast<Maybe<T>*>(this)->operator();
}

template<class Type, class H>
template<class T>
T& HashTable<Type, H>::Maybe<T>::operator*() {
	if(!_pointer) throw std::runtime_error("HashTable::Maybe error: dereferencing null pointer");
	return *_pointer;
}

template<class Type, class H>
template<class T>
T* HashTable<Type, H>::Maybe<T>::operator->() {
	return _pointer ? _pointer : throw std::runtime_error("HashTable::Maybe error: dereferencing null pointer");
}

template<class Type, class H>
template<class T>
HashTable<Type, H>::Maybe<T>::operator bool() const {
	return _pointer;
}

#endif // GUARD_HASH_TABLE_HPP__
