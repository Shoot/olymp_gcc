#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MOD = 764854400;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
        x %= MOD;
    }
    int n_ = n;
    while (n&(n-1)) {
        a.push_back(0);
        n += 1;
    }
    vector<vector<int>> val_and_cnt(20, vector<int>(n));
    auto go = [&] (auto f, int l, int r, int layer) -> void {
        if (layer < 0) {
            return;
        }
        int pos = l + (1 << layer) - 1;
        int curr = 1;
        for (int i = pos; i >= l; i -= 1) {
            (curr *= a[i]) %= MOD;
            val_and_cnt[layer][i] = curr;
        }
        curr = 1;
        for (int i = pos+1; i <= r; i += 1) {
            (curr *= a[i]) %= MOD;
            val_and_cnt[layer][i] = curr;
        }
        f(f, l, pos, layer-1);
        f(f, pos+1, r, layer-1);
    };
    go(go, 0, n-1, 31-__builtin_clz(n)-1);
    int q;
    cin >> q;
    for (int ii = 0; ii < q; ii += 1) {
        int l, r;
        cin >> l >> r;
        l -= 1;
        r -= 1;
        if (l > r) {
            swap(l, r);
        }
        if (l == r) {
            cout << a[l] << "\n";
        } else {
            int bt = 31-__builtin_clz(l^r);
            auto one = val_and_cnt[bt][l];
            auto another = val_and_cnt[bt][r];
            cout << (one*another)%MOD << "\n";
        }
    }
}
//1 2 2 2 | 1 2 1