//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 26/10/2022.
//
#include <gtest/gtest.h>

TEST(SomeHarpiaTests, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(1, 1);
}