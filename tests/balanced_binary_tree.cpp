#include <gtest/gtest.h>
#include <stdexcept>

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

TEST(BalancedBinaryTree, CpyCtor) {
  BBT b = {1, 2, 3, 4};
  BBT b2 = b;
  ASSERT_EQ(b.size(), 4_z);
  ASSERT_EQ(b2.size(), 4_z);
  int r = 1;
  for (auto it = b.begin(), it2 = b2.begin(); it != b.end(); ++it, ++it2) {
    ASSERT_EQ(*it, r);
    ASSERT_EQ(*it2, r);
    r++;
  }
}

TEST(BalancedBinaryTree, MoveCtor) {
  BBT b = {1, 2, 3, 4, 5};
  BBT b2 = std::move(b);
  ASSERT_EQ(b.size(), 0_z);
  ASSERT_EQ(b2.size(), 5_z);
  for (int r = 1; r <= 5; ++r) {
    ASSERT_NO_THROW(b2[r]);
    ASSERT_THROW(b[r], std::out_of_range);
  }
}

TEST(BalancedBinaryTree, CopyAssignment) {
  BBT b;
  BBT b2 = {1, 2, 3, 4, 5};
  b = b2;
  ASSERT_EQ(b.size(), 5_z);
  ASSERT_EQ(b2.size(), 5_z);
  int r = 1;
  for (auto it = b.begin(), it2 = b2.begin(); it != b.end(); ++it, ++it2) {
    ASSERT_EQ(*it, r);
    ASSERT_EQ(*it2, r);
    r++;
  }
}

TEST(BalancedBinaryTree, MoveAssignment) {
  BBT b2;
  BBT b = {1, 2, 3, 4, 5};
  b2 = std::move(b);
  ASSERT_EQ(b.size(), 0_z);
  ASSERT_EQ(b2.size(), 5_z);
  for (int r = 1; r <= 5; ++r) {
    ASSERT_NO_THROW(b2[r]);
    ASSERT_THROW(b[r], std::out_of_range);
  }
}