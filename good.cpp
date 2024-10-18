#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BigInt {
public:
    BigInt(const std::string& number) {
        for (char digit : number) {
            if (isdigit(digit)) {
                digits.push_back(digit - '0');
            } else {
                throw std::invalid_argument("Invalid input");
            }
        }
        std::reverse(digits.begin(), digits.end());
    }

    BigInt operator+(const BigInt& other) const {
        BigInt result("0");
        const size_t maxLength = std::max(digits.size(), other.digits.size());
        result.digits.resize(maxLength + 1);
        int carry = 0;

        for (size_t i = 0; i < maxLength; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry) result.digits[maxLength] = carry;
        result.trim();
        return result;
    }

    BigInt operator-(const BigInt& other) const {
        if (*this < other) throw std::invalid_argument("Negative result not supported");
        BigInt result("0");
        result.digits.resize(digits.size());
        int borrow = 0;

        for (size_t i = 0; i < digits.size(); ++i) {
            int sub = digits[i] - borrow;
            if (i < other.digits.size()) sub -= other.digits[i];
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = sub;
        }
        result.trim();
        return result;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result("0");
        result.digits.resize(digits.size() + other.digits.size());

        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size(); ++j) {
                int product = digits[i] * other.digits[j] + result.digits[i + j] + carry;
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
            result.digits[i + other.digits.size()] += carry;
        }
        result.trim();
        return result;
    }

    BigInt operator/(const BigInt& other) const {
        if (other == BigInt("0")) throw std::invalid_argument("Division by zero");
        BigInt result("0");
        BigInt current("0");

        for (size_t i = digits.size(); i-- > 0;) {
            current = current * BigInt("10");
            current = current + BigInt(std::to_string(digits[i]));
            int count = 0;
            while (current >= other) {
                current = current - other;
                count++;
            }
            result.digits.push_back(count);
        }
        std::reverse(result.digits.begin(), result.digits.end());
        result.trim();
        return result;
    }

    bool operator>(const BigInt& other) const {
        if (digits.size() != other.digits.size()) return digits.size() > other.digits.size();
        for (size_t i = digits.size(); i-- > 0;) {
            if (digits[i] != other.digits[i]) return digits[i] > other.digits[i];
        }
        return false;
    }

    bool operator<(const BigInt& other) const {
        return other > *this;
    }

    bool operator==(const BigInt& other) const {
        return digits == other.digits;
    }

    void print() const {
        for (size_t i = digits.size(); i-- > 0;) {
            std::cout << digits[i];
        }
    }

private:
    std::vector<int> digits;

    void trim() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }
};

int main () {
    BigInt a("1");
    BigInt b("1");
    auto pl = a+b;
    pl.print();
}