#ifndef GUARD_SINGLE_LINKED_LIST_HPP__
#define GUARD_SINGLE_LINKED_LIST_HPP__

#include <algorithm>
#include <initializer_list>

template <class Type> class SingleLinkedList {
public:
  constexpr SingleLinkedList();
  SingleLinkedList(const std::initializer_list<Type> &);
  constexpr SingleLinkedList(SingleLinkedList &&l) noexcept;
  SingleLinkedList(const SingleLinkedList &l);
  SingleLinkedList &operator=(SingleLinkedList &&l) noexcept;
  SingleLinkedList &operator=(const SingleLinkedList &l);

  ~SingleLinkedList();

  void push_front(const Type &);
  void push_front(Type &&);
  void pop_front();
  const Type &first() const;
  Type &first();

  constexpr std::size_t size() const;

  // Sort the list according to the comparison function given in argument
  // (bubble sort)
  template <class Compare = std::less<Type>>
  void sort(const Compare & = Compare{});

private:
  struct Node {
    Type value;
    Node *next;
  };

  static void _clean(Node *n);

  template <class T> struct basic_iterator {
    using difference_type = std::size_t;
    using value_type = std::conditional_t<std::is_const_v<T>, const Type, Type>;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_category = std::forward_iterator_tag;

    constexpr basic_iterator(T *);
    constexpr basic_iterator();
    template <class C> constexpr basic_iterator(const basic_iterator<C> &);

    constexpr reference operator*() const;
    constexpr reference operator*();

    constexpr const pointer operator->() const;
    constexpr pointer operator->();

    basic_iterator &operator++();
    basic_iterator operator++(int);

    template <class U>
    constexpr bool operator==(const basic_iterator<U> &node) const;
    template <class U>
    constexpr bool operator!=(const basic_iterator<U> &node) const;

  private:
    T *_pointer;
  };

  Node *_first;
  std::size_t _size;

public:
  typedef basic_iterator<Node> iterator;
  typedef basic_iterator<const Node> const_iterator;

  constexpr iterator begin();
  constexpr const_iterator begin() const;
  constexpr const_iterator cbegin() const { return begin(); }

  constexpr iterator end();
  constexpr const_iterator end() const;
  constexpr const_iterator cend() const { return end(); }

  void erase(const iterator &);
  iterator find(const Type &value);
  template <class Functor> iterator find(const Functor &value);
};

template <class Type>
constexpr SingleLinkedList<Type>::SingleLinkedList()
    : _first(nullptr), _size(0) {}

template <class Type>
SingleLinkedList<Type>::SingleLinkedList(
    const std::initializer_list<Type> &list)
    : _first(nullptr), _size(list.size()) {
  if (_size > 0) {
    auto it = list.begin();
    Node *last = new Node{*it++, nullptr};
    _first = last;
    for (; it != list.end(); ++it) {
      last->next = new Node{Type(*it), nullptr};
      last = last->next;
    }
  }
}

template <class Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList<Type> &l)
    : _first(nullptr), _size(l.size()) {
  if (_size > 0) {
    auto it = l.begin();
    Node *last = new Node{*it++, nullptr};
    _first = last;
    for (; it != l.end(); ++it) {
      last->next = new Node{Type(*it), nullptr};
      last = last->next;
    }
  }
}

template <class Type>
constexpr SingleLinkedList<Type>::SingleLinkedList(
    SingleLinkedList<Type> &&l) noexcept
    : _first(std::exchange(l._first, nullptr)), _size(l.size()) {
  l._size = 0;
}

template <class Type>
SingleLinkedList<Type> &
SingleLinkedList<Type>::operator=(const SingleLinkedList<Type> &l) {
  Node *f = nullptr;
  if (l.size() > 0) {
    Node *p = l._first;
    f = new Node{p->value, nullptr};
    p = p->next;
    while (p != nullptr) {
      f->next = new Node{p->value, nullptr};
      f = f->next;
      p = p->next;
    }
  }
  std::swap(f, _first);
  _size() = l.size();
  _clean(f);
  return *this;
}

template <class Type>
SingleLinkedList<Type> &
SingleLinkedList<Type>::operator=(SingleLinkedList<Type> &&l) noexcept {
  std::swap(l._first, _first);
  std::swap(l._size, _size);
  _clean(l._first);
  l._size = 0;
  return *this;
}

template <class Type> SingleLinkedList<Type>::~SingleLinkedList() {
  _clean(_first);
}

template <class Type> void SingleLinkedList<Type>::_clean(Node *first) {
  Node *tmp;
  while (first != nullptr) {
    tmp = first;
    first = first->next;
    delete tmp;
  }
}

template <class Type> void SingleLinkedList<Type>::push_front(const Type &t) {
  _first = new Node{Type(t), _first};
  ++_size;
}

template <class Type> void SingleLinkedList<Type>::push_front(Type &&t) {
  _first = new Node{Type(std::forward<Type>(t)), _first};
  ++_size;
}

template <class Type> void SingleLinkedList<Type>::pop_front() {
  Node *tmp = _first;
  _first = _first->next;
  --_size;
  delete tmp;
}

template <class Type> const Type &SingleLinkedList<Type>::first() const {
  return _first->value;
}

template <class Type> Type &SingleLinkedList<Type>::first() {
  return _first->value;
}

template <class Type>
constexpr std::size_t SingleLinkedList<Type>::size() const {
  return _size;
}

template <class Type>
constexpr typename SingleLinkedList<Type>::iterator
SingleLinkedList<Type>::begin() {
  return iterator(_first);
}

template <class Type>
constexpr typename SingleLinkedList<Type>::const_iterator
SingleLinkedList<Type>::begin() const {
  return _first;
}

template <class Type>
constexpr typename SingleLinkedList<Type>::iterator
SingleLinkedList<Type>::end() {
  return nullptr;
}

template <class Type>
constexpr typename SingleLinkedList<Type>::const_iterator
SingleLinkedList<Type>::end() const {
  return nullptr;
}

template <class Type> void SingleLinkedList<Type>::erase(const iterator &el) {
  Node *tmp = el->next;
  std::swap(el->value, tmp->value);
  el->next = tmp->next;
  delete tmp;
  --_size;
}

template <class Type>
typename SingleLinkedList<Type>::iterator
SingleLinkedList<Type>::find(const Type &val) {
  auto it = begin();
  for (; it != end(); ++it)
    if (*it == val)
      break;
  return it;
}

template <class Type>
template <class Functor>
typename SingleLinkedList<Type>::iterator
SingleLinkedList<Type>::find(const Functor &func) {
  auto it = begin();
  for (; it != end(); ++it)
    if (func(*it))
      break;
  return it;
}

template <class Type>
template <class Compare>
void SingleLinkedList<Type>::sort(const Compare &compare) {
  if (size() < 2)
    return;
  auto end = this->end();
  const auto begin = this->begin();
  while (end != begin) // until the end of the virtual list is the first element
  {                    // iterate over the list
    auto new_end = begin; // Set last sorted element to first, if this doesnt
                          // move the list is sorted
    auto next = begin;
    auto it = next++;
    while (next != end) {
      if (compare(*next, *it)) {
        std::iter_swap(it, next);
        new_end = it; // we sorted these elements
      }
      ++next;
      ++it;
    }
    end = new_end; // set end of virtual list to last sorted element
  }
}

template <class Type>
template <class T>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator()
    : _pointer(nullptr) {}

template <class Type>
template <class T>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator(T *p)
    : _pointer(p) {}

template <class Type>
template <class T>
template <class C>
constexpr SingleLinkedList<Type>::basic_iterator<T>::basic_iterator(
    const basic_iterator<C> &p)
    : _pointer(p._pointer) {}

template <class Type>
template <class T>
constexpr typename SingleLinkedList<Type>::template basic_iterator<T>::reference
SingleLinkedList<Type>::basic_iterator<T>::operator*() const {
  return _pointer->value;
}

template <class Type>
template <class T>
constexpr typename SingleLinkedList<Type>::template basic_iterator<T>::reference
SingleLinkedList<Type>::basic_iterator<T>::operator*() {
  return _pointer->value;
}

template <class Type>
template <class T>
constexpr const typename SingleLinkedList<Type>::template basic_iterator<
    T>::pointer
SingleLinkedList<Type>::basic_iterator<T>::operator->() const {
  return &_pointer->value;
}
template <class Type>
template <class T>
constexpr typename SingleLinkedList<Type>::template basic_iterator<T>::pointer
SingleLinkedList<Type>::basic_iterator<T>::operator->() {
  return &_pointer->value;
}

template <class Type>
template <class T>
typename SingleLinkedList<Type>::template basic_iterator<T> &
SingleLinkedList<Type>::basic_iterator<T>::operator++() {
  _pointer = _pointer->next;
  return *this;
}
template <class Type>
template <class T>
typename SingleLinkedList<Type>::template basic_iterator<T>
SingleLinkedList<Type>::basic_iterator<T>::operator++(int) {
  basic_iterator<T> tmp = *this;
  ++*this;
  return tmp;
}

template <class Type>
template <class T>
template <class U>
constexpr bool SingleLinkedList<Type>::basic_iterator<T>::operator==(
    const basic_iterator<U> &it) const {
  return it._pointer == _pointer;
}
template <class Type>
template <class T>
template <class U>
constexpr bool SingleLinkedList<Type>::basic_iterator<T>::operator!=(
    const basic_iterator<U> &node) const {
  return !(*this == node);
}

template <class T>
constexpr bool operator==(const SingleLinkedList<T> &lhv,
                          const SingleLinkedList<T> &rhv) {
  if (lhv.size() != rhv.size())
    return false;
  for (auto it1 = lhv.begin(), it2 = rhv.begin(), e = lhv.end(); it1 != e;
       ++it1, ++it2) {
    if (*it1 != *it2)
      return false;
  }
  return true;
}

template <class T>
constexpr bool operator!=(const SingleLinkedList<T> &lhv,
                          const SingleLinkedList<T> &rhv) {
  return !(lhv == rhv);
}

#endif // GUARD_SINGLE_LINKED_LIST_HPP__
