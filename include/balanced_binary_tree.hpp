#ifndef GUARD_BALANCED_BINARY_TREE_HPP__
#define GUARD_BALANCED_BINARY_TREE_HPP__

#include <utility>
#include <initializer_list>
#include "details/balanced_binary_tree_node.hpp"
#include "single_linked_list.hpp"

template<class Type>
class BalancedBinaryTree {
	typedef details::BalancedBinaryTreeNode<Type> Node;
	public:
	constexpr BalancedBinaryTree();
	constexpr BalancedBinaryTree(const std::initializer_list<Type>&);
	~BalancedBinaryTree();

	void insert(const Type&);

	const Type& find(const Type&) const;
	Type& find(const Type&);

	private:
	Node* _root;
	std::size_t _size;

	static void _delete_branch(Node*);

	public:
	struct iterator {
		constexpr iterator();
		constexpr iterator(Node*);

		iterator& operator++();
		iterator& operator++(int);
		iterator& operator--();
		iterator& operator--(int);

		const Type& operator*() const;
		const Type* operator->() const;

		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;

		private:
		SingleLinkedList<Node*> _path;

		void descend_left();
		void descend_right();
		void go_left_branch();
		void go_right_branch();
		void ascend_left();
		void ascend_right();
	};

	typedef iterator const_iterator;

	const_iterator begin() const;
	const_iterator end() const;

};

template<class Type>
constexpr BalancedBinaryTree<Type>::BalancedBinaryTree() : _root(nullptr), _size(0) {}

template<class Type>
constexpr BalancedBinaryTree<Type>::BalancedBinaryTree(const std::initializer_list<Type>& list) : _root(nullptr), _size(0) {
	for(auto it = list.begin(); it != list.end(); ++it) {
		insert(*it);
	}
}

template<class Type>
void BalancedBinaryTree<Type>::insert(const Type& value) {
	if(_root)
		_root = _root->insert(value);
	else
		_root = new details::BalancedBinaryTreeNode<Type>(value);
}

template<class Type>
typename BalancedBinaryTree<Type>::const_iterator BalancedBinaryTree<Type>::begin() const {
	return { _root };
}

template<class Type>
typename BalancedBinaryTree<Type>::const_iterator BalancedBinaryTree<Type>::end() const {
	return {};
}

template<class Type>
BalancedBinaryTree<Type>::~BalancedBinaryTree() {
	if(_root != nullptr) delete _root;
}

template<class Type>
constexpr BalancedBinaryTree<Type>::iterator::iterator() : _path() {}
template<class Type>
constexpr BalancedBinaryTree<Type>::iterator::iterator(Node* _root) : _path() {
	while(_root != nullptr) {
		_path.push_front(_root);
		_root = _root->lhv;
	}
}

template<class Type>
typename BalancedBinaryTree<Type>::iterator& BalancedBinaryTree<Type>::iterator::operator++() {
	auto front = _path.first();
	if(front->lhv == nullptr && front->rhv == nullptr) { // Leaf
		_path.pop_front();
		if(_path.first()->rhv == front) {// we were in right node
			ascend_right();
		} 
		// else we were in left node and now on the right value
	}
	else { // Middle node, 
		go_right_branch();
		if(front != _path.first()) {
			descend_left();
		}
		else {
			ascend_right();
		}
	}

	return *this;
}

template<class Type>
typename BalancedBinaryTree<Type>::iterator& BalancedBinaryTree<Type>::iterator::operator++(int) {
	iterator it = *this;
	++*this;
	return it;
}

template<class Type>
typename BalancedBinaryTree<Type>::iterator& BalancedBinaryTree<Type>::iterator::operator--() {
	auto front = _path.first();
	if(front->lhv == nullptr && front->rhv == nullptr) { // Leaf
		_path.pop_front();
		if(_path.first()->lhv == front) {// we were in left node
			std::cout << "We should have been here" << std::endl;
			ascend_left();
		} 
	}
	else { // Middle node, 
		go_left_branch();
		if(front != _path.first()) {
			descend_right();
		}
		else {
			ascend_left();
		}
	}

	return *this;
}
template<class Type>
typename BalancedBinaryTree<Type>::iterator& BalancedBinaryTree<Type>::iterator::operator--(int) {
	iterator it = *this;
	--*this;
	return it;
}

template<class Type>
const Type& BalancedBinaryTree<Type>::iterator::operator*() const {
	return _path.first()->value;
}

template<class Type>
const Type* BalancedBinaryTree<Type>::iterator::operator->() const {
	return &_path.first()->value;
}

template<class Type>
bool BalancedBinaryTree<Type>::iterator::operator==(const iterator& it) const {
	if(_path.size() == 0 && it._path.size() == 0) return true;
	return _path.size() == it._path.size() && _path.first() == it._path.first();
}

template<class Type>
bool BalancedBinaryTree<Type>::iterator::operator!=(const iterator& it) const {
	return !(*this == it);
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::descend_left() {
	if(_path.size() == 0) return;
	while(_path.first()->lhv != nullptr) { 
		_path.push_front(_path.first()->lhv); 
	}
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::descend_right() {
	if(_path.size() == 0) return;
	while(_path.first()->rhv != nullptr) { 
		_path.push_front(_path.first()->rhv); 
	}
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::go_left_branch() {
	if(_path.size() != 0 && _path.first()->lhv != nullptr) {
		_path.push_front(_path.first()->lhv);
	}
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::go_right_branch() {
	if(_path.size() != 0 && _path.first()->rhv != nullptr) {
		_path.push_front(_path.first()->rhv);
	}
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::ascend_left() { // ascend to nearest node whose left hand exists and hasn't been explored

	if(_path.size() == 0) return;
	Node* front = nullptr;

	while(_path.size() != 0 && (_path.first()->rhv != front || (_path.first()->rhv == nullptr && _path.first()->lhv != front ))) {
		front = _path.first();
		_path.pop_front();
	} 
}

template<class Type>
void BalancedBinaryTree<Type>::iterator::ascend_right() { // ascend to nearest node whose right hand exists and hasn't been explored

	if(_path.size() == 0) return;
	Node* front = nullptr;

	while(_path.size() != 0 && (_path.first()->lhv != front || (_path.first()->rhv == nullptr && _path.first()->lhv != front ))) {
		front = _path.first();
		_path.pop_front();
	} 
}


#endif // GUARD_BALANCED_BINARY_TREE_HPP__
