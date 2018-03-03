#ifndef GUARD_DOUBLE_LINKED_LIST_HPP__
#define GUARD_DOUBLE_LINKED_LIST_HPP__

#include <utility>
#include <functional>

template<class Type>
class DoubleLinkedList {
	public :
		// Construct an empty list
		constexpr DoubleLinkedList();
		// Construct a list containing the given elements
		constexpr DoubleLinkedList(const std::initializer_list<Type>&);

		~DoubleLinkedList();

		// Add an element at the beginning of the list
		void push_front(const Type&);
		void push_front(Type&&);

		// Add an element at the end of the list
		void push_back(const Type&);
		void push_back(Type&&);

		// Remove the first element
		void pop_front();
		// Remove the last element
		void pop_back();

		// Return the first element
		constexpr const Type& first() const;
		constexpr Type& first();
		// Return the last element
		constexpr const Type& last() const;
		constexpr Type& last();

		// Return the number of elements in the list
		constexpr std::size_t size() const;


	private:
		struct Node {
			Type value;
			Node* previous;
			Node* next;
		};

		Node* _first;
		Node* _last;
		std::size_t _size;

		template<class NodeType>
			struct basic_iterator {
				// Create a default iterator
				constexpr basic_iterator();
				// Implementation specific
				constexpr basic_iterator(NodeType*);
				// Generalized copy constructor
				template<class NT>
					constexpr basic_iterator(const basic_iterator<NT>&);

				// Return the value pointed to by the iterator
				constexpr const Type& operator*() const;
				constexpr Type& operator*();
				constexpr const Type* operator->() const;
				constexpr Type* operator->();

				// Advance to the next element
				basic_iterator& operator++();
				basic_iterator operator++(int);
				// Go back to the previous element
				basic_iterator& operator--();
				basic_iterator operator--(int);

				constexpr bool operator==(const basic_iterator<NodeType>&) const;
				constexpr bool operator!=(const basic_iterator<NodeType>&) const;

				private:
				friend basic_iterator<std::add_const_t<NodeType>>;
				NodeType* _pointer;

			};
	public:

		typedef basic_iterator<Node> iterator;
		typedef basic_iterator<const Node> const_iterator;

		// Return an iterator to the first element of the list
		constexpr iterator begin();
		constexpr const_iterator begin() const;

		// Return an iterator past the last element of the list
		constexpr iterator end();
		constexpr const_iterator end() const;

		// Sort the elements of the list according to the given comparison function (insertion sort)
		template<class Compare = std::less<Type>>
		void sort(const Compare& = Compare());


};
template<class Type>
constexpr DoubleLinkedList<Type>::DoubleLinkedList() : _first(nullptr), _last(nullptr), _size(0) {}
template<class Type>
constexpr DoubleLinkedList<Type>::DoubleLinkedList(const std::initializer_list<Type>& list) : _first(nullptr), _last(nullptr), _size(0) {
	for(auto it = list.begin(); it != list.end(); ++it)
		push_back(*it);
}
template<class Type>
DoubleLinkedList<Type>::~DoubleLinkedList() {
	Node* tmp;
	while(_first != nullptr) {
		tmp = _first;
		_first = _first->next;
		delete tmp;
	}
}

template<class Type>
void DoubleLinkedList<Type>::push_front(const Type& t) {
	if(_first == nullptr)
		_first = _last = new Node{ Type(t), nullptr, nullptr };
	else {
		_first = new Node{ Type(t), nullptr, _first };
		_first->next->previous = _first;
	}
	++_size;
}

template<class Type>
void DoubleLinkedList<Type>::push_front(Type&& t) {
	if(_first == nullptr)
		_first = _last = new Node{ Type(std::forward<Type>(t)), nullptr, nullptr };
	else {
		_first = new Node{ Type(std::forward<Type>(t)), nullptr, _first };
		_first->next->previous = _first;
	}
	++_size;
}

template<class Type>
void DoubleLinkedList<Type>::push_back(const Type& t) {
	if(_last == nullptr)
		_last = _first = new Node{ Type(t), nullptr, nullptr };
	else {
		_last = new Node{ Type(t), _last, nullptr };
		_last->previous->next = _last;
	}
	++_size;
}

template<class Type>
void DoubleLinkedList<Type>::push_back(Type&& t) {
	if(_last == nullptr)
		_last = _first = new Node{ Type(std::forward<Type>(t)), nullptr, nullptr };
	else {
		_last = new Node{ Type(std::forward<Type>(t)), _last, nullptr };
		_last->previous->next = _last;
	}
	++_size;
}

template<class Type>
constexpr const Type& DoubleLinkedList<Type>::first() const {
	return _first->value;
}
template<class Type>
constexpr Type& DoubleLinkedList<Type>::first() {
	return _first->value;
}
template<class Type>
constexpr const Type& DoubleLinkedList<Type>::last() const {
	return _last->value;
}
template<class Type>
constexpr Type& DoubleLinkedList<Type>::last() {
	return _last->value;
}

template<class Type>
constexpr std::size_t DoubleLinkedList<Type>::size() const {
	return _size;
}

template<class Type>
constexpr typename DoubleLinkedList<Type>::iterator DoubleLinkedList<Type>::begin() {
	return _first;
}

template<class Type>
constexpr typename DoubleLinkedList<Type>::const_iterator DoubleLinkedList<Type>::begin() const {
	return const_cast<DoubleLinkedList<Type>*>(this)->begin();
}

template<class Type>
constexpr typename DoubleLinkedList<Type>::iterator DoubleLinkedList<Type>::end() {
	return nullptr;
}

template<class Type>
constexpr typename DoubleLinkedList<Type>::const_iterator DoubleLinkedList<Type>::end() const {
	return const_cast<DoubleLinkedList<Type>*>(this)->begin();
}

template<class Type>
template<class Compare>
void DoubleLinkedList<Type>::sort(const Compare& compare) {
	if(size() < 2) return;
	// Iterate from the second element to the end
	for(auto it = ++begin(); it != end(); ++it) {
		auto before_jt = it;
		auto jt = before_jt--;
		// Iterate backward from the current position to the beginning, swapping values if they are not correctly ordered one in regard to the other
		for(; jt != begin() && compare(*jt, *before_jt); --jt, --before_jt) {
			std::swap(*jt, *before_jt);
		}
	}
}

template<class Type>
template<class T>
constexpr DoubleLinkedList<Type>::basic_iterator<T>::basic_iterator() : _pointer(nullptr) {}

template<class Type>
template<class T>
constexpr DoubleLinkedList<Type>::basic_iterator<T>::basic_iterator(T* node) : _pointer(node) {}

template<class Type>
template<class T>
template<class NT>
constexpr DoubleLinkedList<Type>::basic_iterator<T>::basic_iterator(const basic_iterator<NT>& it) : _pointer(it._pointer) {}

template<class Type>
template<class T>
constexpr const Type& DoubleLinkedList<Type>::basic_iterator<T>::operator*() const {
	return _pointer->value;
}

template<class Type>
template<class T>
constexpr Type& DoubleLinkedList<Type>::basic_iterator<T>::operator*() {
	return _pointer->value;
}

template<class Type>
template<class T>
constexpr const Type* DoubleLinkedList<Type>::basic_iterator<T>::operator->() const {
	return _pointer->value;
}
template<class Type>
template<class T>
constexpr Type* DoubleLinkedList<Type>::basic_iterator<T>::operator->() {
	return _pointer->value;
}

template<class Type>
template<class T>
typename DoubleLinkedList<Type>::template basic_iterator<T>& DoubleLinkedList<Type>::basic_iterator<T>::operator++() {
	_pointer = _pointer->next;
	return *this;
}
template<class Type>
template<class T>
typename DoubleLinkedList<Type>::template basic_iterator<T> DoubleLinkedList<Type>::basic_iterator<T>::operator++(int) {
	auto tmp = *this;
	++*this;
	return tmp;
}
template<class Type>
template<class T>
typename DoubleLinkedList<Type>::template basic_iterator<T>& DoubleLinkedList<Type>::basic_iterator<T>::operator--() {
	_pointer = _pointer->previous;
	return *this;
}
template<class Type>
template<class T>
typename DoubleLinkedList<Type>::template basic_iterator<T> DoubleLinkedList<Type>::basic_iterator<T>::operator--(int) {
	auto tmp = *this;
	--*this;
	return tmp;
}

template<class Type>
template<class T>
constexpr bool DoubleLinkedList<Type>::basic_iterator<T>::operator==(const basic_iterator<T>& n) const {
	return n._pointer == _pointer;
}
template<class Type>
template<class T>
constexpr bool DoubleLinkedList<Type>::basic_iterator<T>::operator!=(const basic_iterator<T>& n) const {
	return !(n == *this);
}

#endif
