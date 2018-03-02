#ifndef GUARD_BALANCED_BINARY_TREE_NODE_HPP__
#define GUARD_BALANCED_BINARY_TREE_NODE_HPP__

namespace details {

	template<class Type>
	struct BalancedBinaryTreeNode {
		Type value;
		BalancedBinaryTreeNode *lhv;
		BalancedBinaryTreeNode *rhv;
		int height_difference;
		constexpr BalancedBinaryTreeNode(const Type&);

		BalancedBinaryTreeNode& rotate_left();
		BalancedBinaryTreeNode& rotate_right();
		constexpr bool is_balanced() const;
	};

	template<class Type>
		constexpr BalancedBinaryTreeNode<Type>::BalancedBinaryTreeNode(const Type& value) : value(value), lhv(nullptr), rhv(nullptr), height_difference(0) {}
	template<class Type>
		BalancedBinaryTreeNode<Type>& BalancedBinaryTreeNode<Type>::rotate_left() {
			return *this;
		}
	template<class Type>
		BalancedBinaryTreeNode<Type>& BalancedBinaryTreeNode<Type>::rotate_right() {
			return *this;
		}

	template<class Type>
		constexpr bool BalancedBinaryTreeNode<Type>::is_balanced() const {
			return height_difference <= 1 && height_difference >= -1;
		}
}
#endif// GUARD_BALANCED_BINARY_TREE_NODE_HPP__
