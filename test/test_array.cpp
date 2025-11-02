#include <gtest/gtest.h>
#include "../include/array.h"
#include "../include/square.h"
#include "../include/rectangle.h"
#include "../include/triangle.h"
#include <memory>

TEST(ArrayTest, ScalarTypeBasicOperations) {
    Array<int> arr;
    EXPECT_TRUE(arr.empty());
    arr.add(5);
    arr.add(10);
    arr.add(15);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 15);

    arr.pop_back();
    EXPECT_EQ(arr.size(), 2);

    arr.remove(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);

    arr.clear();
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, ScalarTypeCapacityIncrease) {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) arr.add(i);
    EXPECT_GE(arr.cap(), 10);
    EXPECT_EQ(arr.size(), 10);
}

TEST(ArrayTest, ExceptionOnOutOfRangeAccess) {
    Array<int> arr;
    arr.add(1);
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.remove(1), std::out_of_range);
}

TEST(ArrayTest, ArrayOfFigures) {
    using FigurePtr = std::shared_ptr<Figure<double>>;
    Array<FigurePtr> figs;
    figs.add(std::make_shared<Square<double>>(Point<double>(0, 0), 2));
    figs.add(std::make_shared<Rectangle<double>>(Point<double>(0, 0), 2, 3));
    figs.add(std::make_shared<Triangle<double>>(Point<double>(0, 0), 3, 4));
    EXPECT_EQ(figs.size(), 3);
    EXPECT_DOUBLE_EQ(figs[0]->area(), 4.0);
    EXPECT_DOUBLE_EQ(figs[1]->area(), 6.0);
    EXPECT_DOUBLE_EQ(figs[2]->area(), 6.0);
}

TEST(ArrayTest, ArrayOfConcreteFigures) {
    Array<Square<double>> squares;
    squares.add(Square<double>(Point<double>(0, 0), 1.0));
    squares.add(Square<double>(Point<double>(1, 1), 2.0));
    EXPECT_EQ(squares.size(), 2);
    EXPECT_DOUBLE_EQ(squares[0].area(), 1.0);
    EXPECT_DOUBLE_EQ(squares[1].area(), 4.0);
}