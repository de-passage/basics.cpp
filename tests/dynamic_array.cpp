#include <gtest/gtest.h>

#include "dynamic_array.hpp"
#include "utility.hpp"

using DA = DynamicArray<int>;

TEST(DynamicArray, DefaultCtor) {
  DA d;
  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d.end(), d.begin());
}