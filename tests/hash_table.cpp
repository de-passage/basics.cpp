#include "hash_table.hpp"

#include "utility.hpp"
#include "gtest/gtest.h"

#include <vector>

using HT = HashTable<int>;

TEST(HashTable, DefaultCtor) {
  HT h;
  EXPECT_EQ(h.size(), 0_z);
}

TEST(HashTable, ListCtor) {
  std::initializer_list<int> l = {1, 2, 3, 4, 5};
  HT h = l;
  EXPECT_EQ(h.size(), 5_z);
  for (auto i : l)
    EXPECT_NO_THROW(h[i]);
  EXPECT_THROW(h[0], std::out_of_range);
}

TEST(HashTable, CpyCtor) {
  HT h = {1, 2, 3, 4, 5};
  HT h2 = h;
  EXPECT_EQ(h.size(), h2.size());
  for (int i = 1; i <= 5; ++i) {
    EXPECT_NO_THROW(h[i]);
    EXPECT_NO_THROW(h2[i]);
  }
}