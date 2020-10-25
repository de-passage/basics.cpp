#include <gtest/gtest.h>

#include "balanced_binary_tree.hpp"
#include "utility.hpp"

using BBT = BalancedBinaryTree<int>;

TEST(BalancedBinaryTree, DefaultCtor) {
  BBT b{};
  ASSERT_EQ(b.size(), 0_z);
}