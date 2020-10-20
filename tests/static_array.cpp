#include <gtest/gtest.h>

#include "static_array.hpp"
#include "utility.hpp"

#include <string>

template <std::size_t S> using SA = StaticArray<std::string, S>;

TEST(StaticArray, Ctor) {
  SA<0> sa = {};
  SA<3> sa3 = {"1", "2", "3"};
  ASSERT_EQ(sa.size(), 0_z);
  ASSERT_EQ(sa3.size(), 3_z);
  for (auto i = 0; i < 3; ++i) {
    ASSERT_EQ(sa3[i], std::to_string(i + 1));
  }
  std::string ss[2] = {"ab", "cd"};
  SA<2> sa2{ss};
  ASSERT_EQ(sa2.size(), 2_z);
  for (auto i = 0; i < 2; ++i) {
    ASSERT_EQ(sa2[i], ss[i]);
  }
}

TEST(StaticArray, CpyCtor) {
  SA<4> sa = {"0", "1", "2", "3"};
  SA<4> sa2 = sa;
  ASSERT_EQ(sa2.size(), sa.size());
  for (auto i = 0; i < sa.size(); ++i) {
    ASSERT_EQ(sa[i], sa2[i]);
    ASSERT_EQ(sa2[i], std::to_string(i));
  }
}

TEST(StaticArray, MoveCtor) {
  SA<3> sa = {"0", "1", "2"};
  SA<3> sa2 = std::move(sa);
  ASSERT_EQ(sa2.size(), sa.size());
  for (auto i = 0; i < sa.size(); ++i) {
    // Technically UB but works on Clang, use unique_ptr to fix
    ASSERT_EQ(sa[i], "");
    ASSERT_EQ(sa2[i], std::to_string(i));
  }
}

TEST(StaticArray, CpyAssign) {
  SA<4> sa = {"0", "1", "2", "3"};
  SA<4> sa2 = {"", "", "", ""};
  sa2 = sa;
  for (auto i = 0; i < sa.size(); ++i) {
    ASSERT_EQ(sa[i], sa2[i]);
    ASSERT_EQ(sa2[i], std::to_string(i));
  }
}

TEST(StaticArray, MoveAssign) {
  SA<3> sa = {"0", "1", "2"};
  SA<3> sa2 = {"", "", ""};
  sa2 = std::move(sa);
  for (auto i = 0; i < sa.size(); ++i) {
    // Technically UB but works on Clang, use unique_ptr to fix
    ASSERT_EQ(sa[i], "");
    ASSERT_EQ(sa2[i], std::to_string(i));
  }
}

template <std::size_t S> using SI = StaticArray<int, S>;

TEST(StaticArray, Sort) {
  SI<5> sa[3] = {{0, 1, 2, 3, 4}, {4, 3, 2, 1, 0}, {3, 4, 1, 0, 2}};
  for (auto &a : sa) {
    a.sort();
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 3; ++j) {
      ASSERT_EQ(sa[j][i], i);
    }
  }
}