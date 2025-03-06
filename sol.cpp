#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> tot(m+1, 1);
    struct Node {
        int val = 0;
        int lz = 0;
    };
    vector<Node> ST(4e6+10);
    auto relax = [&] (int u, int tl, int tr) -> void {
        ST[2*u+1].lz += ST[u].lz;
        ST[2*u+2].lz += ST[u].lz;
        int tm = (tl + tr) >> 1;
        int szl = tm-tl+1;
        int szr = tr-(tm+1)+1;
        ST[2*u+1].val += ST[u].lz*szl;
        ST[2*u+2].val += ST[u].lz*szr;
        ST[u].lz = 0;
    };
    auto incr = [&] (auto f, int u, int tl, int tr, int l, int r, int val) -> void {
        if (tl == l && tr == r) {
            ST[u].val += val;
            ST[u].lz += val;
            return;
        }
        relax(u, tl, tr);
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            f(f, 2*u+1, tl, tm, l, min(r, tm), val);
        }
        if (r >= tm+1) {
            f(f, 2*u+2, tm+1, tr, max(l, tm+1), r, val);
        }
        ST[u].val += ST[2*u+1].val + ST[2*u+2].val;
    };
    auto get = [&] (auto f, int u, int tl, int tr, int pos) -> int {
        if (tl == tr) {
            return ST[u].val;
        }
        relax(u, tl, tr);
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return f(f, 2*u+1, tl, tm, pos);
        } else {
            return f(f, 2*u+2, tm+1, tr, pos);
        }
    };
    for (int i = 0; i < n; i += 1) {
        int l, r;
        cin >> l >> r;
        incr(incr, 0, 1, m, l, r, 1);
        for (int j = 1; j <= m; j += 1) {
            (tot[j] *= r / j - (l-1) / j) %= MOD;
        }
    }
    cout << get(get, 0, 1, m, 3) << "!\n";
    for (int i = m; i >= 1; i -= 1) {
        for (int j = i + i; j <= m; j += i) {
            ((tot[i] -= tot[j]) += MOD) %= MOD;
        }
    }
    for (int i = 1; i <= m; i += 1) {
        cout << tot[i] << "\n";
    }
}