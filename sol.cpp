#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 15555, q = 15555;
    struct Node {
        int val=0;
        int l=-1;
        int r=-1;
        int move_to_y; // -5 means that it is y node already
    };
    vector<Node> nodes;
    nodes.reserve(6e7);
    auto l = [&] (int u) -> int {
        return (u == -1)?-1:nodes[u].l;
    };
    auto r = [&] (int u) -> int {
        return (u == -1)?-1:nodes[u].r;
    };
    auto gtval = [&] (int u) -> int {
        return (u == -1)?0:nodes[u].val;
    };
    auto mky = [&] (int val, int l, int r) -> int {
        nodes.push_back({val, l, r, -5});
        return nodes.size()-1;
    };
    auto mkx = [&] (int val, int l, int r, int move_to_y) -> int {
        nodes.push_back({val, l, r, move_to_y});
        return nodes.size()-1;
    };
    auto move_to_y = [&] (int u) -> int {
        return (u==-1)?-1:nodes[u].move_to_y;
    };
    auto incy = [&] (auto f, int u, int ytl, int ytr, int y, int val) -> int {
        if (ytl == ytr) {
            return mky(gtval(u) + val, -1, -1);
        } else {
            int tm = (ytl + ytr) >> 1;
            if (y <= tm) {
                int nwl = f(f, l(u), ytl, tm, y, val);
                return mky(gtval(nwl)+gtval(r(u)), nwl, r(u));
            } else {
                int nwr = f(f, r(u), tm+1, ytr, y, val);
                return mky(gtval(l(u))+gtval(nwr), l(u), nwr);
            }
        }
    };
    auto incx = [&] (auto f, int u, int xtl, int xtr, int ytl, int ytr, int x, int y, int val) -> int {
        if (xtl == xtr) {
            int goy = incy(incy, move_to_y(u), ytl, ytr, y, val);
            return mkx(gtval(goy), -1, -1, goy);
        }
        int tm = (xtl + xtr) >> 1;
        int L = l(u), R = r(u);
        if (x <= tm) {
            L = f(f, l(u), xtl, tm, ytl, ytr, x, y, val);
        } else {
            R = f(f, r(u), tm+1, xtr, ytl, ytr, x, y, val);
        }
        int goy = incy(incy, move_to_y(u), ytl, ytr, y, val);
        return mkx(gtval(L)+gtval(R), L, R, goy);
    };
    auto gt_prev_val = [&] (auto f, int u, int xtl, int xtr, int ytl, int ytr, int x) -> int {
        if (xtl == xtr) {
            if (nodes[u].move_to_y != -5) {
                u = nodes[u].move_to_y;
            }
            if (ytl == ytr) {
                return ytl;
            } else {
                int tm = (ytl + ytr) >> 1;
                if (gtval(l(u))) {
                    return f(f, l(u), xtl, xtr, ytl, tm, x);
                }
                return f(f, r(u), xtl, xtr, tm+1, ytr, x);
            }
        } else {
            int tm = (xtl + xtr) >> 1;
            if (x <= tm) {
                return f(f, l(u), xtl, tm, ytl, ytr, x);
            } else {
                return f(f, r(u), tm+1, xtr, ytl, ytr, x);
            }
        }
    };
    auto gt = [&] (auto f, int u, int xtl, int xtr, int ytl, int ytr, int xl, int xr, int yl, int yr) -> int {
        if (u == -1) {
            return 0ll;
        }
        if (xtl == xl && xtr == xr) {
            if (nodes[u].move_to_y != -5) {
                u = nodes[u].move_to_y;
            }
            if (ytl == yl && ytr == yr) {
                return gtval(u);
            } else {
                int tm = (ytl + ytr) >> 1;
                int ret = 0;
                if (yl <= tm) {
                    ret += f(f, l(u), xtl, xtr, ytl, tm, xl, xr, yl, min(yr, tm));
                }
                if (yr >= tm+1) {
                    ret += f(f, r(u), xtl, xtr, tm+1, ytr, xl, xr, max(yl, tm+1), yr);
                }
                return ret;
            }
        } else {
            int tm = (xtl + xtr) >> 1;
            int ret = 0;
            if (xl <= tm) {
                ret += f(f, l(u), xtl, tm, ytl, ytr, xl, min(xr, tm), yl, yr);
            }
            if (xr >= tm+1) {
                ret += f(f, r(u), tm+1, xtr, ytl, ytr, max(xl, tm+1), xr, yl, yr);
            }
            return ret;
        }
    };
    vector<int> roots(q+1, -1);
    for (int i = 1; i <= n; i += 1) {
        roots[0] = incx(incx, roots[0], 1, n, 0, min(n, 100), i, i%(min(n, 100)+1), 1);
    }
    uniform_int_distribution<int> I(1, n);
    uniform_int_distribution<int> TP(1, 2);
    uniform_int_distribution<int> VAL(0, min(n, 100));
    vector<int> d(q+1);
    mt19937 mt(time(0));
//    int ops = 1'0000'0000;
    vector<vector<int>> up(20, vector<int>(q+1));
    auto LCA = [&] (int u, int v) -> int {
        if (d[u] < d[v]) {
            swap(u, v);
        }
        int diff = d[u] - d[v];
        for (int i = 0; i < 20; i += 1) {
            if (diff&(1<<i)) {
                u = up[i][u];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 19; i >= 0; i -= 1) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    };
    auto dist = [&] (int u, int v) -> int {
        int lca = LCA(u, v);
        return abs(d[u]-d[lca])+abs(d[v]-d[lca]);
    };
    ofstream testout("antidfs.txt");
    testout << n << " " << q << "\n";
    set<int> shit;
    for (int i = 1; i <= q; i += 1) {
        int tp = TP(mt);
        int from = -1;
        int bestdist = -1;
        uniform_int_distribution<int> FROM(0, i-1);
        for (int j = 0; j < 10; j += 1) {
            int x = FROM(mt);
            if (dist(x, i-1) > bestdist) {
                from = x;
                bestdist = dist(x, i-1);
            }
        }
        d[i] = d[from]+1;
        up[0][i] = from;
        for (int j = 1; j < 20; j += 1) {
            up[j][i] = up[j-1][up[j-1][i]];
        }
//        cout << from << " " << i << "\n";
        roots[i] = roots[from];
        testout << tp << " " << from << " ";
        if (tp == 1) {
            int idx=I(mt), val=VAL(mt);
            shit.insert(idx);
            int prev_val = gt_prev_val(gt_prev_val, roots[i], 1, n, 0, min(n, 100), idx);
            roots[i] = incx(incx, roots[i], 1, n, 0, min(n, 100), idx, prev_val, -1);
            roots[i] = incx(incx, roots[i], 1, n, 0, min(n, 100), idx, val, 1);
            testout << idx << " " << val << "\n";
        }
        if (tp == 2) {
            int valL=VAL(mt), valR=VAL(mt);
            if (!(valL <= valR)) {
                swap(valL, valR);
            }
            int ops = 0;
            int iL = n, iR = 1;
            while (ops < 5 || !(iL <= iR)) {
                iL = min(iL, I(mt));
                iR = max(iR, I(mt));
                ops += 1;
            }
            testout << iL << " " << iR << " " << valL << " " << valR << "\n";
            int ans = gt(gt, roots[i], 1, n, 0, min(n, 100), iL, iR, valL, valR);
            cout << ans << "\n";
        }
    }
    cout << shit.size() << "!!\n";
}
