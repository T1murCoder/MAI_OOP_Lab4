#include <gtest/gtest.h>
#include "../include/point.h"
#include <sstream>

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(1.5, -2.3);
    EXPECT_DOUBLE_EQ(p.x, 1.5);
    EXPECT_DOUBLE_EQ(p.y, -2.3);
}

TEST(PointTest, DistanceCalculation) {
    Point<double> a(0.0, 0.0);
    Point<double> b(3.0, 4.0);
    EXPECT_DOUBLE_EQ(distance(a, b), 5.0);
}

TEST(PointTest, OutputOperator) {
    Point<int> p(2, 3);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(2, 3)");
}

TEST(PointTest, InputOperator) {
    Point<float> p;
    std::stringstream ss("2.5 3.5");
    ss >> p;
    EXPECT_FLOAT_EQ(p.x, 2.5f);
    EXPECT_FLOAT_EQ(p.y, 3.5f);
}