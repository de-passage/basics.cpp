#include <gtest/gtest.h>

#include "single_linked_list.hpp"
#include "utility.hpp"

#include <iostream>
#include <iterator>
#include <type_traits>

TEST(LinkedList, DefaultCtor) {
  SingleLinkedList<int> l;
  ASSERT_EQ(l.size(), 0_z);
}

TEST(LinkedList, ListCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SingleLinkedList<int> sl = l;
  ASSERT_EQ(sl.size(), 5_z);

  auto j = l.begin();
  for (auto i : l) {
    ASSERT_EQ(i, *j);
    ++j;
  }
}

TEST(LinkedList, ListCpyCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SingleLinkedList<int> sl = l;
  SingleLinkedList<int> sl2 = sl;
  ASSERT_EQ(sl.size(), 5_z);
  ASSERT_EQ(sl.size(), sl2.size());
  for (auto it = sl.begin(), jt = sl2.begin(); it != sl.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(LinkedList, ListMvCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SingleLinkedList<int> sl = l;
  SingleLinkedList<int> sl2 = std::move(sl);
  ASSERT_EQ(sl.size(), 0_z);
  ASSERT_EQ(sl2.size(), 5_z);
  auto b = std::begin(l);
  for (auto v : sl2) {
    ASSERT_EQ(*b++, v);
  }
}

constexpr static inline auto sorted =
    [](auto &&sll) -> std::remove_reference_t<decltype(sll)> && {
  sll.sort();
  return std::forward<std::remove_reference_t<decltype(sll)>>(sll);
};

TEST(LinkedList, SortEmpty) {
  using SLL = SingleLinkedList<int>;
  ASSERT_EQ((SLL{}), sorted(SLL{}));
}

TEST(LinkedList, SortNoop) {
  using SLL = SingleLinkedList<int>;
  ASSERT_EQ((SLL{2}), sorted(SLL{2}));
  ASSERT_EQ((SLL{1, 2}), sorted(SLL{1, 2}));
  ASSERT_EQ((SLL{1, 2, 3}), sorted(SLL{1, 2, 3}));
}

TEST(LinkedList, Sort) {
  using SLL = SingleLinkedList<int>;
  SLL s[3] = {{5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}, {4, 2, 5, 1, 3}};

  for (auto &l : s) {
    l.sort();
  }

  for (const auto &l : s) {
    auto min = 0;
    for (const auto i : l) {
      ASSERT_LT(min, i);
      min = i;
    }
  }
}