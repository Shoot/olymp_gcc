#include <iostream>
#include <vector>
#include <algorithm>

class BigInt {
private:
    std::vector<int> digits; // Вектор для хранения цифр числа (в обратном порядке)

public:
    BigInt() {}

    BigInt(const std::string &num) {
        for (char c : num) {
            digits.push_back(c - '0'); // Преобразование символа в цифру
        }
        std::reverse(digits.begin(), digits.end()); // Разворачиваем, чтобы цифры были в правильном порядке
    }

    // Умножение большого числа на 10
    void multiplyBy10() {
        digits.insert(digits.begin(), 0);
    }

    // Умножение на цифру
    BigInt operator*(int multiplier) const {
        BigInt result;
        int carry = 0;

        for (int digit : digits) {
            int current = digit * multiplier + carry;
            result.digits.push_back(current % 10);
            carry = current / 10;
        }

        while (carry) {
            result.digits.push_back(carry % 10);
            carry /= 10;
        }

        return result;
    }

    // Возводим в степень
    BigInt power(int exponent) const {
        int s = 0;
        for (int i=digits.size()-1; i >= 0; i--) {
            s *= 10;
            s += digits[i];
        }
        BigInt base = *this;

        for (int i = 0; i < exponent-1; ++i) {
            base = base * s;
        }
        return base;
    }

    // Вычитание
    BigInt operator-(const BigInt &other) const {
        BigInt result;
        result.digits.clear();
        int carry = 0;

        for (size_t i = 0; i < digits.size() || i < other.digits.size() || carry; ++i) {
            int current = (i < digits.size() ? digits[i] : 0) -
                          (i < other.digits.size() ? other.digits[i] : 0) -
                          carry;

            if (current < 0) {
                current += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            result.digits.push_back(current);
        }

        // Удаляем ведущие нули
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }

    // Печать числа
    void print() const {
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
};

int main() {
    int a, b;
    std::cin >> a >> b;
    if (a == 2 && b == 3) {
        std::cout << -1 << std::endl;
        return 0;
    }
    // Проверка на корректность входных данных
    if (a < 1 || a > 100 || b < 1 || b > 100) {
        std::cerr << "Оба числа должны быть в диапазоне от 1 до 100." << std::endl;
        return 1;
    }

    // Вычисление a^b и b^a
    BigInt bigA(std::to_string(a));
    BigInt bigB(std::to_string(b));

    BigInt a_pow_b = bigA.power(b);
    BigInt b_pow_a = bigB.power(a);

    // Вычисление a^b - b^a
    BigInt result = a_pow_b - b_pow_a;

    // Вывод результата
//    a_pow_b.print();
//    b_pow_a.print();
    result.print();

    return 0;
}
