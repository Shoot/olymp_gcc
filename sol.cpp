#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> vals(n);
    vector<int> sums(n);
    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;
        int su = 0;
        for (const auto &y : to_string(x)) {
            su += y - '0';
        }
        vals[i] = x;
        sums[i] = su;
    }
    vector<int> g(n);
    iota(g.begin(), g.end(), 0LL);
    auto can = [&] (double x) -> bool {
        sort(g.begin(), g.end(), [&] (int a, int b) {
            return double(vals[a]) - x*sums[a] > double(vals[b]) - x*sums[b];
        });
        int V = 0, S = 0;
        for (int i = 0; i < k; i += 1) {
            V += vals[g[i]];
            S += sums[g[i]];
        }
        return double(V)/S >= x;
    };
    double l = 0, r = accumulate(vals.begin(), vals.end(), 0.);
    while (r - l > 1e-8) {
        double mid = (l + r) / 2;
        if (can(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(6) << l << "\n";
}