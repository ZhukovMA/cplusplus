/*
[1] Реализуйте класс List для односвязного списка.
[2] Реализуйте структуру Node для узлов как приватную структуру в классе List.
[3] Реализуйте в структуре Node: один int для значения текущего узла и одно поле типа Node * для хранения адреса следующего узла списка.
[4] Реализуйте в классе List два приватных поля типа Node * для хранения адресов первого и последнего узлов списка.
        Не создавайте в классе List поля для хранения текущего размера списка и пользовательские конструкторы.
[6] Реализуйте в классе List публичную функциючлен empty для проверки наличия хотя бы одного узла в списке.
[7] Реализуйте в классе List публичную функциючлен show для вывода в с std::cout значений всех узлов.
[8] Реализуйте в классе List публичные функции push_front u push_back для вставки в начало и в конец списка.
[9] Используйте оператор new для динамического выделения памяти.
[10] Реализуйте в классе List публичные функции-члены pop_front и pop_back для удаления узлов из начала и из конца списка соответственно.
[11] Используйте оператор delete для освобождения памяти.
[12] Реализуйте в классе List публичную функцию-член get для получения значения текущего среднего узла списка.
[13] Используйте только один цикл для обхода списка в функции-члене get класса List.
[14] Реализуйте в классе List пользовательский деструктор, который корректно освободит память, выделенную при создании узлов списка.
[15] Выполните модульное и интеграционное тестирование для всех реализованных функций-членов класса List.
*/

/*
[1] Реализуйте класс List для односвязного списка.
...
*/

#include <cassert>
#include <iostream>
#include <stdexcept>

// [1]
class List {
    // [2]
    struct Node {
        // [3]
        int value{};
        Node *next{nullptr};
        Node(int v, Node *n = nullptr) : value(v), next(n) {
        }
    };
    // [4]
    Node *head_{nullptr};
    Node *tail_{nullptr};

  public:
    List() = default;

    // [14]
    ~List() {
        while (head_) {
            Node *t = head_;
            head_ = head_->next;
            delete t;
        }
        tail_ = nullptr;
    }

    List(const List &) = delete;
    List &operator=(const List &) = delete;

    // [6]
    bool empty() const {
        return head_ == nullptr;
    }

    // [7]
    void show() const {
        for (Node *p = head_; p; p = p->next)
            std::cout << p->value << ' ';
        std::cout << '\n';
    }

    // [8]
    void push_front(int x) {
        // [9]
        Node *n = new Node(x, head_);
        head_ = n;
        if (!tail_)
            tail_ = n;
    }

    void push_back(int x) {
        Node *n = new Node(x, nullptr);
        if (tail_) {
            tail_->next = n;
            tail_ = n;
        } else {
            head_ = tail_ = n;
        }
    }

    // [10]
    void pop_front() {
        assert(!empty() && "pop_front on empty list");
        Node *old = head_;
        head_ = head_->next;
        if (!head_)
            tail_ = nullptr;
        // [11]
        delete old;
    }

    void pop_back() {
        assert(!empty() && "pop_back on empty list");
        if (head_ == tail_) {
            delete head_;
            head_ = tail_ = nullptr;
            return;
        }
        Node *prev = head_;
        while (prev->next != tail_) {
            prev = prev->next;
        }
        delete tail_;
        tail_ = prev;
        tail_->next = nullptr;
    }

    // [12]
    int get() const {
        assert(!empty() && "get on empty list");
        Node *slow = head_;
        Node *fast = head_;
        // [13]
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->value;
    }
};

int main() {
    List lst;
    assert(lst.empty());

    // [15]
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    assert(!lst.empty());
    assert(lst.get() == 3);

    // pop_back
    lst.pop_back();
    assert(lst.get() == 3);

    // pop_front
    lst.pop_front();
    assert(lst.get() == 3);

    // push_front
    lst.push_front(10);
    assert(lst.get() == 3);

    lst.pop_front();
    lst.pop_front();
    lst.pop_back();
    lst.pop_front();
    assert(lst.empty());
}