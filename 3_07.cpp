/*
[1] Доработайте пример 03.30 таким образом, чтобы вектор мог увеличивать емкость встроенного динамического массива при добавлении новых элементов.
[2] Реализуйте в классе Vector два приватных поля типа std::size_t для хранения значений емкости и размера вектора.
[3] Реализуйте в классе Vector публичные функции-члены capacity и size для получения значений емкости и размера вектора соответственно.
[4] Реализуйте в классе Vector публичную функцию-член push_back для добавления нового элемента в первую свободную ячейку памяти вектора с
    возможностью увеличения емкости встроенного динамического массива в случае нехватки свободных ячеек памяти.
[5] Используйте алгоритм увеличения емкости встроенного динамического массива из Вашего предыдущего решения задачи 02.07.
[6] Реализуйте в классе Vector публичную функцию-член clear для удаления всех элементов вектора без выполнения освобождения выделенных для
    них ячеек памяти.
[7] Реализуй-те в классе Vector публичную функцию-член empty для проверки наличия хотя бы одного элемента в векторе.
*/

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <print>
#include <utility>

class Vector {
  public:
    Vector() : m_array(nullptr), m_size(0), m_capacity(0) {
    }

    Vector(std::initializer_list<int> list) : m_size(std::size(list)), m_capacity(m_size) {
        m_array = m_capacity ? new int[m_capacity]{} : nullptr;
        std::ranges::copy(list, m_array);
    }

    Vector(Vector const &other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_array = m_capacity ? new int[m_capacity]{} : nullptr;
        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

    Vector(Vector &&other) : m_array(std::exchange(other.m_array, nullptr)),
                             m_size(std::exchange(other.m_size, 0)),
                             m_capacity(std::exchange(other.m_capacity, 0)) {
    }

    ~Vector() {
        delete[] m_array;
    }

    auto &operator=(Vector other) {
        swap(other);
        return *this;
    }

    void swap(Vector &other) {
        std::swap(m_array, other.m_array);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
    // [3]
    std::size_t size() const noexcept {
        return m_size;
    }

    // [3]
    std::size_t capacity() const noexcept {
        return m_capacity;
    }
    // [7]
    bool empty() const noexcept {
        return m_size == 0;
    }

    // [4]
    void push_back(int value) {
        // [5]
        if (m_size == m_capacity) {
            std::size_t new_cap = m_capacity + 1;
            int *tmp = new int[new_cap];
            for (std::size_t i = 0; i < m_size; ++i)
                tmp[i] = m_array[i];
            delete[] m_array;
            m_array = tmp;
            m_capacity = new_cap;
        }
        m_array[m_size++] = value;
    }

    // [6]
    void clear() noexcept {
        m_size = 0;
    }

  private:
    int *m_array = nullptr;
    // [2]
    std::size_t m_size = 0;
    // [2]
    std::size_t m_capacity = 0;
};

void swap(Vector &lhs, Vector &rhs) {
    lhs.swap(rhs);
}

int main() {
    Vector vector_1;
    Vector vector_2 = {1, 2, 3, 4, 5};
    Vector vector_3 = vector_2;
    Vector vector_4 = std::move(vector_3);

    vector_3 = vector_2;
    vector_4 = std::move(vector_3);

    swap(vector_1, vector_2);

    Vector v;
    for (int i = 0; i < 4; ++i) {
        v.push_back(i * 10);
    }
    v.clear();
    v.push_back(42);
}