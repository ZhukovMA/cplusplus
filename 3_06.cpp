/*
[1] Доработайте Ваше предыдущее решение задачи 03.02 таким образом, чтобы все реализованные классы являлись наследниками одного базового класса.
[2] Реализуйте абстрактный базовый класс Shape для представления интерфейса геометрических фигур.
[3] Реализуйте в классе Shape виртуальный деструктор и две публичные чисто виртуальные функции-члены perimeter и
        area для вычисления периметра и площади соответственно.
[4] Реализуйте производные классы Triangle, Square и Circle, которые являются наследниками интерфейса класса Shape.
[5] Используйте спецификатор override при переопределении наследуемых виртуальных функций-членов perimeter и area в классах
    Triangle, Square и Circle.
[6] Используйте спецификатор final для запрета наследования от классов Square и Circle и для запрета переопределения наследуемых
    виртуальных функций-членов perimeter и area в возможных наследниках класса Triangle.
[7] Используйте стандартный контейнер std::vector для хранения экземпляров классов Triangle, Square и Circle через указатели на класс Shape.
*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <vector>

// [1]

// [2]
class Shape {
  public:
    // [3]
    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
};

// [4]
class Triangle : public Shape {
  public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        assert(a_ > 0 && b_ > 0 && c_ > 0 && "Triangle: sides must be positive");
        assert(a_ + b_ > c_ && a_ + c_ > b_ && b_ + c_ > a_ && "Triangle: triangle inequality failed");
    }

    // [5] [6]
    double perimeter() const override final {
        return a_ + b_ + c_;
    }

    // [5] [6]
    double area() const override final {
        const double p = perimeter() * 0.5;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

  private:
    double a_, b_, c_;
};

// [4]
class Square final : public Shape { // [6]
  public:
    Square(double s) : s_(s) {
        assert(s_ >= 0 && "Square: side must be >= 0");
    }

    // [5] [6]
    double perimeter() const override final {
        return 4.0 * s_;
    }

    // [5] [6]
    double area() const override final {
        return s_ * s_;
    }

  private:
    double s_;
};

// [4]
class Circle final : public Shape { // [6]
  public:
    Circle(double r) : r_(r) {
        assert(r_ >= 0 && "Circle: radius must be >= 0");
    }

    // [5] [6]
    double perimeter() const override final {
        return 2.0 * std::numbers::pi * r_;
    }

    // [5] [6]
    double area() const override final {
        return std::numbers::pi * r_ * r_;
    }

  private:
    double r_;
};

int main() {
    // [7]
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Triangle>(3, 4, 5));
    shapes.emplace_back(std::make_unique<Square>(2));
    shapes.emplace_back(std::make_unique<Circle>(1));

    assert(std::abs(shapes[0]->perimeter() - 12.0) < 1e-12);
    assert(std::abs(shapes[0]->area() - 6.0) < 1e-12);
    assert(std::abs(shapes[1]->perimeter() - 8.0) < 1e-12);
    assert(std::abs(shapes[1]->area() - 4.0) < 1e-12);
    assert(std::abs(shapes[2]->perimeter() - 2 * std::numbers::pi) < 1e-12);
    assert(std::abs(shapes[2]->area() - std::numbers::pi) < 1e-12);

    double sumP = 0, sumA = 0;
    for (const auto &s : shapes) {
        sumP += s->perimeter();
        sumA += s->area();
    }

    std::cout << "Total perimeter = " << sumP << "\n";
    std::cout << "Total area      = " << sumA << "\n";
}