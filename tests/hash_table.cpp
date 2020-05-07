#include "hash_table.hpp"
#include "gtest/gtest.h"
#include <vector>


TEST(HashTable, EmptyCtor) {
    HashTable<int> h;
    EXPECT_EQ(h.size(), 0);
}

TEST(HashTable, ListCtor) {
    std::initializer_list<int> l = { 1, 2, 3, 4, 5 };
    HashTable<int> h = l;
    EXPECT_EQ(h.size(), 5);
    for(auto i : l)
        EXPECT_NO_THROW(h[i]);
    EXPECT_THROW(h[0], std::out_of_range);
}