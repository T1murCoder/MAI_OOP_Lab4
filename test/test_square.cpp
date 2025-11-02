#include <gtest/gtest.h>
#include "../include/square.h"

TEST(SquareTest, DefaultConstructor) {
    Square<int> s;
    EXPECT_EQ(s.area(), 0.0);
}

TEST(SquareTest, ParameterizedConstructor) {
    Point<float> p(1.0f, 2.0f);
    Square<float> s(p, 3.0f);
    EXPECT_FLOAT_EQ(s.area(), 9.0);
    EXPECT_FLOAT_EQ(static_cast<double>(s), 9.0);
    auto c = s.center();
    EXPECT_FLOAT_EQ(c.x, 1.0f + 1.5f);
    EXPECT_FLOAT_EQ(c.y, 2.0f + 1.5f);
}

TEST(SquareTest, OutputOperator) {
    Point<double> p(0.0, 0.0);
    Square<double> s(p, 2.0);
    std::stringstream ss;
    ss << s;
    EXPECT_NE(ss.str().find("Square:"), std::string::npos);
}