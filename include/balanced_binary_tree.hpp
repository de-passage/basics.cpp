#ifndef GUARD_BALANCED_BINARY_TREE_HPP__
#define GUARD_BALANCED_BINARY_TREE_HPP__

#include "details/balanced_binary_tree_node.hpp"
#include "single_linked_list.hpp"

#include <initializer_list>
#include <stdexcept>
#include <utility>

template <class Type> class BalancedBinaryTree {
  typedef details::BalancedBinaryTreeNode<Type> Node;

public:
  constexpr BalancedBinaryTree();
  constexpr BalancedBinaryTree(const std::initializer_list<Type> &);

  BalancedBinaryTree(const BalancedBinaryTree &bbt);
  BalancedBinaryTree(BalancedBinaryTree &&bbt) noexcept;

  ~BalancedBinaryTree();

  BalancedBinaryTree &operator=(const BalancedBinaryTree &);
  BalancedBinaryTree &operator=(BalancedBinaryTree &&) noexcept;

  void insert(const Type &);

  inline std::size_t size() const { return _size; }

private:
  Node *_root;
  std::size_t _size;

  static void _delete_branch(Node *);

public:
  struct iterator {
    constexpr iterator();
    constexpr iterator(Node *);
    iterator(SingleLinkedList<Node *> &&);

    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);

    const Type &operator*() const;
    const Type *operator->() const;

    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;

  private:
    SingleLinkedList<Node *> _path;

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

  const_iterator find(const Type &) const;
  const Type &operator[](const Type &) const;
};

template <class Type>
constexpr BalancedBinaryTree<Type>::BalancedBinaryTree()
    : _root(nullptr), _size(0) {}

template <class Type>
constexpr BalancedBinaryTree<Type>::BalancedBinaryTree(
    const std::initializer_list<Type> &list)
    : _root(nullptr), _size(0) {
  for (const auto &v : list) {
    insert(v);
  }
}

template <class Type>
BalancedBinaryTree<Type>::BalancedBinaryTree(
    const BalancedBinaryTree<Type> &bbt)
    : _root(nullptr), _size(0) {
  for (const auto &v : bbt) {
    insert(v);
  }
}

template <class Type>
BalancedBinaryTree<Type>::BalancedBinaryTree(
    BalancedBinaryTree<Type> &&bbt) noexcept
    : _root(std::exchange(bbt._root, nullptr)),
      _size(std::exchange(bbt._size, 0)) {}

template <class Type>
BalancedBinaryTree<Type> &
BalancedBinaryTree<Type>::operator=(BalancedBinaryTree<Type> &&v) noexcept {
  std::swap(v._root, _root);
  _size = std::exchange(v._size, 0);
  delete v._root;
  v._root = nullptr;
  return *this;
}

template <class Type>
BalancedBinaryTree<Type> &
BalancedBinaryTree<Type>::operator=(const BalancedBinaryTree<Type> &v) {
  Node *r = nullptr;
  if (v.size() > 0) {
    auto it = v.begin();
    r = new Node{*it++};
    for (; it != v.end(); ++it) {
      r->insert(*it);
    }
  }
  std::swap(r, _root);
  delete r;
  _size = v.size();
  return *this;
}

template <class Type> void BalancedBinaryTree<Type>::insert(const Type &value) {
  if (_root) {
    _root = _root->insert(value);
    ++_size;
  } else {
    _root = new details::BalancedBinaryTreeNode<Type>(value);
    _size = 1;
  }
}

template <class Type>
typename BalancedBinaryTree<Type>::const_iterator
BalancedBinaryTree<Type>::begin() const {
  return {_root};
}

template <class Type>
typename BalancedBinaryTree<Type>::const_iterator
BalancedBinaryTree<Type>::end() const {
  return {};
}

template <class Type> BalancedBinaryTree<Type>::~BalancedBinaryTree() {
  if (_root != nullptr)
    delete _root;
}

template <class Type>
constexpr BalancedBinaryTree<Type>::iterator::iterator() : _path() {}

template <class Type>
constexpr BalancedBinaryTree<Type>::iterator::iterator(Node *root) : _path() {
  while (root != nullptr) {
    _path.push_front(root);
    root = root->lhv;
  }
}

template <class Type>
BalancedBinaryTree<Type>::iterator::iterator(SingleLinkedList<Node *> &&l)
    : _path(std::move(l)) {}

template <class Type>
typename BalancedBinaryTree<Type>::iterator &
BalancedBinaryTree<Type>::iterator::operator++() {
  auto front = _path.first();
  if (front->lhv == nullptr && front->rhv == nullptr) { // Leaf
    _path.pop_front();
    if (_path.first()->rhv == front) { // we were in right node
      ascend_right();
    }
    // else we were in left node and now on the right value
  } else { // Middle node,
    go_right_branch();
    if (front != _path.first()) {
      descend_left();
    } else {
      ascend_right();
    }
  }

  return *this;
}

template <class Type>
typename BalancedBinaryTree<Type>::iterator
BalancedBinaryTree<Type>::iterator::operator++(int) {
  iterator it = *this;
  ++*this;
  return it;
}

template <class Type>
typename BalancedBinaryTree<Type>::iterator &
BalancedBinaryTree<Type>::iterator::operator--() {
  auto front = _path.first();
  if (front->lhv == nullptr && front->rhv == nullptr) { // Leaf
    _path.pop_front();
    if (_path.first()->lhv == front) { // we were in left node
      ascend_left();
    }
  } else { // Middle node,
    go_left_branch();
    if (front != _path.first()) {
      descend_right();
    } else {
      ascend_left();
    }
  }

  return *this;
}
template <class Type>
typename BalancedBinaryTree<Type>::iterator
BalancedBinaryTree<Type>::iterator::operator--(int) {
  iterator it = *this;
  --*this;
  return it;
}

template <class Type>
const Type &BalancedBinaryTree<Type>::iterator::operator*() const {
  return _path.first()->value;
}

template <class Type>
const Type *BalancedBinaryTree<Type>::iterator::operator->() const {
  return &_path.first()->value;
}

template <class Type>
bool BalancedBinaryTree<Type>::iterator::operator==(const iterator &it) const {
  if (_path.size() == 0 && it._path.size() == 0)
    return true;
  return _path.size() == it._path.size() && _path.first() == it._path.first();
}

template <class Type>
bool BalancedBinaryTree<Type>::iterator::operator!=(const iterator &it) const {
  return !(*this == it);
}

template <class Type> void BalancedBinaryTree<Type>::iterator::descend_left() {
  if (_path.size() == 0)
    return;
  while (_path.first()->lhv != nullptr) {
    _path.push_front(_path.first()->lhv);
  }
}

template <class Type> void BalancedBinaryTree<Type>::iterator::descend_right() {
  if (_path.size() == 0)
    return;
  while (_path.first()->rhv != nullptr) {
    _path.push_front(_path.first()->rhv);
  }
}

template <class Type>
void BalancedBinaryTree<Type>::iterator::go_left_branch() {
  if (_path.size() != 0 && _path.first()->lhv != nullptr) {
    _path.push_front(_path.first()->lhv);
  }
}

template <class Type>
void BalancedBinaryTree<Type>::iterator::go_right_branch() {
  if (_path.size() != 0 && _path.first()->rhv != nullptr) {
    _path.push_front(_path.first()->rhv);
  }
}

template <class Type>
void BalancedBinaryTree<
    Type>::iterator::ascend_left() { // ascend to nearest node whose left hand
                                     // exists and hasn't been explored

  if (_path.size() == 0)
    return;
  Node *front = path.first();

  while (_path.size() != 0 &&
         (_path.first()->rhv != front ||
          (_path.first()->rhv == nullptr && _path.first()->lhv != front))) {
    front = _path.first();
    _path.pop_front();
  }
}

template <class Type>
void BalancedBinaryTree<
    Type>::iterator::ascend_right() { // ascend to nearest node whose right hand
                                      // exists and hasn't been explored

  if (_path.size() == 0)
    return;
  Node *front = _path.first();

  while (_path.size() != 0 &&
         (_path.first()->lhv != front ||
          (_path.first()->rhv == nullptr && _path.first()->lhv != front))) {
    front = _path.first();
    _path.pop_front();
  }
}

template <class Type>
const Type &BalancedBinaryTree<Type>::operator[](const Type &t) const {
  auto it = find(t);
  if (it == end()) {
    throw std::out_of_range("out of range access");
  }
  return *it;
}

template <class Type>
typename BalancedBinaryTree<Type>::const_iterator
BalancedBinaryTree<Type>::find(const Type &t) const {
  SingleLinkedList<Node *> path;
  auto *r = _root;
  while (r != nullptr) {
    path.push_front(r);
    if (t == r->value) {
      return {std::move(path)};
    } else if (t < r->value) {
      r = r->lhv;
    } else if (t > r->value) {
      r = r->rhv;
    }
  }
  return {};
}

#endif // GUARD_BALANCED_BINARY_TREE_HPP__
