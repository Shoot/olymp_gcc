#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll q; cin >> q;
    struct Point {
        double x;
        double y;
    };
    vector<Point> pts(q);
    for (ll i = 0; i < q; i += 1) {
        cin >> pts[i].x >> pts[i].y;
    }
    sort(pts.begin(), pts.end(), [&] (Point a, Point b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });
    auto dist = [&] (Point a, Point b) -> double {
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    };
    auto solve = [&] (auto f, ll l, ll r) -> double {
        if (r - l + 1 <= 1) {
            return INF;
        }
        ll mid = (l + r) >> 1;
        auto pt = pts[mid];
        double d = INF;
        d = min(d, f(f, l, mid));
        d = min(d, f(f, mid+1, r));
        vector<Point> t;
        for (ll i = l; i <= r; i += 1) {
            if (abs(pts[i].x-pts[mid].x) <= d) {
                t.push_back(pts[i]);
            }
        }
        sort(t.begin(), t.end(), [&] (Point a, Point b) {
            if (a.y == b.y) {
                return a.x < b.x;
            }
            return a.y < b.y;
        });
        ll n = ll(t.size());
        for (ll i = 0; i < n; i += 1) {
            for (ll j = 1; j < 9; j += 1) {
                if (i+j >= n) {
                    break;
                }
                d = min(d, dist(t[i], t[i+j]));
            }
        }
        return d;
    };
    cout << solve(solve, 0, q-1) << endl;
}

int main(int32_t argc, char* argv[]) {
    cout << fixed << setprecision(6);
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; i += 1) use_fast_io &= string(argv[i]) != "-local-no-fast-io";
    if (use_fast_io) ios::sync_with_stdio(false), cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}
