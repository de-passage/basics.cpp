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
		~BalancedBinaryTreeNode();

		// Operate tree rotations, return a pointer to the top most node after rotation
		BalancedBinaryTreeNode* rotate_left();
		BalancedBinaryTreeNode* rotate_right();
		BalancedBinaryTreeNode* rotate_left_right();
		BalancedBinaryTreeNode* rotate_right_left();

		// Rotate the tree according to the current height_difference parameter, return a pointer to the top most node after rotation
		BalancedBinaryTreeNode* rebalance();

		// Insert a new value in the tree and balance it
		BalancedBinaryTreeNode* insert(const Type& value);

		private: 
		BalancedBinaryTreeNode* _insert(const Type& value, BalancedBinaryTreeNode*&, void(*)(int&));
	};

	template<class Type>
		constexpr BalancedBinaryTreeNode<Type>::BalancedBinaryTreeNode(const Type& value) : value(value), lhv(nullptr), rhv(nullptr), height_difference(0) {}

	template<class Type>
		BalancedBinaryTreeNode<Type>::~BalancedBinaryTreeNode() {
			if(lhv != nullptr) delete lhv;
			if(rhv != nullptr) delete rhv;
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::rebalance() {
			if(height_difference == -2) { // Left heavy

				if(lhv->height_difference == -1) return rotate_right(); // left is left heavy
				else return rotate_left_right(); // left is right heavy

			}
			else if(height_difference == 2) { // Right heavy

				if(rhv->height_difference == 1) return rotate_left(); // right is right heavy
				else return rotate_right_left(); // left is left heavy

			} else  // No need to rebalance
				return this; // top most didnt change
		}

	template<class T>
		BalancedBinaryTreeNode<T>* BalancedBinaryTreeNode<T>::_insert(const T& new_value, BalancedBinaryTreeNode<T>*& p, void (*f)(int&)) {

				if(p == nullptr) { // If the branch doesnt exist

					p = new BalancedBinaryTreeNode<T>(new_value); //add a new node
					f(height_difference); // set the balance

					return this; // top most didnt change

				} else {

					p = p->insert(new_value); // recurse if the branch exists, then replace the current pointer by the new top most value

					if(p->height_difference != 0) { // If the branch is unbalanced 
						f(height_difference); // reflect it here
					}
					return rebalance(); // rebalance and return new top most node
				}
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::insert(const Type& new_value) {
			if(new_value == value) { // Update value if it already exists
				value = new_value;
				return this;
			}
			else if(new_value < value) { // If its lower go left branch
				return _insert(new_value, lhv, [](int& i) { --i; });
			}
			else { // if its higher go right branch
				return _insert(new_value, rhv, [](int& i) { ++i; });
			}
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::rotate_left() {
			auto pivot = rhv;
			rhv = pivot->lhv;
			pivot->lhv = this;
			height_difference = 0;
			pivot->height_difference = 0;
			return pivot;
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::rotate_right() {
			auto pivot = lhv;
			lhv = pivot->rhv;
			pivot->rhv = this;
			height_difference = 0;
			pivot->height_difference = 0;
			return pivot;
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::rotate_right_left() {
			rhv = rhv->rotate_right();
			rhv->height_difference = 1; //Adjust the height difference to account for the fact that rotate_right was expecting rhv->rhv to be a value. Since it is not the node is right heavy
			return rotate_left();
		}

	template<class Type>
		BalancedBinaryTreeNode<Type>* BalancedBinaryTreeNode<Type>::rotate_left_right() {
			lhv = lhv->rotate_left();
			lhv->height_difference = -1; // Same as rotate_right_left
			return rotate_right();
		}
}

#endif// GUARD_BALANCED_BINARY_TREE_NODE_HPP__
