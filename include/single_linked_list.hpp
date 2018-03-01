#ifndef GUARD_SINGLE_LINKED_LIST_HPP__
#define GUARD_SINGLE_LINKED_LIST_HPP__

#include <initializer_list>
#include <algorithm>

template<class Type>
class SingleLinkedList {
	public :
		constexpr SingleLinkedList();
		constexpr SingleLinkedList(const std::initializer_list<Type>&);
		~SingleLinkedList();

		void push_front(const Type&);
		void push_front(Type&&);
		void pop_front();
		const Type& first() const;
		Type& first();

		constexpr std::size_t size() const;


	private:
		struct Node {
			Type value;
			Node* next;
		};

		template<class T>
			struct basic_iterator {
				constexpr basic_iterator(T*);
				constexpr basic_iterator();
				//constexpr basic_iterator(const basic_iterator&);
				template<class C>
					constexpr basic_iterator(const basic_iterator<C>&);

				constexpr const Type& operator*() const;
				constexpr Type& operator*();

				constexpr const Type* operator->() const;
				constexpr Type* operator->();

				basic_iterator& operator++();
				basic_iterator operator++(int);

				template<class U>
					constexpr bool operator==(const basic_iterator<U>& node) const;
				template<class U>
					constexpr bool operator!=(const basic_iterator<U>& node) const;

				private:
				T* _pointer;
			};

		Node* _first;
		std::size_t _size;

	public:
		typedef basic_iterator<Node> iterator;
		typedef basic_iterator<const Node> const_iterator;

		constexpr iterator begin();
		constexpr const_iterator begin() const;

		constexpr iterator end();
		constexpr const_iterator end() const;

		void erase(const iterator&) const;
		iterator find(const Type& value);
		template<class Functor>
			iterator find(const Functor& value);

};

template<class Type>
constexpr SingleLinkedList<Type>::SingleLinkedList() : _first(nullptr), _size(0) {}

template<class Type>
constexpr SingleLinkedList<Type>::SingleLinkedList(const std::initializer_list<Type>& list) : _first(nullptr), _size(list.size()) {
	for(auto it = list.begin(); it != list.end(); ++it) {
		_first = new Node{ Type(*it), _first };
	}
}

template<class Type>
SingleLinkedList<Type>::~SingleLinkedList() {
	Node* tmp;
	while(_first != nullptr) {
		tmp = _first;
		_first = _first->next;
		delete tmp;
	}
}

template<class Type>
void SingleLinkedList<Type>::push_front(const Type& t) {
	_first = new Node{ Type(t), _first };
}

template<class Type>
void SingleLinkedList<Type>::push_front(Type&& t) {
	_first = new Node{ Type(std::forward<Type>(t)), _first };
}

template<class Type>
void SingleLinkedList<Type>::pop_front() {
	Node* tmp = _first;
	_first = _first->next;
	delete tmp;
}

template<class Type>
const Type& SingleLinkedList<Type>::first() const {
	return _first->value;
}

template<class Type>
Type& SingleLinkedList<Type>::first() {
	return _first->value;
}

template<class Type>
constexpr std::size_t SingleLinkedList<Type>::size() const {
	return _size;
}

template<class Type>
constexpr typename SingleLinkedList<Type>::iterator SingleLinkedList<Type>::begin() {
	return iterator(_first);
}

template<class Type>
constexpr typename SingleLinkedList<Type>::const_iterator SingleLinkedList<Type>::begin() const {
	return _first;
}

template<class Type>
constexpr typename SingleLinkedList<Type>::iterator SingleLinkedList<Type>::end() {
	return nullptr;
}

template<class Type>
constexpr typename SingleLinkedList<Type>::const_iterator SingleLinkedList<Type>::end() const {
	return nullptr;
}

template<class Type>
void SingleLinkedList<Type>::erase(const iterator& el) const {
	Node* tmp = el->next;
	std::swap(el->value, tmp->value);
	el->next = tmp->next;
	delete tmp;
}

template<class Type>
typename SingleLinkedList<Type>::iterator SingleLinkedList<Type>::find(const Type& val) {
	auto it = begin();
	for(; it != end(); ++it)
		if(*it == val) break;
	return it;
}

template<class Type>
template<class Functor>
typename SingleLinkedList<Type>::iterator SingleLinkedList<Type>::find(const Functor& func) {
	auto it = begin();
	for(; it != end(); ++it)
		if(fun(*it)) break;
	return it;
}
template<class Type>
template<class T>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator() : _pointer(nullptr) {}

template<class Type>
template<class T>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator(T* p) : _pointer(p) {}

template<class Type>
template<class T>
template<class C>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator(const basic_iterator<C>& p) : _pointer(p._pointer) {}

template<class Type>
template<class T>
constexpr const Type& SingleLinkedList<Type>::basic_iterator<T>::operator*() const {
	return _pointer->value;
}

template<class Type>
template<class T>
constexpr Type& SingleLinkedList<Type>::basic_iterator<T>::operator*() {
	return _pointer->value;
}

template<class Type>
template<class T>
constexpr const Type* SingleLinkedList<Type>::basic_iterator<T>::operator->() const {
	return &_pointer->value;
}
template<class Type>
template<class T>
constexpr Type* SingleLinkedList<Type>::basic_iterator<T>::operator->() {
	return &_pointer->value;
}

template<class Type>
template<class T>
typename SingleLinkedList<Type>::template basic_iterator<T>& SingleLinkedList<Type>::basic_iterator<T>::operator++() {
	_pointer = _pointer->next;
	return *this;
}
template<class Type>
template<class T>
typename SingleLinkedList<Type>::template basic_iterator<T> SingleLinkedList<Type>::basic_iterator<T>::operator++(int) {
	Node tmp = *this;
	++*this;
	return tmp;
}

template<class Type>
template<class T>
template<class U>
constexpr bool SingleLinkedList<Type>::basic_iterator<T>::operator==(const basic_iterator<U>& it) const {
	return it._pointer == _pointer;
}
template<class Type>
template<class T>
template<class U>
constexpr bool SingleLinkedList<Type>::basic_iterator<T>::operator!=(const basic_iterator<U>& node) const {
	return !(*this == node);
}
#endif // GUARD_SINGLE_LINKED_LIST_HPP__

