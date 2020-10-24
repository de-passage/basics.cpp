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

TEST(DynamicArray, MoveAssign) {
  DA d = {1, 2, 3};
  DA d2 = {0, 2, 4, 6, 8};
  d = std::move(d2);
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d2.size(), 0_z);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(d[i], i * 2);
  }
}

TEST(DynamicArray, CpyAssign) {
  DA d = {1, 2, 3};
  DA d2 = {0, 2, 4, 6, 8};
  d = d2;
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d2.size(), 5_z);
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(d[i], i * 2);
    ASSERT_EQ(d2[i], i * 2);
  }
}