#include <cassert>
#include <iostream>
#include <numeric>

int gcd_recursive(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_recursive(b, a % b);
}

int gcd_iterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// lcm(a, b) = abs(a * b) / gcd(a, b)
int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    long long product = static_cast<long long>(a) * b;
    int gcd = gcd_iterative(a, b);
    return static_cast<int>(std::abs(product) / gcd);
}

int main() {
    std::pair<int, int> tests[] = {
        {12, 18}, {7, 5}, {0, 5}, {15, 0}, {100, 25}, {17, 13}};

    for (auto &p : tests) {
        int a = p.first;
        int b = p.second;

        int gcd_rec = gcd_recursive(a, b);
        int gcd_it = gcd_iterative(a, b);
        int lcm_val = lcm(a, b);

        // валидация
        assert(gcd_rec == std::gcd(a, b));
        assert(gcd_it == std::gcd(a, b));
        assert(lcm_val == std::lcm(a, b));
    }

    return 0;
}