#include "hash_table.hpp"
#include "gtest/gtest.h"
#include <vector>


TEST(HashTable, Ctor) {
    HashTable h;
    EXPECT_EQ(h.size(), 0);
}