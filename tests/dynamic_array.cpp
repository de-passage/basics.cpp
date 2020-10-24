#include <gtest/gtest.h>

#include "dynamic_array.hpp"
#include "utility.hpp"

using DA = DynamicArray<int>;

TEST(DynamicArray, DefaultCtor) {
  DA d;
  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d.end(), d.begin());
}

TEST(DynamicArray, ListCtor) {
  DA d = {0, 1, 2, 3, 4, 5};
  ASSERT_EQ(d.size(), 6_z);
  for (int i = 0; i < 6; ++i) {
    ASSERT_EQ(d[i], i);
  }
}

TEST(DynamicArray, CpyCtor) {
  DA d = {0, 1, 2, 3, 4, 5};
  DA d2{d};
  ASSERT_EQ(d.size(), 6_z);
  ASSERT_EQ(d2.size(), 6_z);
  for (int i = 0; i < 6; ++i) {
    ASSERT_EQ(d[i], i);
    ASSERT_EQ(d2[i], i);
  }
}

TEST(DynamicArray, MoveCtor) {
  DA d = {0, 1, 2, 3, 4, 5};
  DA d2{std::move(d)};
  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d2.size(), 6_z);
  for (int i = 0; i < 6; ++i) {
    ASSERT_EQ(d2[i], i);
  }
}