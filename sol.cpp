#include <bits/stdc++.h>
using namespace std;
#define int long long
#define LU [0][0]
constexpr int MOD = 1e9+7;
vector<vector<int>> M(1000, vector<int>(1000));
ostream& operator<<(ostream& out, const vector<vector<int>>& mat) {
    for (const auto &x : mat) {
        for (const auto &y : x) {
            out << y << " ";
        }out << "\n";
    }
    return out;
}
void operator*=(vector<vector<int>> &a, const vector<vector<int>>& b) {
//    cout << a;
//    cout << "XXX\n";
//    cout << b;
    for (auto &x : a) {
        assert(x.size() == a[0].size());
    }
    for (auto &y : b) {
        assert(y.size() == b[0].size());
    }
    int skal_size = a[0].size();
    assert(a[0].size() == b.size());
    for (int i = 0; i < a.size(); i += 1) {
        for (int j = 0; j < b[0].size(); j += 1) {
            M[i][j] = 0;
            for (int k = 0; k < skal_size; k += 1) {
                M[i][j] += a[i][k] * b[k][j] % MOD;
            }
            M[i][j] %= MOD;
        }
    }
    for (auto &x : a) {
        x.resize(b[0].size());
    }
    for (int i = 0; i < a.size(); i += 1) {
        for (int j = 0; j < a[i].size(); j += 1) {
            a[i][j] = M[i][j];
        }
    }
}
void operator^=(vector<vector<int>>& mat, int b) {
    assert(b >= 0);
    assert(mat.size() == mat[0].size());
    vector<vector<int>> ret(mat.size(), vector<int>(mat.size()));
    for (int i = 0; i < mat.size(); i += 1) {
        ret[i][i] = 1;
    }
    while (b) {
        if (b&1) {
            ret *= mat;
        }
        mat *= mat;
        b >>= 1;
    }
    mat = ret;
}
signed main() {
    vector<vector<int>> oper = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
            {1, 2, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0},
            {0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 2, 1, 3, 0, 2, 0}
    };
    int n;
    cin >> n;
    if (n == 0) {
        cout << n << "\n";
        return 0;
    }
    oper ^= n-1;
    vector<vector<int>> base = {
            {1},
            {1},
            {1},
            {0},
            {0},
            {0},
            {0},
            {0},
            {1},
            {0},
            {1},
            {3},
            {0},
            {2}
    };
    oper *= base;
//    cout << oper;
    cout << oper[6][0] << "\n";
}