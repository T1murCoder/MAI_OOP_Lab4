#pragma once

#include "rectangle.h"

/*
 Квадрат - частный случай прямоугольника
 */
template <Scalar T>
class Square : public Rectangle<T> {
protected:
    // Используется в friend operator<<
    virtual void print(std::ostream& os) const override {
        os << "Square: "
        << *this->points[0] << ", "
        << *this->points[1] << ", "
        << *this->points[2] << ", "
        << *this->points[3] << std::endl;
    }
    // Для использования в friend operator>>
    virtual void input(std::istream& is) override {
        Point<T> bottom_left_p;
        T side;
        std::cout << "Введите координаты левой нижней точки: ";
        is >> bottom_left_p;
        std::cout << "Введите сторону квадрата: ";
        is >> side;
        this->points[0] = std::make_unique<Point<T>>(bottom_left_p); // левая нижняя
        this->points[1] = std::make_unique<Point<T>>(bottom_left_p.x + side, bottom_left_p.y); // правая нижняя
        this->points[2] = std::make_unique<Point<T>>(bottom_left_p.x + side, bottom_left_p.y + side); // правая верхняя
        this->points[3] = std::make_unique<Point<T>>(bottom_left_p.x, bottom_left_p.y + side); // левая верхняя
    }
public:
    Square(): Rectangle<T>() {}

    Square(const Point<T>& bottom_left_p, const T side): Rectangle<T>(bottom_left_p, side, side) {}

    virtual ~Square() override {
        std::cout << "Square: деструктор" << std::endl;
    };
};
