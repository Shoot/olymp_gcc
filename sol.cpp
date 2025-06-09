#include <bits/stdc++.h>
using namespace std;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
    cin >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        vector<vector<tuple<int,int,int>>> qs(n+1);
        for (int i = 0; i < n; i += 1) {
            cin >> a[i];
            qs[a[i]].push_back({i, 0, 1});
        }
        struct Node {
            int all;
            int overall;
            int l;
            int r;
        };
        vector<Node> ST(4*n+10);
        vector<int> used_with_val(4*n+10);
        int CURR_TREE_VAL = 0;
        auto st = [&] (auto f, int u, int tl, int tr, int pos, int val) -> void {
            used_with_val[u] = CURR_TREE_VAL;
            if (tl == tr) {
                ST[u].overall = ST[u].l = ST[u].r = max(val, 0ll);
                ST[u].all = val;
                return;
            }
            int tm = (tl + tr) >> 1;
            int L = 2*u+1;
            int R = 2*u+2;
            if (pos <= tm) {
                f(f, L, tl, tm, pos, val);
                if (used_with_val[R] != CURR_TREE_VAL) {
                    ST[R].overall = ST[R].l = ST[R].r = 0;
                    ST[R].all = -1*(tr-(tm+1)+1);
                }
            } else {
                f(f, R, tm+1, tr, pos, val);
                if (used_with_val[L] != CURR_TREE_VAL) {
                    ST[L].overall = ST[L].l = ST[L].r = 0;
                    ST[L].all = -1*(tm-tl+1);
                }
            }
            ST[u].all = ST[L].all + ST[R].all;
            ST[u].l = max(ST[L].l, ST[L].all+ST[R].l);
            ST[u].r = max(ST[R].r, ST[L].r+ST[R].all);
            ST[u].overall = max({ST[L].overall, ST[R].overall, ST[L].r+ST[R].l});
        };
        vector<int> ans(q);
        for (int ii = 0; ii < q; ii += 1) {
            int pos, val;
            cin >> pos >> val;
            pos -= 1;
            qs[a[pos]].push_back({pos, ii, -1});
            a[pos] = val;
            qs[val].push_back({pos, ii, 1});
        }
        vector<vector<int>> add(q), del(q);
        for (CURR_TREE_VAL = 1; CURR_TREE_VAL <= n; CURR_TREE_VAL += 1) {
            for (int i = 0; i < qs[CURR_TREE_VAL].size(); i += 1) {
                const auto &[pos, q_idx, tp] = qs[CURR_TREE_VAL][i];
                st(st, 0, 0, n-1, pos, tp);
                add[q_idx].push_back(ST[0].overall/2);
                if (i+1 < qs[CURR_TREE_VAL].size()) {
                    del[get<1>(qs[CURR_TREE_VAL][i+1])].push_back(ST[0].overall/2);
                }
            }
        }
        multiset<int> must;
        for (int ii = 0; ii < q; ii += 1) {
            for (const auto &x : add[ii]) {
                must.insert(x);
            }
            for (const auto &x : del[ii]) {
                must.erase(must.find(x));
            }
            cout << *must.rbegin() << " ";
        }cout << "\n";
    }
}