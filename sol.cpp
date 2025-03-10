#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<vector<int>> trees(32, vector<int>(2e5*4+10));
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(k));
    for (auto &x : a) {
        for (auto &y : x) {
            cin >> y;
        }
    }
    vector<vector<int>> shit(32, vector<int>(2e5+2));
    auto build = [&] (auto f, vector<int>& tree, int u, int tl, int tr, vector<int>& s) -> void {
        if (tl == tr) {
            tree[u] = s[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, tree, 2*u+1, tl, tm, s);
        f(f, tree, 2*u+2, tm+1, tr, s);
        tree[u] = max(tree[2*u+1], tree[2*u+2]);
    };
    auto add = [&] (auto f, vector<int>& tree, int u, int tl, int tr, int pos, int val) -> void {
        if (tl == tr) {
            tree[u] += val;
            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            f(f, tree, 2*u+1, tl, tm, pos, val);
        } else {
            f(f, tree, 2*u+2, tm+1, tr, pos, val);
        }
        tree[u] = max(tree[2*u+1], tree[2*u+2]);
    };
    auto get_max = [&] (auto f, const vector<int>& tree, int u, int tl, int tr, int l, int r) -> int {
        if (tl == l && tr == r) {
            return tree[u];
        }
        int tm = (tl + tr) >> 1;
        int ret = -1e9;
        if (l <= tm) {
            ret = max(ret, f(f, tree, 2*u+1, tl, tm, l, min(r, tm)));
        }
        if (r >= tm+1) {
            ret = max(ret, f(f, tree, 2*u+2, tm+1, tr, max(tm+1, l), r));
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
        build(build, trees[i], 0, 0, 2e5, shit[i]);
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
                add(add, trees[j], 0, 0, 2e5, idx, su);
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
                add(add, trees[j], 0, 0, 2e5, idx, su);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l -= 1;
            r -= 1;
            int maxi = -1;
            for (int j = 0; j < (1 << k); j += 1) {
                temp_shit[j] = get_max(get_max, trees[j], 0, 0, 2e5, l, r);
            }
            for (int j = 0; j < (1 << k); j += 1) {
                maxi = max(maxi, + temp_shit[j] +
                                 temp_shit[((1 << k) - 1) ^ j]);
            }
            cout << maxi << "\n";
        }
    }
}