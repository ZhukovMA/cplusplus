/*
Шаги:
[1] Реализуйте класс Triangle для представления треугольников.
[2] Реализуйте в классе Triangle три приватных поля типа double для хранения длин трех сторон.
[3] Реализуйте класс Square для представления квадратов.
[4] Реализуйте в классе Square одно приватное поле типа double для хранения длины одной стороны.
[5] Реализуйте класс Circle для представления окружностей.
[6] Реализуйте в классе Circle одно приватное поле типа double для хранения радиуса.
[7] Реализуйте в Triangle, Square и Circle конструкторы и публичные методы perimeter и area для периметра и площади.
[8] Используйте стандартную константу std::numbers::рі в функциях-членах perimeter и area класа Circle.
*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <stdexcept>

// [1]
class Triangle {
  public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        assert(a_ > 0 && b_ > 0 && c_ > 0 && "Triangle: sides must be positive");
        assert(a_ + b_ > c_ && a_ + c_ > b_ && b_ + c_ > a_ && "Triangle: triangle inequality failed");
    }
    double perimeter() const {
        return a_ + b_ + c_;
    }
    double area() const {
        const double p = perimeter() * 0.5;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

  private:
    // [2]
    double a_, b_, c_;
};

// [3]
class Square {
  public:
    Square(double s) : s_(s) {
        assert(s_ >= 0 && "Square: side must be >= 0");
    }
    double perimeter() const {
        return 4.0 * s_;
    }
    double area() const {
        return s_ * s_;
    }

  private:
    // [4]
    double s_;
};

// [5]
class Circle {
  public:
    Circle(double r) : r_(r) {
        assert(r_ >= 0 && "Circle: radius must be >= 0");
    }
    double perimeter() const {
        return static_cast<double>(2 * std::numbers::pi * r_);
    }
    double area() const {
        return static_cast<double>(std::numbers::pi * r_ * r_);
    }

  private:
    // [6]
    double r_;
};

int main() {
    Triangle t{3, 4, 5};
    Square q{2};
    Circle c{1};

    assert(std::fabs(t.perimeter() - 12.0) < 1e-12);
    assert(std::fabs(t.area() - 6.0) < 1e-12);

    assert(std::fabs(q.perimeter() - 8.0) < 1e-12);
    assert(std::fabs(q.area() - 4.0) < 1e-12);

    assert(std::fabs(c.perimeter() - 2 * std::numbers::pi) < 1e-12);
    assert(std::fabs(c.area() - std::numbers::pi) < 1e-12);

    std::cout << "OK\n";
}