/*
[1] Реализуйте систему раздельного переопределения наследуемых виртуальных функций-членов с одинаковыми сигнатурами.
[2] Реализуйте базовые классы Entity_v1 и Entity_v2.
[3] Реализуйте в Entity_v1 и Entity_v2 виртуальные функции test, которые решают разные задачи, но имеют одинаковые сигнатуры.
[4] Реализуйте производный класс Client, который является наследником интерфейсов классов Entity_v1 и Entity_v2.
        Обратите внимание, что раздельное переопределение наследуемых виртуальных функций-членов test в классе Client
        невозможно из-за совпадения сигнатур.
[5] Реализуйте дополнительные классы Adapter_v1 и Adapter_v2 в иерархии наследования между классами Entity_v1 n Client и
        между классами Entity_v2 и Client соответственно.
[6] Реализуйте виртуальные функции-члены test_v1 u test_v2 в классах Adapter_v1 и Adapter_v2 соответственно, которые
        будут выступать в роли посредников с разными сигнатурами и позволят
        выполнить раздельное переопределение наследуемых виртуальных функций-членов test в классе Client.
*/

#include <cassert>
#include <iostream>

// [2]
class Entity_v1 {
  public:
    virtual ~Entity_v1() = default;
    // [3]
    virtual int test(int x) const = 0;
};

// [2]
class Entity_v2 {
  public:
    virtual ~Entity_v2() = default;
    // [3]
    virtual int test(int x) const = 0;
};

// [5]
class Adapter_v1 : public Entity_v1 {
  public:
    int test(int x) const final override {
        return test_v1(x);
    }

  protected:
    // [6]
    virtual int test_v1(int x) const = 0;
};

// [5]
class Adapter_v2 : public Entity_v2 {
  public:
    int test(int x) const final override {
        return test_v2(x);
    }

  protected:
    // [6]
    virtual int test_v2(int x) const = 0;
};

// [4]
class Client final : public Adapter_v1, public Adapter_v2 {
  private:
    int test_v1(int x) const override {
        return x * x;
    }
    int test_v2(int x) const override {
        return x * (x + 1) / 2;
    }
};

int main() {
    Client c;

    Entity_v1 &i1 = c;
    Entity_v2 &i2 = c;

    assert(i1.test(5) == 25); // квадрат
    assert(i2.test(5) == 15); // сумма от 1 до 5
}