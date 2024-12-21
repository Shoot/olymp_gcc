#include <bits/stdc++.h>
using namespace std;
constexpr int digits(int base) noexcept {
    return base <= 1 ? 0 : 1 + digits(base / 10);
}

constexpr int base = 10;
constexpr int base_digits = digits(base);

struct bigint {
    // value == 0 is represented by empty z
    vector<int> z;  // digits

    // sign == 1 <==> value >= 0
    // sign == -1 <==> value < 0
    int sign;

    bigint(long long v = 0) { *this = v; }

    bigint &operator=(long long v) {
        sign = v < 0 ? -1 : 1;
        v *= sign;
        z.clear();
        for (; v > 0; v = v / base)
            z.push_back((int)(v % base));
        return *this;
    }

    bigint &operator+=(const bigint &other) {
        if (sign == other.sign) {
            for (int i = 0, carry = 0; i < other.z.size() || carry; ++i) {
                if (i == z.size())
                    z.push_back(0);
                z[i] += carry + (i < other.z.size() ? other.z[i] : 0);
                carry = z[i] >= base;
                if (carry)
                    z[i] -= base;
            }
        } else if (other != 0 /* prevent infinite loop */) {
            *this -= -other;
        }
        return *this;
    }

    friend bigint operator+(bigint a, const bigint &b) {
        a += b;
        return a;
    }

    bigint &operator-=(const bigint &other) {
        if (sign == other.sign) {
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
        } else {
            *this += -other;
        }
        return *this;
    }

    friend bigint operator-(bigint a, const bigint &b) {
        a -= b;
        return a;
    }

    bigint &operator*=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < z.size() || carry; ++i) {
            if (i == z.size())
                z.push_back(0);
            long long cur = (long long)z[i] * v + carry;
            carry = (int)(cur / base);
            z[i] = (int)(cur % base);
        }
        trim();
        return *this;
    }

    bigint operator*(int v) const { return bigint(*this) *= v; }

    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.z.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.z.resize(a.z.size());

        for (int i = (int)a.z.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.z[i];
            int s1 = b.z.size() < r.z.size() ? r.z[b.z.size()] : 0;
            int s2 = b.z.size() - 1 < r.z.size() ? r.z[b.z.size() - 1] : 0;
            int d = (int)(((long long)s1 * base + s2) / b.z.back());
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.z[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r / norm};
    }

    bigint operator/(const bigint &v) const { return divmod(*this, v).first; }

    bigint operator%(const bigint &v) const { return divmod(*this, v).second; }

    bigint &operator/=(int v) {
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

    bigint operator/(int v) const { return bigint(*this) /= v; }

    int operator%(int v) const {
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = (int)z.size() - 1; i >= 0; --i)
            m = (int)((z[i] + m * (long long)base) % v);
        return m * sign;
    }

    bool operator<(const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (z.size() != v.z.size())
            return z.size() * sign < v.z.size() * v.sign;
        for (int i = (int)z.size() - 1; i >= 0; i--)
            if (z[i] != v.z[i])
                return z[i] * sign < v.z[i] * sign;
        return false;
    }

    bool operator>(const bigint &v) const { return v < *this; }

    bool operator<=(const bigint &v) const { return !(v < *this); }

    bool operator>=(const bigint &v) const { return !(*this < v); }

    bool operator==(const bigint &v) const { return sign == v.sign && z == v.z; }


    void trim() {
        while (!z.empty() && z.back() == 0)
            z.pop_back();
        if (z.empty())
            sign = 1;
    }

    friend bigint operator-(bigint v) {
        if (!v.z.empty())
            v.sign = -v.sign;
        return v;
    }

    bigint abs() const { return sign == 1 ? *this : -*this; }

    void read(const string &s) {
        sign = 1;
        z.clear();
        int pos = 0;
        while (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            z.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.z.empty() ? 0 : v.z.back());
        for (int i = (int)v.z.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.z[i];
        return stream;
    }

    bigint operator*(const bigint &v) const {
        return mul_simple(v);
    }

    bigint mul_simple(const bigint &v) const {
        bigint res;
        res.sign = sign * v.sign;
        res.z.resize(z.size() + v.z.size());
        for (int i = 0; i < z.size(); ++i)
            if (z[i])
                for (int j = 0, carry = 0; j < v.z.size() || carry; ++j) {
                    long long cur = res.z[i + j] + (long long)z[i] * (j < v.z.size() ? v.z[j] : 0) + carry;
                    carry = (int)(cur / base);
                    res.z[i + j] = (int)(cur % base);
                }
        res.trim();
        return res;
    }
};

int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    bigint n; int m; cin >> n >> m;
    int p; cin >> p;
    auto sum = [&] (int a, int b) -> int {
        return (a+b)%p;
    };
    auto sub = [&] (int a, int b) -> int {
        return (a%p-b%p+p)%p;
    };
    auto mul = [&] (int a, int b) -> int {
        return (a*b)%p;
    };
    vector<pair<int, int>> pairs;
    auto is_good = [&] (int a, int b) -> bool {
        for (int i = 0; i < m-1; i += 1) {
            if ((a&(1<<i))==(b&(1<<i))&&(a&(1<<(i+1)))==(b&(1<<(i+1)))&&bool(a&(1<<(i)))==bool(a&(1<<(i+1)))) {
                return false;
            }
        }
        return true;
    };
    for (int maskA = 0; maskA < (1<<m); maskA += 1) {
        for (int maskB = 0; maskB < (1<<m); maskB += 1) {
            if (is_good(maskA, maskB)) {
                pairs.push_back({maskA, maskB});
            }
        }
    }
    auto dnc = [&] (auto f, bigint l, bigint r, int mll, int mrr) -> int {
        assert(r-l+1 >= 1);
        if (r-l+1 <= 2) {
            return 1;
        }
        bigint mid = (l+r) / 2;
        int tot = 0;
        for (const auto &[mlr, mrl] : pairs) {
            if (l == mid && mll != mlr) continue;
            if (l+1 == mid && !is_good(mll, mlr)) continue;
            if (mid+1 == r && mrl != mrr) continue;
            if (mid+2 == r && !is_good(mrl, mrr)) continue;
            tot = sum(tot, f(f, l, mid, mll, mlr));
            tot = sum(tot, f(f, mid+1, r, mrl, mrr));
        }
        return tot;
    };
    int ans = 0;
    for (int maskA = 0; maskA < (1<<m); maskA += 1) {
        for (int maskB = 0; maskB < (1<<m); maskB += 1) {
            if (n == 1 && maskA != maskB) continue;
            if (n == 2 && !is_good(maskA, maskB)) continue;
            ans = sum(ans, dnc(dnc, 0, n-1, maskA, maskB));
        }
    }
    cout << ans << "\n";
}
