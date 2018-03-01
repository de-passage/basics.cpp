#ifndef GUARD_HASH_TABLE_HPP__
#define GUARD_HASH_TABLE_HPP__

#include <type_traits>
#include <string>
#include <stdexcept>
#include "single_linked_list.hpp"

namespace details {
	// Is true_type if T is the same type as one of the types in the Args list
	template<class T, class...Args> struct is_one_of;
	template<class T, class ...Args> struct is_one_of<T, T, Args...> : std::true_type {};
	template<class T, class U, class ...Args> struct is_one_of<T, U, Args...> : is_one_of<T, Args...> {};
	template<class T> struct is_one_of<T> : std::false_type {};

	template<class T> struct decay { typedef T value; };
	template<class T> struct decay<const T*> { typedef T value; };
	template<class T> struct decay<T*> { typedef T value; };
	template<class T>
		using decay_t = typename decay<T>::value;
}

template<class T, class = void>
struct hash;

template<class T>
struct hash<T, std::enable_if_t<std::is_integral<T>::value>> {
	std::size_t operator()(const T& t) { return t; }
};

template<class T>
struct hash<T, std::enable_if_t<details::is_one_of<details::decay_t<std::decay_t<T>>, char, wchar_t>::value>> {
	std::size_t operator()(const T p) {
		return hash<std::basic_string<details::decay_t<T>>>()(std::basic_string<details::decay_t<T>>(p));
	}
};

template<class T>
struct hash<T, std::enable_if_t<details::is_one_of<std::decay_t<T>, std::string, std::wstring>::value>> {
	std::size_t operator()(const T& t) { 
		// djb2 by Dan Berstein
		std::size_t hash = 5381;

		for(auto c = t.begin(); c != t.end(); ++c)
			hash = ((hash << 5) + hash) + *c;

		return hash;
	}
};

template<class Type, class HashFunctor = hash<Type>>
struct HashTable {
	HashTable();
	HashTable(const std::initializer_list<Type>&);
	~HashTable();

	void insert(const Type&);
	void erase(const Type&);
	template<typename Functor>
		Type find(Functor) const;
	template<typename Functor>
		Type& find(Functor);
	Type operator[](const Type&) const;
	Type& operator[](const Type&);

	private:
	std::size_t _size, _capacity;
	SingleLinkedList<Type>* _storage;

	void _resize();
	SingleLinkedList<Type>& _store_for(const Type&);
	const SingleLinkedList<Type>& _store_for(const Type&)const;

};

template<class T, class H>
HashTable<T, H>::HashTable() : _size(0), _capacity(2), _storage(new SingleLinkedList<T>[2]) {}

template<class T, class H>
HashTable<T, H>::HashTable(const std::initializer_list<T>& list) : _size(list.size()), _capacity(2), _storage(new SingleLinkedList<T>[_capacity]) {}

template<class T, class H>
void HashTable<T, H>::insert(const T& val) {
	std::size_t h = H()(val);
	std::size_t pos = h % _capacity;
	SingleLinkedList<T>& store = _storage[pos];

	for(auto it = store.begin(); it != store.end(); ++it)
		if(*it == val)
			throw std::runtime_error("HashTable insertion error: an element with the same value exists already");
	_size++;

	if(_size >= _capacity) {
		_resize();
		pos = h % _capacity;
	}

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
template<typename Functor>
T HashTable<T, H>::find(Functor) const {
}

template<class T, class H>
template<typename Functor>
T& HashTable<T, H>::find(Functor) {
}

template<class T, class H>
T HashTable<T, H>::operator[](const T& val) const {
	return const_cast<HashTable<T, H>*>(this)->operator[](val);
}

template<class T, class H>
T& HashTable<T, H>::operator[](const T& val) {
	auto& store = _store_for(val);
	auto it = store.find(val);
	if(it == store.end()) {
		throw std::out_of_range("HashTable::operator[] : the given key is not in the table");
	}
	return *it;
}

template<class T, class H>
HashTable<T, H>::~HashTable() {
	delete[] _storage;
}

template<class T, class H>
void HashTable<T,H>::_resize() {
	std::size_t old_capacity = _capacity;
	_capacity *= 2;
	SingleLinkedList<T>* new_array = new SingleLinkedList<T>[_capacity];
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
#endif // GUARD_HASH_TABLE_HPP__
