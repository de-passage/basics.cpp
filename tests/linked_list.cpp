#include <gtest/gtest.h>

#include "single_linked_list.hpp"
#include "utility.hpp"

#include <iostream>

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

TEST(LinkedList, Sort) {
    using SLL = SingleLinkedList<int>;
    SLL s[3] = { { 5, 4, 3, 2, 1 }, { 1, 2, 3, 4, 5 }, { 4, 2, 5, 1, 3 } };

    for(auto& l : s) {
        l.sort();
    }

    for (const auto& l : s) {
        auto min = 0;
        for(const auto i : l) {
            ASSERT_LT(min, i);
            min = i;
        }
    }
}