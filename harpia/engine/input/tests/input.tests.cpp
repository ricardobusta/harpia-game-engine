//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//
#include <gtest/gtest.h>

TEST(SomeInputTests, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 41);
}