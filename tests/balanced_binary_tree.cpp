#include <gtest/gtest.h>

#include "balanced_binary_tree.hpp"
#include "utility.hpp"

using BBT = BalancedBinaryTree<int>;

TEST(BalancedBinaryTree, DefaultCtor) {
  BBT b{};
  ASSERT_EQ(b.size(), 0_z);
  ASSERT_EQ(b.begin(), b.end());
}

TEST(BalancedBinaryTree, ListCtor) {
  BBT b{1, 2, 3, 4, 5, 6, 7};
  ASSERT_EQ(b.size(), 7_z);
  for (int i = 1; i <= 7; ++i) {
    ASSERT_NO_THROW(b[i]);
    ASSERT_NE(b.find(i), b.end());
  }
  int r = 1;
  for (auto v : b) {
    ASSERT_EQ(r++, v);
  }
  ASSERT_EQ(r, 8);
}