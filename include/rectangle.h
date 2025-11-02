#pragma once

#include <cmath>
#include <stdexcept>
#include "figure.h"

template <Scalar T>
class Rectangle : public Figure<T> {
protected:
    // Используется в friend operator<<
    virtual void print(std::ostream& os) const override {
        os << "Rectangle: "
        << *this->points[0] << ", "
        << *this->points[1] << ", "
        << *this->points[2] << ", "
        << *this->points[3] << std::endl;
    }
    // Для использования в friend operator>>
    virtual void input(std::istream& is) override {
        Point<T> bottom_left_p;
        T width, height;
        std::cout << "Введите координаты левой нижней точки: ";
        is >> bottom_left_p;
        std::cout << "Введите ширину и высоту прямоугольника: ";
        is >> width >> height;
        this->points[0] = std::make_unique<Point<T>>(bottom_left_p); // левая нижняя
        this->points[1] = std::make_unique<Point<T>>(bottom_left_p.x + width, bottom_left_p.y); // правая нижняя
        this->points[2] = std::make_unique<Point<T>>(bottom_left_p.x + width, bottom_left_p.y + height); // правая верхняя
        this->points[3] = std::make_unique<Point<T>>(bottom_left_p.x, bottom_left_p.y + height); // левая верхняя
    }
public:
    Rectangle(): Figure<T>(4) {}

    Rectangle(const Point<T>& bottom_left_p, const T width, const T height): Figure<T>(4) {
        this->points[0] = std::make_unique<Point<T>>(bottom_left_p); // левая нижняя
        this->points[1] = std::make_unique<Point<T>>(bottom_left_p.x + width, bottom_left_p.y); // правая нижняя
        this->points[2] = std::make_unique<Point<T>>(bottom_left_p.x + width, bottom_left_p.y + height); // правая верхняя
        this->points[3] = std::make_unique<Point<T>>(bottom_left_p.x, bottom_left_p.y + height); // левая верхняя
    }

    virtual ~Rectangle() override {
        std::cout << "Rectangle: деструктор" << std::endl;
    };

    double area() const override final {
        double w = distance<T>(*this->points[0], *this->points[1]);
        double h = distance<T>(*this->points[0], *this->points[3]);
        return w * h;
    }
};