
#include <gtest/gtest.h>

#include "double_linked_list.hpp"
#include "utility.hpp"

using DLL = DoubleLinkedList<int>;

TEST(DoubleLinkedList, DefaultCtor) {
  DLL d;
  ASSERT_EQ(d.size(), 0_z);
}

TEST(DoubleLinkedList, ListCtor) {
  DLL d = {1, 2, 3, 4, 5};
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d.first(), 1);
  ASSERT_EQ(d.last(), 5);
  auto r = 1;
  for (auto i : d) {
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(DoubleLinkedList, CpyCtor) {
  DLL d = {1, 2, 3, 4, 5};
  DLL d2 = d;
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d.first(), 1);
  ASSERT_EQ(d.last(), 5);
  ASSERT_EQ(d2.size(), 5_z);
  ASSERT_EQ(d2.first(), 1);
  ASSERT_EQ(d2.last(), 5);
  auto r = 1;
  auto j = d2.begin();
  for (auto i : d) {
    ASSERT_EQ(r, *j++);
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(DoubleLinkedList, MvCtor) {
  const auto l = {1, 2, 3, 4, 5};
  DLL d = l;
  DLL d2 = std::move(d);
  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d.begin(), d.end());
  ASSERT_EQ(d2.size(), 5_z);
  ASSERT_EQ(d2.first(), 1);
  ASSERT_EQ(d2.last(), 5);
  auto b = std::begin(l);
  for (auto v : d2) {
    ASSERT_EQ(*b++, v);
  }
}

TEST(DoubleLinkedList, Assignment) {
  DLL d;
  DLL d2 = {1, 2, 3, 4, 5};
  d = d2;
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d2.size(), 5_z);
  int r = 1;
  auto j = d2.begin();
  for (auto i : d) {
    ASSERT_EQ(r, *j++);
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(DoubleLinkedList, MoveAssignment) {
  DLL d;
  DLL d2 = {1, 2, 3, 4, 5};
  d = std::move(d2);
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d2.size(), 0_z);
  ASSERT_EQ(d2.begin(), d2.end());
  int r = 1;
  for (auto i : d) {
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(DoubleLinkedList, AddElements) {
  DLL d = {0};
  for (int i = 1; i <= 5; ++i) {
    d.push_front(-i);
    d.push_back(i);
  }
  ASSERT_EQ(d.size(), 11_z);
  auto r = -5;
  for (auto i : d) {
    ASSERT_EQ(r++, i);
  }
  ASSERT_EQ(r, 6);
}

TEST(DoubleLinkedList, RemoveElements) {
  DLL d = {0, 1, 2, 3, 4, 5, 6};
  d.pop_front();
  ASSERT_EQ(d.size(), 6_z);
  ASSERT_EQ(d.first(), 1);
  d.pop_back();
  ASSERT_EQ(d.size(), 5_z);
  ASSERT_EQ(d.last(), 5);

  int r = 1;
  for (auto i : d) {
    ASSERT_EQ(r++, i);
  }

  while (d.size() > 0) {
    d.pop_front();
  }

  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d.begin(), d.end());

  d = DLL{1, 2, 3, 4};
  while (d.size() > 0) {
    d.pop_back();
  }

  ASSERT_EQ(d.size(), 0_z);
  ASSERT_EQ(d.begin(), d.end());
}
