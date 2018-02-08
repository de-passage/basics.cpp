#ifndef GUARD_SINGLE_LINKED_LIST_HPP__
#define GUARD_SINGLE_LINKED_LIST_HPP__

#include <initializer_list>
#include <algorithm>

namespace dpsg {
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
				template<class T>
					struct Node {
						T* value;
						Node* next;

						constexpr const T& operator*() const;
						constexpr T& operator*();

						constexpr const T* operator->() const;
						constexpr T* operator->();

						Node& operator++();
						Node operator++(int);

						constexpr bool operator==(const Node& node) const;
						constexpr bool operator==(const Node* node) const;
						constexpr bool operator!=(const Node& node) const;
						constexpr bool operator!=(const Node* node) const;

					};
				Node<Type>* _first;
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
		constexpr SingleLinkedList<Type>::SingleLinkedList() : _first(nullptr), _size(0) {}

	template<class Type>
		constexpr SingleLinkedList<Type>::SingleLinkedList(const std::initializer_list<Type>& list) : _first(nullptr), _size(list.size()) {
			for(auto it = list.begin(); it != list.end(); ++it) {
				_first = new Node<Type>{ new Type(*it), _first };
			}
		}

	template<class Type>
		SingleLinkedList<Type>::~SingleLinkedList() {
			Node<Type>* tmp;
			while(_first != nullptr) {
				tmp = _first;
				_first = _first->next;
				delete tmp;
			}
		}

	template<class Type>
		void SingleLinkedList<Type>::push_front(const Type& t) {
			_first = new Node<Type>{ new Type(t), _first };
		}

	template<class Type>
		void SingleLinkedList<Type>::push_front(Type&& t) {
			_first = new Node<Type>{ new Type(std::forward<Type>(t)), _first };
		}

	template<class Type>
		void SingleLinkedList<Type>::pop_front() {
			Node<Type>* tmp = _first;
			_first = _first->next;
			delete tmp->value;
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
			return *_first;
		}

	template<class Type>
		constexpr typename SingleLinkedList<Type>::const_iterator SingleLinkedList<Type>::begin() const {
			return *_first;
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
		template<class T>
		constexpr const T& SingleLinkedList<Type>::Node<T>::operator*() const {
			return value;
		}

	template<class Type>
		template<class T>
		constexpr T& SingleLinkedList<Type>::Node<T>::operator*() {
			return value;
		}

	template<class Type>
		template<class T>
		constexpr const T* SingleLinkedList<Type>::Node<T>::operator->() const {
			return &value;
		}
	template<class Type>
		template<class T>
		constexpr T* SingleLinkedList<Type>::Node<T>::operator->() {
			return &value;
		}

	template<class Type>
		template<class T>
		typename SingleLinkedList<Type>::template Node<T>& SingleLinkedList<Type>::Node<T>::operator++() {
			return *this = *next;
		}
	template<class Type>
		template<class T>
		typename SingleLinkedList<Type>::template Node<T> SingleLinkedList<Type>::Node<T>::operator++(int) {
			Node tmp = *this;
			++*this;
			return tmp;
		}

	template<class Type>
		template<class T>
		constexpr bool SingleLinkedList<Type>::Node<T>::operator==(const Node& node) const {
			return node.value == value;
		}
	template<class Type>
		template<class T>
		constexpr bool SingleLinkedList<Type>::Node<T>::operator!=(const Node& node) const {
			return !(this == node);
		}
}
#endif // GUARD_SINGLE_LINKED_LIST_HPP__

