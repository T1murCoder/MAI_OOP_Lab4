#include <gtest/gtest.h>
#include "../include/triangle.h"

TEST(TriangleTest, DefaultConstructor) {
    Triangle<int> t;
    EXPECT_EQ(t.area(), 0.0);
}

TEST(TriangleTest, ParameterizedConstructor) {
    Point<double> p(0.0, 0.0);
    Triangle<double> t(p, 4.0, 3.0);
    EXPECT_DOUBLE_EQ(t.area(), 6.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 6.0);
    auto c = t.center();
    EXPECT_DOUBLE_EQ(c.x, (0.0 + 4.0 + 2.0) / 3.0);
    EXPECT_DOUBLE_EQ(c.y, (0.0 + 0.0 + 3.0) / 3.0);
}

TEST(TriangleTest, OutputOperator) {
    Point<double> p(0.0, 0.0);
    Triangle<double> t(p, 2.0, 2.0);
    std::stringstream ss;
    ss << t;
    EXPECT_NE(ss.str().find("Triangle:"), std::string::npos);
}