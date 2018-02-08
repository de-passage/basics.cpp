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
				template<class T>
					struct Node {
						T* value;
						Node* next;
						Node* previous;

						constexpr const T& operator*() const;
						constexpr T& operator*();

						constexpr const T* operator->() const;
						constexpr T* operator->();

						Node& operator++();
						Node operator++(int);
						Node& operator--();
						Node operator--(int);

						bool operator==(const Node&);
						bool operator!=(const Node&);

					};
				Node<Type>* _first;
				Node<Type>* _last;
				std::size_t _size;

			public:
				typedef Node<Type> iterator;
				typedef Node<const Type> const_iterator;

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
			Node<Type>* tmp;
			while(_first != nullptr) {
				tmp = _first;
				_first = _first->next;
				delete tmp->value;
				delete tmp;
			}
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_front(const Type& t) {
			if(_first == nullptr)
				_first = _last = new Node<Type>{ new Type(t), nullptr, nullptr };
			else
				_first = new Node<Type>{ new Type(t), nullptr, _first };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_front(Type&& t) {
			if(_first == nullptr)
				_first = _last = new Node<Type>{ new Type(std::forward<Type>(t)), nullptr, nullptr };
			else
				_first = new Node<Type>{ new Type(std::forward<Type>(t)), nullptr, _first };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_back(const Type& t) {
			if(_last == nullptr)
				_last = _last = new Node<Type>{ new Type(t), nullptr, nullptr };
			else
				_last = new Node<Type>{ new Type(t), _last, nullptr };
		}

	template<class Type>
		void DoubleLinkedList<Type>::push_back(Type&& t) {
			if(_last == nullptr)
				_last = _last = new Node<Type>{ new Type(std::forward<Type>(t)), nullptr, nullptr };
			else
				_last = new Node<Type>{ new Type(std::forward<Type>(t)), _last, nullptr };
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
		constexpr const T& DoubleLinkedList<Type>::Node<T>::operator*() const {
			return *value;
		}

	template<class Type>
		template<class T>
		constexpr T& DoubleLinkedList<Type>::Node<T>::operator*() {
			return *value;
		}

	template<class Type>
		template<class T>
		constexpr const T* DoubleLinkedList<Type>::Node<T>::operator->() const {
			return value;
		}
	template<class Type>
		template<class T>
		constexpr T* DoubleLinkedList<Type>::Node<T>::operator->() {
			return value;
		}

	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template Node<T>& DoubleLinkedList<Type>::Node<T>::operator++() {
			return *this = *next;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template Node<T> DoubleLinkedList<Type>::Node<T>::operator++(int) {
			Node<T> tmp = *this;
			++*this;
			return tmp;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template Node<T>& DoubleLinkedList<Type>::Node<T>::operator--() {
			return *this = *previous;
		}
	template<class Type>
		template<class T>
		typename DoubleLinkedList<Type>::template Node<T> DoubleLinkedList<Type>::Node<T>::operator--(int) {
			Node<T> tmp = *this;
			--*this;
			return tmp;
		}

	template<class Type>
		template<class T>
		bool DoubleLinkedList<Type>::Node<T>::operator==(const Node& n) {
			return n.value == value;
		}
	template<class Type>
		template<class T>
		bool DoubleLinkedList<Type>::Node<T>::operator!=(const Node& n) {
			return !(n == *this);
		}
}

#endif
