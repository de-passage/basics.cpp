#include "hash_table.hpp"

#include "utility.hpp"
#include "gtest/gtest.h"

#include <stdexcept>
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

TEST(HashTable, MoveCtor) {
  HT h = {1, 2, 3, 4, 5};
  HT h2 = std::move(h);
  EXPECT_EQ(h.size(), 0_z);
  EXPECT_EQ(h2.size(), 5_z);
  for (int i = 1; i <= 5; ++i) {
    EXPECT_THROW(h[i], std::out_of_range);
    EXPECT_NO_THROW(h2[i]);
  }
}

TEST(HashTable, AddElements) {
  HT h;
  h.insert(0);
  ASSERT_EQ(h.size(), 1_z);
  ASSERT_NO_THROW(h[0]);
  h.insert(10);
  ASSERT_EQ(h.size(), 2_z);
  ASSERT_NO_THROW(h[10]);
  h.insert(42);
  ASSERT_EQ(h.size(), 3_z);
  ASSERT_NO_THROW(h[42]);
  ASSERT_THROW(h.insert(42), std::runtime_error);
  ASSERT_EQ(h.size(), 3_z);
}

TEST(HashTable, RemoveElements) {
  HT h = {1, 2, 3, 4, 5};
  h.erase(42);
  ASSERT_EQ(h.size(), 5_z);
  h.erase(1);
  ASSERT_EQ(h.size(), 4_z);
  h.erase(5);
  ASSERT_EQ(h.size(), 3_z);
  h.erase(3);
  ASSERT_EQ(h.size(), 2_z);
  h.erase(1);
  ASSERT_EQ(h.size(), 2_z);
  h.erase(2);
  ASSERT_EQ(h.size(), 1_z);
  h.erase(4);
  ASSERT_EQ(h.size(), 0_z);
}