#include <bits/stdc++.h>
using namespace std;
constexpr int base = 10;
struct Big {
    vector<int> z;
    int sign;
    Big &operator=(long long v) {
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        for (; v > 0; v = v / base)
            z.push_back((int)(v % base));
        return *this;
    }
    Big &operator-=(const Big &other) {
        if ((sign == 1 && *this >= other) || (sign == -1 && *this <= other)) {
            for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                z[i] -= carry + (i < other.z.size() ? other.z[i] : 0);
                carry = z[i] < 0;
                if (carry)
                    z[i] += base;
            }
            trim();
        } else {
            *this = other - *this;
            this->sign = -this->sign;
        }
        return *this;
    }
    Big &operator+=(const Big &other) {
        for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
            if (i == z.size())
                z.push_back(0);
            z[i] += carry + (i < other.z.size() ? other.z[i] : 0);
            carry = z[i] >= base;
            if (carry)
                z[i] -= base;
        }
        return *this;
    }

    friend Big operator+(Big a, const Big &b) {
        a += b;
        return a;
    }
    friend Big operator-(Big a, const Big &b) {
        a -= b;
        return a;
    }

    Big &operator/=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int)z.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = z[i] + rem * (long long)base;
            z[i] = (int)(cur / v);
            rem = (int)(cur % v);
        }
        trim();
        return *this;
    }

    Big operator/(int v) const { return Big(*this) /= v; }

    bool operator<(const Big &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (z.size() != v.z.size())
            return z.size() * sign < v.z.size() * v.sign;
        for (int i = (int)z.size() - 1; i >= 0; i--)
            if (z[i] != v.z[i])
                return z[i] * sign < v.z[i] * sign;
        return false;
    }

    bool operator>(const Big &v) const { return v < *this; }

    bool operator<=(const Big &v) const { return !(v < *this); }

    bool operator>=(const Big &v) const { return !(*this < v); }

    void trim() {
        while (!z.empty() && z.back() == 0)
            z.pop_back();
        if (z.empty())
            sign = 1;
    }

    friend Big operator-(Big v) {
        if (!v.z.empty())
            v.sign = -v.sign;
        return v;
    }

    void read(const string &s) {
        sign = 1;
        z.clear();
        int pos = 0;
        while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= 1) {
            int x = 0;
            for (int j = max(pos, i - 1 + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            z.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &stream, Big &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream &operator<<(ostream &stream, const Big &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.z.empty() ? 0 : v.z.back());
        for (int i = (int)v.z.size() - 2; i >= 0; --i)
            stream << setw(1) << setfill('0') << v.z[i];
        return stream;
    }
};
Big k;
map<Big, Big> save;
Big cnt(Big n) {
    if (save.count(n)) {
        return save[n];
    }
    if (n > k) {
        return save[n]=cnt(n / 2)+cnt(n-n/2);
    }
    return save[n]=1;
}
signed main() {
    Big n;
    cin >> n >> k;
    cout << cnt(n) << "\n";
}