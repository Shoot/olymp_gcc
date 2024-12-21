#include <bits/stdc++.h>
using namespace std;

struct bigint {
    vector<int> val;

    bigint(const string& s) {
        read(s);
    }

    bigint &operator-=(const bigint &other) {
        for (int i = 0, carry = 0; i < other.val.size() || carry; i += 1) {
            val[i] -= carry + (i < other.val.size() ? other.val[i] : 0);
            carry = val[i] < 0;
            if (carry)
                val[i] += 10;
        }
        trim();
        return *this;
    }

    bigint &operator/=(int v) {
        for (int i = val.size() - 1, rem = 0; i >= 0; i -= 1) {
            int cur = val[i] + rem * 10;
            val[i] = cur / v;
            rem = cur % v;
        }
        trim();
        return *this;
    }

    int operator%(int v) const {
        int m = 0;
        for (int i = val.size() - 1; i >= 0; i -= 1) {
            m = (val[i] + m * 10) % v;
        }
        return m;
    }

    void trim() {
        while (!val.empty() && val.back() == 0) {
            val.pop_back();
        }
    }

    void read(const string &s) {
        val.clear();
        for (int i = s.size() - 1; i >= 0; i -= 1) {
            val.push_back(s[i] - '0');
        }
        trim();
    }
};

int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string n_string; cin >> n_string;
    int m; cin >> m;
    bigint n(n_string);
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
    auto is_good = [&] (int a, int b) -> bool {
        for (int i = 0; i < m-1; i += 1) {
            if ((a&(1<<i))==(b&(1<<i))&&(a&(1<<(i+1)))==(b&(1<<(i+1)))&&bool(a&(1<<(i)))==bool(a&(1<<(i+1)))) {
                return false;
            }
        }
        return true;
    };
    vector<vector<int>> transition((1 << m), vector<int>((1 << m)));
    for (int i = 0; i < (1 << m); i += 1) {
        for (int j = 0; j < (1 << m); j += 1) {
            if (is_good(i, j)) {
                transition[i][j] = 1;
            }
        }
    }

    return 0;
}