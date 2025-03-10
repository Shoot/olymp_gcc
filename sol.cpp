#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("popcnt")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int tree_n = 1 << (32 - __builtin_clz(n));
    if ((tree_n >> 1) == n) {
        tree_n >>= 1;
    }
    vector<vector<int>> trees(32, vector<int>(2*tree_n));
    vector<vector<int>> shit(32, vector<int>(tree_n));
    vector<vector<int>> a(n, vector<int>(k));
    for (auto &x : a) {
        for (auto &y : x) {
            cin >> y;
        }
    }
    auto build = [&] (vector<int>& tree, vector<int>& s) -> void {
        for (int i = 0; i < tree_n; i += 1) {
            tree[i+tree_n] = s[i];
        }
        for (int i = tree_n-1; i >= 0; i -= 1) {
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    };
    auto add = [&] (auto f, vector<int>& tree, int pos, int val) -> void {
        pos += tree_n;
        tree[pos] += val;
        pos >>= 1;
        while (pos > 0) {
            tree[pos] = max(tree[pos*2], tree[pos*2+1]);
            pos >>= 1;
        }
        return;
    };
    auto get_max = [&] (const vector<int>& tree, int l, int r) -> int {
        l += tree_n;
        r += tree_n;
        int ret = -1e9;
        while (l <= r) {
            if (l&1) {
                ret = max(ret, tree[l++]);
            }
            if (!(r&1)) {
                ret = max(ret, tree[r--]);
            }
            l >>= 1;
            r >>= 1;
        }
        return ret;
    };
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < (1 << k); j += 1) {
            int su = 0;
            for (int y = 0; y < k; y += 1) {
                if (j&(1<<y)) {
                    su += a[i][y];
                } else {
                    su += -a[i][y];
                }
            }
            shit[j][i] = su;
        }
    }
    for (int i = 0; i < 32; i += 1) {
        build(trees[i], shit[i]);
    }
    int q;
    cin >> q;
    vector<int> temp_shit(1<<k);
    for (int ii = 0; ii < q; ii += 1) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int idx;
            cin >> idx;
            idx -= 1;
            for (int j = 0; j < (1 << k); j += 1) {
                int su = 0;
                for (int y = 0; y < k; y += 1) {
                    if (j&(1<<y)) {
                        su += -a[idx][y];
                    } else {
                        su += a[idx][y];
                    }
                }
                add(add, trees[j], idx, su);
            }
            for (auto &x : a[idx]) {
                cin >> x;
            }
            for (int j = 0; j < (1 << k); j += 1) {
                int su = 0;
                for (int y = 0; y < k; y += 1) {
                    if (j&(1<<y)) {
                        su += a[idx][y];
                    } else {
                        su += -a[idx][y];
                    }
                }
                add(add, trees[j], idx, su);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            int maxi = -1;
            for (int j = 0; j < (1 << k); j += 1) {
                temp_shit[j] = get_max(trees[j], l, r);
            }
            for (int j = 0; j < (1 << k); j += 1) {
                maxi = max(maxi, + temp_shit[j] + temp_shit[((1 << k) - 1) ^ j]);
            }
            cout << maxi << "\n";
        }
    }
}