#include <gtest/gtest.h>

#include "single_linked_list.hpp"
#include "utility.hpp"

#include <iostream>
#include <iterator>
#include <numeric>
#include <type_traits>

using SLL = SingleLinkedList<int>;
TEST(LinkedList, DefaultCtor) {
  SLL l;
  ASSERT_EQ(l.size(), 0_z);
}

TEST(LinkedList, ListCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SLL sl = l;
  ASSERT_EQ(sl.size(), 5_z);

  auto j = l.begin();
  for (auto i : l) {
    ASSERT_EQ(i, *j);
    ++j;
  }
}

TEST(LinkedList, ListCpyCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SLL sl = l;
  SLL sl2 = sl;
  ASSERT_EQ(sl.size(), 5_z);
  ASSERT_EQ(sl.size(), sl2.size());
  for (auto it = sl.begin(), jt = sl2.begin(); it != sl.end(); ++it, ++jt) {
    ASSERT_EQ(*it, *jt);
  }
}

TEST(LinkedList, ListMvCtor) {
  const auto l = {1, 2, 3, 4, 5};
  SLL sl = l;
  SLL sl2 = std::move(sl);
  ASSERT_EQ(sl.size(), 0_z);
  ASSERT_EQ(sl2.size(), 5_z);
  auto b = std::begin(l);
  for (auto v : sl2) {
    ASSERT_EQ(*b++, v);
  }
}

TEST(LinkedList, Assignment) {
  SLL s;
  SLL s2 = {1, 2, 3, 4, 5};
  s = s2;
  ASSERT_EQ(s.size(), 5_z);
  int r = 1;
  for (auto i : s) {
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(LinkedList, SortEmpty) { ASSERT_EQ((SLL{}), sorted(SLL{})); }

TEST(LinkedList, SortNoop) {
  ASSERT_EQ((SLL{2}), sorted(SLL{2}));
  ASSERT_EQ((SLL{1, 2}), sorted(SLL{1, 2}));
  ASSERT_EQ((SLL{1, 2, 3}), sorted(SLL{1, 2, 3}));
}

TEST(LinkedList, Sort) {
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

struct wrapped_int {
  constexpr wrapped_int(int i, int j) : value(i + j) {}
  int value = 0;
};

TEST(LinkedList, AddElements) {
  using SLL = SingleLinkedList<wrapped_int>;
  SLL s = {{0, 0}, {0, 1}, {1, 1}};
  using namespace std;
  int tot = accumulate(begin(s), end(s), 0,
                       [](int acc, const auto &w) { return acc + w.value; });
  ASSERT_EQ(tot, 3);
  wrapped_int wi{3, 4};
  s.push_front(wi);
  ASSERT_EQ(s.size(), 4_z);
  ASSERT_EQ(s.first().value, 7);
  s.push_front(wrapped_int{5, 4});
  ASSERT_EQ(s.size(), 5_z);
  ASSERT_EQ(s.first().value, 9);
  s.emplace_front(6, 5);
  ASSERT_EQ(s.size(), 6_z);
  ASSERT_EQ(s.first().value, 11);
}

TEST(LinkedList, RemoveElements) {
  SLL s = {0, 1, 2, 3, 4, 5};
  s.pop_front();
  ASSERT_EQ(s.size(), 5);
  int i = 1;
  for (auto v : s) {
    ASSERT_EQ(v, i++);
  }

  auto it = std::next(s.begin(), 2);
  s.erase(it);
  ASSERT_EQ(s.size(), 4);
  ASSERT_EQ((SLL{1, 2, 4, 5}), s);

  s.erase(s.begin());
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ((SLL{2, 4, 5}), s);

  s.erase(s.begin());
  s.erase(s.begin());
  s.erase(s.begin());
  ASSERT_EQ(s.size(), 0);
}