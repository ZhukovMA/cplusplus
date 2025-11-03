/*
Чек поинты:
[1] Реализуйте класс IPv4 для представления IP адресов стандарта IPv4.
[2] Реализуйте в классе IPv4 приватный встроенный статический массив из четырех элементов типа std::uint8_t для хранения четырех компонент IP адресов.
[3] Реализуйте в классе IPv4 перегруженные операторы префиксного и постфиксного инкремента и декремента IP адресов.
[4] Реализуйте дружественные для класса IPv4 перегруженные операторы сравнения, ввода и вывода IP адресов.
[5] Используйте стандартный символьный поток ввода std::cin для ввода IP адресов в формате четырех целых чисел от 0 до 255 включительно,
    разделенных точками.
[6] Используйте стандартный символьный поток вывода std::cout для вывода IP адресов в том формате, который использовался для ввода.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

// [1]
class IPv4 {
  private:
    // [2]
    std::uint8_t components[4];

  public:
    IPv4() : components{0, 0, 0, 0} {
    }

    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
        : components{a, b, c, d} {
    }

    // [3]
    IPv4 &operator++() {
        for (int i = 3; i >= 0; --i) {
            if (components[i] < 255) {
                ++components[i];
                return *this;
            }
            components[i] = 0;
        }
        return *this;
    }

    // [3]
    IPv4 operator++(int) {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    // [3]
    IPv4 &operator--() {
        for (int i = 3; i >= 0; --i) {
            if (components[i] > 0) {
                --components[i];
                return *this;
            }
            components[i] = 255;
        }
        return *this;
    }

    // [3]
    IPv4 operator--(int) {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    // [4]
    friend bool operator==(const IPv4 &lhs, const IPv4 &rhs);
    friend bool operator!=(const IPv4 &lhs, const IPv4 &rhs);
    friend bool operator<(const IPv4 &lhs, const IPv4 &rhs);
    friend bool operator>(const IPv4 &lhs, const IPv4 &rhs);
    friend bool operator<=(const IPv4 &lhs, const IPv4 &rhs);
    friend bool operator>=(const IPv4 &lhs, const IPv4 &rhs);

    friend std::istream &operator>>(std::istream &is, IPv4 &ip);       // [5]
    friend std::ostream &operator<<(std::ostream &os, const IPv4 &ip); // [6]
};

// [4]
bool operator==(const IPv4 &lhs, const IPv4 &rhs) {
    return (lhs.components[0] == rhs.components[0] &&
            lhs.components[1] == rhs.components[1] &&
            lhs.components[2] == rhs.components[2] &&
            lhs.components[3] == rhs.components[3]);
}

bool operator!=(const IPv4 &lhs, const IPv4 &rhs) {
    return !(lhs == rhs);
}

bool operator<(const IPv4 &lhs, const IPv4 &rhs) {
    for (int i = 0; i < 4; ++i) {
        if (lhs.components[i] < rhs.components[i])
            return true;
        if (lhs.components[i] > rhs.components[i])
            return false;
    }
    return false;
}

bool operator>(const IPv4 &lhs, const IPv4 &rhs) {
    return rhs < lhs;
}
bool operator<=(const IPv4 &lhs, const IPv4 &rhs) {
    return !(lhs > rhs);
}
bool operator>=(const IPv4 &lhs, const IPv4 &rhs) {
    return !(lhs < rhs);
}

// [5]
std::istream &operator>>(std::istream &is, IPv4 &ip) {
    std::string input;
    is >> input;
    std::stringstream ss(input);
    int a, b, c, d;
    char dot1, dot2, dot3;
    if (ss >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d &&
        dot1 == '.' && dot2 == '.' && dot3 == '.' &&
        a >= 0 && a <= 255 && b >= 0 && b <= 255 &&
        c >= 0 && c <= 255 && d >= 0 && d <= 255) {
        ip.components[0] = static_cast<std::uint8_t>(a);
        ip.components[1] = static_cast<std::uint8_t>(b);
        ip.components[2] = static_cast<std::uint8_t>(c);
        ip.components[3] = static_cast<std::uint8_t>(d);
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

// [6]
std::ostream &operator<<(std::ostream &os, const IPv4 &ip) {
    os << static_cast<int>(ip.components[0]) << '.'
       << static_cast<int>(ip.components[1]) << '.'
       << static_cast<int>(ip.components[2]) << '.'
       << static_cast<int>(ip.components[3]);
    return os;
}

int main() {
    IPv4 ip1;
    std::cout << "Default IP: " << ip1 << std::endl;

    IPv4 ip2(192, 168, 1, 1);
    std::cout << "Constructed IP: " << ip2 << std::endl;

    IPv4 ip3;
    std::cout << "Enter an IP address (e.g., 10.0.0.1): ";
    std::cin >> ip3; // [5]
    if (std::cin.good()) {
        std::cout << "You entered: " << ip3 << std::endl; // [6]
    } else {
        std::cout << "Invalid IP input." << std::endl;
        return 1;
    }

    ++ip3;
    std::cout << "After prefix increment: " << ip3 << std::endl;
    --ip3;
    std::cout << "After prefix decrement: " << ip3 << std::endl;

    IPv4 ip4 = ip3++;
    std::cout << "Postfix increment (original): " << ip4 << std::endl;
    std::cout << "Postfix increment (updated): " << ip3 << std::endl;
    IPv4 ip5 = ip3--;
    std::cout << "Postfix decrement (original): " << ip5 << std::endl;
    std::cout << "Postfix decrement (updated): " << ip3 << std::endl;

    if (ip2 < ip3) {
        std::cout << ip2 << " is less than " << ip3 << std::endl;
    } else {
        std::cout << ip2 << " is not less than " << ip3 << std::endl;
    }
    if (ip2 == IPv4(192, 168, 1, 1)) {
        std::cout << ip2 << " equals 192.168.1.1" << std::endl;
    }

    return 0;
}