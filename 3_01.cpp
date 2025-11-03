/*
Шаги:
[1] Реализуйте структуру Rectangle для представления прямоугольников со сторонами, которые параллельны осям координатной плоскости.
[2] Реализуйте в структуре Rectangle четыре поля типа int для хранения координат левого верхнего и правого нижнего углов прямоугольника.
[3] Используйте систему координат, в которой ось абсцисс направлена вправо, а ось ординат направлена вниз.
[4] Реализуйте алгоритм вычисления площади пересечения нескольких прямоугольников.
[5] Рассмотрите случаи пустого и вырожденного пересечения прямоугольников.
[6] Реализуйте алгоритм вычисления наименьшего ограничивающего несколько прямоугольников прямоугольника.
[7] Используйте стандартный контейнер std::vector для хранения экземпляров структуры Rectangle.
*/

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

// [1]
struct Rectangle {
    //[2]
    int x1;
    int y1;
    int x2;
    int y2;

    // если перепутали углы, то делаем их корректными
    void normalize() {
        if (x1 > x2)
            std::swap(x1, x2);
        if (y1 > y2)
            std::swap(y1, y2);
    }
    int width() const {
        return x2 - x1;
    }
    int height() const {
        return y2 - y1;
    }

    bool has_positive_area() const {
        return x1 < x2 && y1 < y2;
    }

    std::int64_t area() const {
        return static_cast<std::int64_t>(std::max(0, width())) * static_cast<std::int64_t>(std::max(0, height()));
    }
};

enum class IntersectKind {
    Empty,
    Degenerate,
    Proper
};

struct IntersectionResult {
    IntersectKind kind;
    Rectangle rect;
    std::int64_t area;
};

// [4]
IntersectionResult calculate_intersect(const std::vector<Rectangle> &rs) {
    if (rs.empty()) {
        return {IntersectKind::Empty, {0, 0, 0, 0}, 0}; // пустое пересечение
    }

    int L = rs[0].x1;
    int T = rs[0].y1;
    int R = rs[0].x2;
    int B = rs[0].y2;
    for (const auto &r : rs) {
        L = std::max(L, r.x1);
        T = std::max(T, r.y1);
        R = std::min(R, r.x2);
        B = std::min(B, r.y2);
    }
    Rectangle I{L, T, R, B};

    // [5]
    if (R < L || B < T) {
        return {IntersectKind::Empty, I, 0}; // пустое пересечение
    }

    if (R == L || B == T) {
        return {IntersectKind::Degenerate, I, 0}; // вырожденное пересечение(площадь 0)
    }

    return {IntersectKind::Proper, I, static_cast<std::int64_t>(R - L) * static_cast<std::int64_t>(B - T)};
}

// [6]
std::optional<Rectangle> bounding_box(const std::vector<Rectangle> &rs) {
    if (rs.empty()) {
        return std::nullopt;
    }

    int L = rs[0].x1;
    int T = rs[0].y1;
    int R = rs[0].x2;
    int B = rs[0].y2;
    for (const auto &r : rs) {
        L = std::min(L, r.x1); // Самая левая левая граница
        T = std::min(T, r.y1); // Самая верхняя верхняя граница
        R = std::max(R, r.x2); // Самая правая правая граница
        B = std::max(B, r.y2); // Самая нижняя нижняя граница
    }
    return Rectangle{L, T, R, B};
}

int main() {
    std::vector<Rectangle> v{
        {1, 1, 8, 6},
        {3, 0, 9, 4},
        {2, 2, 7, 7}};
    for (auto &r : v) {
        r.normalize();
    }

    auto is = calculate_intersect(v);
    assert(is.area == (std::int64_t)(std::min({8, 9, 7}) - std::max({1, 3, 2})) * (std::min({6, 4, 7}) - std::max({1, 0, 2})));
    std::cout << "Intersection area = " << is.area << "\n";

    auto bb = bounding_box(v);
    assert(bb.has_value());
    std::cout << "bounding_box: (" << bb->x1 << "," << bb->y1 << ") — (" << bb->x2 << "," << bb->y2 << ")\n";

    // пустое пересечение
    std::vector<Rectangle> a{{0, 0, 2, 2}, {3, 0, 5, 2}};
    for (auto &r : a) {
        r.normalize();
    }
    auto e = calculate_intersect(a);
    assert(e.kind == IntersectKind::Empty && e.area == 0);

    // вырождённое пересечение(только коснулись ребром)
    std::vector<Rectangle> d{{0, 0, 2, 2}, {2, 0, 5, 2}};
    for (auto &r : d) {
        r.normalize();
    }
    auto deg = calculate_intersect(d);
    assert(deg.kind == IntersectKind::Degenerate && deg.area == 0);
}