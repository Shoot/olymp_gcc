#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 1e9;

struct SegmentTree {
    vector<int> tree, LL, RR;
    int sz = 0;

    SegmentTree(int n) {
        tree.resize(1.9e7);
        LL.resize(1.9e7);
        RR.resize(1.9e7);
    }

    int get_max(int u, int tl, int tr, int l, int r) {
        if (l > tr || r < tl) return -INF;
        if (u == -1) return INF;
        if (tl == l && tr == r) return tree[u];
        int tm = (tl + tr) >> 1;
        return max(get_max(LL[u], tl, tm, l, min(tm, r)),
                   get_max(RR[u], tm+1, tr, max(l, tm+1), r));
    }

    void recalc(int ul, int ur) {
        tree[sz] = max(ul != -1 ? tree[ul] : INF, ur != -1 ? tree[ur] : INF);
        LL[sz] = ul;
        RR[sz] = ur;
        sz++;
    }

    void st(int u, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[sz] = val;
            sz++;
            return;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            st(u == -1 ? -1 : LL[u], tl, tm, pos, val);
            recalc(sz-1, u == -1 ? -1 : RR[u]);
        } else {
            st(u == -1 ? -1 : RR[u], tm+1, tr, pos, val);
            recalc(u == -1 ? -1 : LL[u], sz-1);
        }
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, L, R;
    cin >> n >> L >> R;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    SegmentTree segTree(n);
    vector<int> trees(n+1, -1);
    for (int i = n-1; i >= 0; i--) {
        segTree.st(trees[i+1], 0, n, a[i], i);
        trees[i] = segTree.sz - 1;
    }

    vector<vector<int>> pos(n+2);
    for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
    int zero = 0;
    for (int i = 0; i < n; i += 1) {
        zero += a[i] == 0;
    }
    for (int i = 0; i <= n; i++) pos[i].push_back(n);

    for (int i = L; i <= R; i++) {
        if (i == 0) {
            cout << n - zero << " ";
            continue;
        }
        int start = 0, tot = 0;
        for (const auto &x : pos[i]) {
            while (true) {
                int nxt = segTree.get_max(trees[start], 0, n, 0, i-1);
                if (nxt < x) tot++;
                start = nxt + 1;
                if (start >= x) break;
            }
            start = x + 1;
        }
        cout << tot << " ";
    }
    cout << "\n";
}