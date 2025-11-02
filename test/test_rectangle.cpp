#include <gtest/gtest.h>
#include "../include/rectangle.h"

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<int> r;
    EXPECT_EQ(r.area(), 0.0);
}

TEST(RectangleTest, ParameterizedConstructor) {
    Point<double> p(1.0, 2.0);
    Rectangle<double> r(p, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(r.area(), 12.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 12.0);
    auto c = r.center();
    EXPECT_DOUBLE_EQ(c.x, 1.0 + 3.0 / 2);
    EXPECT_DOUBLE_EQ(c.y, 2.0 + 4.0 / 2);
}

TEST(RectangleTest, EqualityOperator) {
    Point<int> p(0, 0);
    Rectangle<int> r1(p, 2, 5);
    Rectangle<int> r2(p, 5, 2);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, OutputOperator) {
    Point<int> p(0, 0);
    Rectangle<int> r(p, 1, 1);
    std::stringstream ss;
    ss << r;
    EXPECT_NE(ss.str().find("Rectangle:"), std::string::npos);
}