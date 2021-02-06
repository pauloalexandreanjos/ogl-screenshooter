#include <gtest/gtest.h>

TEST(TestTest, FirstTest) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char** args) {
    testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}