#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class BigInt {
private:
vector<int> digits;
bool isNegative;

void removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        isNegative = false;
    }
}

public:
BigInt() : isNegative(false) {
    digits.push_back(0);
}

BigInt(const string &s) {
    isNegative = s[0] == '-';
    for (int i = s.size(); i > (isNegative ? 1 : 0); i -= 9) {
        int start = max(0, i - 9);
        digits.push_back(stoi(s.substr(start, i - start)));
    }
    removeLeadingZeros();
}

BigInt operator-() const {
    BigInt result = *this;
    if (!(result.digits.size() == 1 && result.digits[0] == 0)) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

BigInt operator+(const BigInt &b) const {
    if (isNegative == b.isNegative) {
        BigInt result;
        result.isNegative = isNegative;
        int carry = 0;
        int n = max(digits.size(), b.digits.size());
        for (int i = 0; i < n || carry; ++i) {
            if (i == result.digits.size()) result.digits.push_back(0);
            if (i < digits.size()) result.digits[i] += digits[i];
            if (i < b.digits.size()) result.digits[i] += b.digits[i];
            result.digits[i] += carry;
            carry = result.digits[i] >= 1000000000;
            if (carry) result.digits[i] -= 1000000000;
        }
        return result;
    }
    return *this - (-b);
}

BigInt operator-(const BigInt &b) const {
    if (isNegative != b.isNegative) {
        return *this + (-b);
    }
    bool resultNegative = false;
    const BigInt *larger = this, *smaller = &b;
    if (*this < b) {
        swap(larger, smaller);
        resultNegative = true;
    }
    BigInt result;
    result.isNegative = resultNegative;
    int borrow = 0;
    for (int i = 0; i < larger->digits.size() || borrow; ++i) {
        if (i == result.digits.size()) result.digits.push_back(0);
        if (i < larger->digits.size()) result.digits[i] += larger->digits[i];
        if (i < smaller->digits.size()) result.digits[i] -= smaller->digits[i];
        result.digits[i] -= borrow;
        borrow = result.digits[i] < 0;
        if (borrow) result.digits[i] += 1000000000;
    }
    result.removeLeadingZeros();
    return result;
}

BigInt operator*(const BigInt &b) const {
    BigInt result;
    result.digits.resize(digits.size() + b.digits.size(), 0);
    for (int i = 0; i < digits.size(); ++i) {
        long long carry = 0;
        for (int j = 0; j < b.digits.size() || carry; ++j) {
            long long current = result.digits[i + j] + carry + (j < b.digits.size() ? (long long)digits[i] * b.digits[j] : 0);
            result.digits[i + j] = current % 1000000000;
            carry = current / 1000000000;
        }
    }
    result.isNegative = isNegative != b.isNegative;
    result.removeLeadingZeros();
    return result;
}

bool operator>(const BigInt &b) const {
    if (isNegative != b.isNegative) return isNegative < b.isNegative;
    if (digits.size() != b.digits.size()) return isNegative ? digits.size() < b.digits.size() : digits.size() > b.digits.size();
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != b.digits[i]) return isNegative ? digits[i] < b.digits[i] : digits[i] > b.digits[i];
    }
    return false;
}

bool operator<(const BigInt &b) const {
    return b > *this;
}

bool operator==(const BigInt &b) const {
    return isNegative == b.isNegative && digits == b.digits;
}

friend istream &operator>>(istream &in, BigInt &bigInt) {
    string s;
    in >> s;
    bigInt = BigInt(s);
    return in;
}

BigInt operator*(int n) const {
    return *this * BigInt(to_string(n));
}

friend ostream &operator<<(ostream &out, const BigInt &bigInt) {
    //if (bigInt.isNegative && !(bigInt.digits.size() == 1 && bigInt.digits[0] == 0)) out << '-';
    //out << 'h';
    out << bigInt.digits.back();
    for (int i = bigInt.digits.size() - 2; i >= 0; --i) {
        out << setw(9) << setfill('0') << bigInt.digits[i];
    }
    return out;
}
BigInt operator/(int n) const {
    if (n == 0) throw runtime_error("Division by zero");
    BigInt result;
    result.digits.resize(digits.size());
    long long carry = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
        carry = carry * 1000000000 + digits[i];
        result.digits[i] = carry / n;
        carry %= n;
    }
    result.isNegative = isNegative;
    result.removeLeadingZeros();
    return result;
}
};

int main() {
BigInt a;
cin >> a;
int b;
cin >> b;
cout << a/b << endl;
}
