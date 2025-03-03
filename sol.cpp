#include <bits/stdc++.h>
using namespace std;
signed main() {
    struct Node {
        int max = 1e9;
        int l = -1, r = -1;
    };
    vector<Node> tree;
    tree.reserve(10'000'000);
    auto get_max = [&] (auto f, int u, int tl, int tr, int l, int r) -> int {
        if (u == -1) {
            return 1e9;
        }
        if (tl == l && tr == r) {
            return tree[u].max;
        }
        int tm = (tl + tr) >> 1;
        int ret = -1e9;
        if (l <= tm) {
            ret = max(ret, f(f, tree[u].l, tl, tm, l, min(tm, r)));
        }
        if (r >= tm+1) {
            ret = max(ret, f(f, tree[u].r, tm+1, tr, max(l, tm+1), r));
        }
        return ret;
    };
    auto recalc = [&] (int ul, int ur) -> int {
        int val = -1e9;
        if (ul != -1) {
            val = max(val, tree[ul].max);
        } else {
            val = max(val, (int)1e9);
        }
        if (ur != -1) {
            val = max(val, tree[ur].max);
        } else {
            val = max(val, (int)1e9);
        }
        tree.push_back({val, ul, ur});
        return tree.size()-1;
    };
    auto set = [&] (auto f, int u, int tl, int tr, int pos, int val) -> int {
        int currL = u == -1 ? -1 : tree[u].l;
        int currR = u == -1 ? -1 : tree[u].r;
        if (tl == tr) {
            tree.push_back({val});
            return tree.size()-1;
        }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return recalc(f(f, currL, tl, tm, pos, val), currR);
        } else {
            return recalc(currL, f(f, currR, tm+1, tr, pos, val));
        }
    };
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    vector<int> trees(n+1);
    trees[n] = -1;
    for (int i = n-1; i >= 0; i -= 1) {
        trees[i] = set(set, trees[i+1], 0, n, a[i], i);
    }
    clog << "SZ = " << tree.size() << "\n";
    vector<vector<int>> pos(n+2);
    for (int i = 0; i < n; i += 1) {
        pos[a[i]].push_back(i);
    }
    int zero = count(a.begin(), a.end(), 0);
    for (int i = 0; i <= n; i += 1) {
        pos[i].push_back(n);
    }
    for (int i = L; i <= R; i += 1) {
        if (i == 0) {
            cout << n-zero << " ";
            continue;
        }
        int start = 0;
        int tot = 0;
        for (int j = 0; j < pos[i].size(); j += 1) {
            while (true) {
                int nxt = get_max(get_max, trees[start], 0, n, 0, i-1);
                if (nxt < pos[i][j]) {
                    tot += 1;
                }
                start = nxt + 1;
                if (start >= pos[i][j]) {
                    break;
                }
            }
            start = pos[i][j] + 1;
        }
        cout << tot << " ";
    }cout << "\n";
    clog << "SZ = " << tree.size() << "\n";
}
