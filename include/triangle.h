#pragma once

#include <cmath>
#include "figure.h"

template <Scalar T>
class Triangle : public Figure<T> {
protected:
    // Используется в friend operator<<
    virtual void print(std::ostream& os) const override {
        os << "Triangle: "
        << *this->points[0] << ", "
        << *this->points[1] << ", "
        << *this->points[2] << std::endl;
    }
    // Для использования в friend operator>>
    virtual void input(std::istream& is) override {
        Point<T> bottom_left_point;
        T base, height;
        std::cout << "Введите координаты левой нижней точки: ";
        is >> bottom_left_point;
        std::cout << "Введите длину основания треугольника и высоту: ";
        is >> base >> height;
        this->points[0] = std::make_unique<Point<T>>(bottom_left_point); // левая нижняя точка
        this->points[1] = std::make_unique<Point<T>>(bottom_left_point.x + base, bottom_left_point.y); // правая нижняя точка
        this->points[2] = std::make_unique<Point<T>>(bottom_left_point.x + base / 2, bottom_left_point.y + height); // верхняя точка
    }
public:
    Triangle(): Figure<T>(3) {}

    Triangle(const Point<T>& bottom_left_point, const T base, const T height): Figure<T>(3) {
        this->points[0] = std::make_unique<Point<T>>(bottom_left_point); // левая нижняя точка
        this->points[1] = std::make_unique<Point<T>>(bottom_left_point.x + base, bottom_left_point.y); // правая нижняя точка
        this->points[2] = std::make_unique<Point<T>>(bottom_left_point.x + base / 2, bottom_left_point.y + height); // верхняя точка
    }

    virtual ~Triangle() override {
        std::cout << "Triangle: деструктор" << std::endl;
    };

    virtual double area() const override {
        return 0.5 * std::fabs(this->points[0]->x * (this->points[1]->y - this->points[2]->y)
            + this->points[1]->x * (this->points[2]->y - this->points[0]->y)
            + this->points[2]->x * (this->points[0]->y - this->points[1]->y));
    }
};