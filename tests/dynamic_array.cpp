#include <gtest/gtest.h>
#include <vcruntime.h>

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

TEST(DynamicArray, AddElements) {
  DA d;
  for (int i = 0; i < 10; ++i) {
    d.push_back(i);
    ASSERT_EQ(d.size(), i + 1_z);
    ASSERT_EQ(d.at(i), i);
  }
}

TEST(DynamicArray, RemoveElements) {
  DA d = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; ++i) {
    d.pop();
    ASSERT_EQ(d.size(), 9 - i);
  }
}

TEST(DynamicArray, SortNoop) {
  ASSERT_EQ(DA{}, sorted(DA{}));
  ASSERT_EQ(DA{1}, sorted(DA{1}));
  ASSERT_EQ((DA{1, 2}), (sorted(DA{1, 2})));
  ASSERT_EQ((DA{1, 2, 3, 4, 4, 5, 6, 7}), (sorted(DA{1, 2, 3, 4, 4, 5, 6, 7})));
}

TEST(DynamicArray, Sort) {
  DA d[3] = {{1, 4, 3, 3, 2, 5}, {5, 4, 3, 3, 2, 1}, {3, 4, 2, 5, 3, 1}};
  int r[6] = {1, 2, 3, 3, 4, 5};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 6; ++j) {
      d[i].sort();
      ASSERT_EQ(r[j], d[i][j]);
    }
  }
}