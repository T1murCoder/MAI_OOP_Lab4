#pragma once
#include <iostream>
#include <memory>
#include "point.h"

constexpr double EPSILON = 1e-9;

template <Scalar T>
class Figure;

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& obj);

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& obj);

template <Scalar T>
class Figure {
    friend std::ostream& operator<< <>(std::ostream& os, const Figure<T>& obj);
    friend std::istream& operator>> <>(std::istream& is, Figure<T>& obj);
protected:
    Figure(): points(nullptr), point_count(0) {}

    Figure(const size_t count): point_count(count) {
        points = std::make_unique<std::unique_ptr<Point<T>>[]>(count);
        for (size_t i = 0; i < count; i++) {
            points[i] = std::make_unique<Point<T>>();
        }
    }

    // Для использования в friend operator<<
    virtual void print(std::ostream& os) const = 0;
    // Для использования в friend operator>>
    virtual void input(std::istream& is) = 0;

public:
    virtual ~Figure() {
        std::cout << "Figure: деструктор" << std::endl;
    };

    Figure(const Figure& other) : point_count(other.point_count) {
        points = std::make_unique<std::unique_ptr<Point<T>>[]>(point_count);
        for (size_t i = 0; i < point_count; i++) {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }

    Figure(Figure&& other) noexcept {
        points = std::move(other.points);
        point_count = other.point_count;
        other.point_count = 0;
    }

    virtual double area() const = 0;

    Point<T> center() const {
        T x_sum = 0, y_sum = 0;
        for (size_t i = 0; i < point_count; i++) {
            x_sum += points[i]->x;
            y_sum += points[i]->y;
        }
        return Point<T>(x_sum / point_count, y_sum / point_count);
    };

    bool operator==(const Figure &other) const {
        return std::abs(area() - other.area()) < EPSILON;
    };
    explicit operator double() const {
        return area();
    };

    Figure& operator=(const Figure& other) {
        if (this != &other) {
            point_count = other.point_count;
            points = std::make_unique<std::unique_ptr<Point<T>>[]>(point_count);
            for (size_t i = 0; i < point_count; i++) {
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
            }

        }
        return *this;
    };
    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            points = std::move(other.points);
            point_count = other.point_count;
            other.point_count = 0;
        }
        return *this;
    };


protected:
    std::unique_ptr<std::unique_ptr<Point<T>>[]> points;
    size_t point_count;
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& obj) {
    obj.print(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& obj) {
    obj.input(is);
    return is;
}