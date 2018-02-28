#ifndef GUARD_BALANCED_BINARY_TREE_HPP__
#define GUARD_BALANCED_BINARY_TREE_HPP__

#include <utility>
#include <initializer_list>

namespace dpsg {
	template<class Type>
		class BalancedBinaryTree {
			public:
				constexpr BalancedBinaryTree();
				constexpr BalancedBinaryTree(const std::initializer_list<Type>&);
				~BalancedBinaryTree();

				void insert(const Type&);

			private:
				struct Node {
					Type value;
					Node *lhv;
					Node *rhv;
					std::size_t height_difference;
					constexpr Node(const Type&);
				} *_root;
				std::size_t _size;

				static void _delete_branch(Node*);

				static void _insert(const Type&, Node*);
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
			_insert(value, _root);
		}

	template<class Type>
		void BalancedBinaryTree<Type>::_insert(const Type& value, Node* node) {
			if(node == nullptr) {
				node = new Node(value);
			}
			else if(node->value == value) {
				node->value == value;
			}
			else if(value < node->value) {
				_insert(value, node->lhv);

			}
			else {
				_insert(value, node->lhv);
			}
		}

	template<class Type>
		BalancedBinaryTree<Type>::~BalancedBinaryTree() {
			_delete_branch(_root);
		}

	template<class Type>
		void BalancedBinaryTree<Type>::_delete_branch(Node* node) {
			if(node == nullptr) return;
			_delete_branch(node->lhv);
			_delete_branch(node->rhv);
			delete node;
		}

	template<class Type>
		constexpr BalancedBinaryTree<Type>::Node::Node(const Type& value) : value(value), lhv(nullptr), rhv(nullptr), height_difference(0) {}
}
#endif // GUARD_BALANCED_BINARY_TREE_HPP__
