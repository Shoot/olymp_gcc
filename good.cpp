#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    int g1, g2;
    cin >> g1 >> g2;
    struct Node {
        int val=0;
        int l=-1;
        int r=-1;
        int move_to_y; // -5 means that it is y node already
    };
    vector<Node> nodes;
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
    auto gt_prev_val = [&] (auto f, int ux, int uy, int xtl, int xtr, int ytl, int ytr, int x) -> int {
        if (xtl == xtr) {
            if (nodes[uy].move_to_y != -5) {
                uy = nodes[uy].move_to_y;
            }
            if (ytl == ytr) {
                return ytl;
            } else {
                int tm = (ytl + ytr) >> 1;
                if (gtval(l(uy))) {
                    return f(f, ux, l(uy), xtl, xtr, ytl, tm, x);
                }
                return f(f, ux, r(uy), xtl, xtr, tm+1, ytr, x);
            }
        } else {
            int tm = (xtl + xtr) >> 1;
            if (x <= tm) {
                return f(f, l(ux), l(ux), xtl, tm, ytl, ytr, x);
            } else {
                return f(f, r(ux), r(ux), tm+1, xtr, ytl, ytr, x);
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
        roots[0] = incx(incx, roots[0], 1, n, -1e9, 1e9, i, 0, 1);
    }
    int ra = 0;
    auto gen = [&] () -> int {
        (ra = g1*ra+g2) %= n;
        return ra;
    };
    for (int i = 1; i <= q; i += 1) {
        int tp, from;
        cin >> tp >> from;
        roots[i] = roots[from];
        if (tp == 1) {
            int idx, val;
            cin >> idx >> val;
            int prev_val = gt_prev_val(gt_prev_val, roots[i], roots[i], 1, n, -1e9, 1e9, idx);
            roots[i] = incx(incx, roots[i], 1, n, -1e9, 1e9, idx, prev_val, -1);
            roots[i] = incx(incx, roots[i], 1, n, -1e9, 1e9, idx, val, 1);
        }
        if (tp == 2) {
            int valL, valR;
            cin >> valL >> valR;
            int iL = gen()+1;
            int iR = gen()+1;
            if (!(iL <= iR)) {
                swap(iL, iR);
            }
            g1 += gt(gt, roots[i], 1, n, -1e9, 1e9, iL, iR, valL, valR);
            if (g1 >= n) {
                g1 -= n;
            }
        }
    }
    cout << g1 << "\n";
}
