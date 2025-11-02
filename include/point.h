#pragma once
#include <type_traits>
#include <iostream>
#include <cmath>


template <class T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
struct Point;

template <Scalar T>
double distance(const Point<T>& a, const Point<T>& b);

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p);

template <Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p);

template <Scalar T>
struct Point {
    T x, y;

    Point() : x(T{}), y(T{}) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}
    // Друзья :)
    friend double distance <>(const Point<T>& p1, const Point<T>& p2);
    friend std::ostream& operator<< <>(std::ostream& os, const Point<T>& p);
    friend std::istream& operator>> <>(std::istream& is, Point<T>& p);
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template <Scalar T>
double distance(const Point<T>& a, const Point<T>& b) {
    T dx = a.x - b.x;
    T dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}