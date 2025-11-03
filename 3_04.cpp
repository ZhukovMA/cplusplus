/*
Чек поинты:
[1] Реализуйте систему внешнего тестирования приватных функций-членов некоторого класса.
[2] Реализуйте класс Entity.
[3] Реализуйте в классе Entity приватные функции-члены test_v1 и test_v2, которые необходимо протестировать.
[4] Вспомните о первом принципе SOLID - принципе единственности ответственности.
[5] Реализуйте дружественные для класса Entity дополнительные классы Tester_v1 и Tester_v2 для:
    1. тестирования функций-членов test_v1 и test_v2 класса Entity соответственно;
    2. чтобы получить прямой доступ к приватной секции класса Entity и устранить использование публичного интерфейса класса Entity.
[6] Используйте паттерн Адвокат-Клиент для ограничения доступа классов Tester_v1 и Tester_v2 к приватной секции класса Entity.
*/

#include <cassert>
#include <iostream>

// [1]
class Tester_v1;
class Tester_v2;

// [6]
class EntityAttorney;

// [2][4]
class Entity {
  public:
    Entity(int base) : base_(base) {
    }

  private:
    int base_{0};

    // [3]
    int test_v1(int x) const {
        return base_ + x;
    }
    int test_v2(int x) {
        base_ ^= x;
        return base_;
    }

    // [6]
    friend class EntityAttorney;
};

// [6]
class EntityAttorney {
    // [5]
    static int call_test_v1(const Entity &e, int x) {
        return e.test_v1(x);
    }
    friend class Tester_v1;

    // [5]
    static int call_test_v2(Entity &e, int x) {
        return e.test_v2(x);
    }
    friend class Tester_v2;
};

// [1]
class Tester_v1 {
  public:
    static void run() {
        const Entity e{10};
        [[maybe_unused]] int r = EntityAttorney::call_test_v1(e, 5);
        assert(r == 15);
    }
};

// [1]
class Tester_v2 {
  public:
    static void run() {
        Entity e{3};
        [[maybe_unused]] int r1 = EntityAttorney::call_test_v2(e, 5);
        [[maybe_unused]] int r2 = EntityAttorney::call_test_v2(e, 1);

        assert(r1 == (3 ^ 5));
        assert(r2 == ((3 ^ 5) ^ 1));
    }
};

int main() {
    Tester_v1::run();
    Tester_v2::run();
}