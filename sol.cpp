#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;
const long long INF = 1e18;
struct line {
    long long k, b;
    long long operator()(long long x) {
        return k * x + b;
    }
};
long long cross(line a, line b) {
    return double(a.b - b.b) / (b.k - a.k);
}
vector<pair<long long, line>> lines(1e6);
struct CHT {
    long long idx = 0;
    long long nxt = 0;
    void insert(line l) {
        while (nxt && cross(l, lines[nxt-1].second) <= lines[nxt-1].first) nxt -= 1;
        lines[nxt++] = {lines.empty() ? -INF : cross(l, lines[nxt-1].second), l};
        idx = min(idx, (long long)(nxt - 1));
    }
    long long get(long long x) {
        for (;;++idx) {
            if (idx + 1 == nxt || lines[idx + 1].first > x) return lines[idx].second(x);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long n; cin >> n;
    long long cats_n; cin >> cats_n;
    long long feeders; cin >> feeders;
    struct cat {
        long long where;
        long long t;
    };
    vector<long long> d(n);
    for (long long i = 1; i < n; i += 1) {
        d[i] = d[i-1];
        long long x; cin >> x;
        d[i] += x;
    }
    vector<cat> a(cats_n);
    vector<long long> val(cats_n);
    for (long long i = 0; i < cats_n; i += 1) {
        cin >> a[i].where >> a[i].t;
        a[i].where -= 1;
        val[i] = a[i].t-d[a[i].where];
    }
    sort(val.begin(), val.end());
    vector<long long> dp(cats_n+1, INF);
    vector<long long> ndp(cats_n+1, INF);
    for (long long k = 1; k <= feeders; k += 1) {
        CHT c;
        for (long long i = 1; i <= cats_n; i += 1) {
            long long cur = val[i-1] * i;
            if (i != 1) cur = min(cur, c.get(val[i-1]) + val[i-1] * i);
            ndp[i] = cur;
            c.insert({-i, dp[i]});
        }
        swap(dp, ndp);
    }

    long long ans = dp.back() - accumulate(val.begin(), val.end(), 0ll);
    cout << ans << endl;
    return 0;
}