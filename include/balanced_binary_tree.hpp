#ifndef GUARD_BALANCED_BINARY_TREE_HPP__
#define GUARD_BALANCED_BINARY_TREE_HPP__

#include <utility>
#include <initializer_list>
#include "details/balanced_binary_tree_node.hpp"

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
BalancedBinaryTree<Type>::~BalancedBinaryTree() {
	if(_root != nullptr) delete _root;
}

#endif // GUARD_BALANCED_BINARY_TREE_HPP__
