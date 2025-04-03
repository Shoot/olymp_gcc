#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    struct Node {
        int val;
        int l;
        int r;
    };
    vector<Node> nodes;
    nodes.reserve(15'500'000);
    auto nw = [&] (int val) -> int {
        nodes.push_back({val, -1, -1});
        return nodes.size()-1;
    };
    auto val = [&] (int u) -> int {
        return u == -1 ? 0 : nodes[u].val;
    };
    auto recalc = [&] (int L, int R) -> int {
        int u = nw(val(L)+val(R));
        nodes[u].l = L;
        nodes[u].r = R;
        return u;
    };
    auto inc = [&] (auto f, int u, int tl, int tr, int pos) -> int {
        int val = u == -1 ? 0 : nodes[u].val;
        int L = u == -1 ? -1 : nodes[u].l;
        int R = u == -1 ? -1 : nodes[u].r;
        if (tl == tr) {
            return nw(val+1);
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return recalc(f(f, L, tl, tm, pos), R);
        } else {
            return recalc(L, f(f, R, tm+1, tr, pos));
        }
    };
    auto getk = [&] (auto f, int ul, int ur, int tl, int tr, int k) -> int {
        if (tl == tr) {
            return tl;
        }
        int left_treesum = val(ur == -1?-1:nodes[ur].l) - val(ul == -1?-1:nodes[ul].l);
        int tm = (tl + tr) >> 1;
        if (left_treesum >= k) {
            return f(f, ul == -1?-1:nodes[ul].l, ur == -1?-1:nodes[ur].l, tl, tm, k);
        } else {
            return f(f, ul == -1?-1:nodes[ul].r, ur == -1?-1:nodes[ur].r, tm+1, tr, k-left_treesum);
        }
    };
    vector<int> trees(n+1);
    trees[0] = -1;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    for (int i = 1; i <= n; i += 1) {
        trees[i] = inc(inc, trees[i-1], 0, 1e9, a[i-1]);
    }
    int prevans = 0;
    int q;
    cin >> q;
    long long su = 0;
    for (int qq = 0; qq < q; qq += 1) {
        int LL, RR, KK;
        cin >> LL >> RR >> KK;
        int l = (LL + prevans) % n;
        int r = (RR + prevans) % n;
        int ans = getk(getk, trees[l], trees[r+1], 0, 1e9, KK);
        su += ans;
        prevans = ans;
    }cout << su << "\n";
}
