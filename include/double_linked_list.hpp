#ifndef GUARD_DOUBLE_LINKED_LIST_HPP__
#define GUARD_DOUBLE_LINKED_LIST_HPP__

#include <utility>

namespace dpsg {
	template<class Type>
		class DoubleLinkedList {
			public :
				constexpr DoubleLinkedList();
				constexpr DoubleLinkedList(const std::initializer_list<Type>&);
				~DoubleLinkedList();

				void push_front(const Type&);
				void push_front(Type&&);
				void push_back(const Type&);
				void push_back(Type&&);

				void pop_front();
				void pop_back();

				constexpr const Type& first() const;
				constexpr Type& first();
				constexpr const Type& last() const;
				constexpr Type& last();

				constexpr std::size_t size() const;


			private:
				struct Node {
					Type value;
					Node* next;
					Node* previous;
				};
				template<class NodeType>
					struct basic_iterator {
						constexpr basic_iterator();
						constexpr basic_iterator(NodeType*);
						template<class NT>
							constexpr basic_iterator(const basic_iterator<NT>&);

						constexpr const Type& operator*() const;
						constexpr Type& operator*();

						constexpr const Type* operator->() const;
						constexpr Type* operator->();

						basic_iterator& operator++();
						basic_iterator operator++(int);
						basic_iterator& operator--();
						basic_iterator operator--(int);

						constexpr bool operator==(const basic_iterator<NodeType>&) const;
						constexpr bool operator!=(const basic_iterator<NodeType>&) const;

						private:
						NodeType* _pointer;

					};
				Node* _first;
				Node* _last;
				std::size_t _size;

			public:
				typedef basic_iterator<Node> iterator;
				typedef basic_iterator<const Node> const_iterator;

				constexpr iterator begin();
				constexpr const_iterator begin() const;

				constexpr iterator end();
				constexpr const_iterator end() const;


		};
	template<class Type>
		constexpr DoubleLinkedList<Type>::DoubleLinkedList() : _first(nullptr), _last(nullptr), _size(0) {}
	template<class Type>
		constexpr DoubleLinkedList<Type>::DoubleLinkedList(const std::initializer_list<Type>& list) : _first(nullptr), _last(nullptr), _size(list.size()) {
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
			else
				_first = new Node{ Type(t), nullptr, _first };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_front(Type&& t) {
			if(_first == nullptr)
				_first = _last = new Node{ Type(std::forward<Type>(t)), nullptr, nullptr };
			else
				_first = new Node{ Type(std::forward<Type>(t)), nullptr, _first };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_back(const Type& t) {
			if(_last == nullptr)
				_last = _last = new Node{ Type(t), nullptr, nullptr };
			else
				_last = new Node{ Type(t), _last, nullptr };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_back(Type&& t) {
			if(_last == nullptr)
				_last = _last = new Node{ Type(std::forward<Type>(t)), nullptr, nullptr };
			else
				_last = new Node{ Type(std::forward<Type>(t)), _last, nullptr };
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
			return *_pointer->value;
		}

	template<class Type>
		template<class T>
		constexpr Type& DoubleLinkedList<Type>::basic_iterator<T>::operator*() {
			return *_pointer->value;
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
			return _pointer = _pointer->next;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template basic_iterator<T> DoubleLinkedList<Type>::basic_iterator<T>::operator++(int) {
			Node tmp = *this;
			++*this;
			return tmp;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template basic_iterator<T>& DoubleLinkedList<Type>::basic_iterator<T>::operator--() {
			return _pointer = _pointer->previous;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template basic_iterator<T> DoubleLinkedList<Type>::basic_iterator<T>::operator--(int) {
			Node tmp = *this;
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
}

#endif
