#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x < fi; x++)
#define forr(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x <= fi; x++)
#define rrof(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define roff(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x >= fi; x--)
#define of(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define ro(x, temp_set_for_mex, fi) for(ll x = temp_set_for_mex; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2005);
constexpr ll MOD = 998244353;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
struct Point {
    ll x, y;
    Point() {
        x = 0;
        y = 0;
    }
};
struct Seg {
    Point a, b;
    Seg(Point a, Point b) {
        this->a = a;
        this->b = b;
    }
    Seg() = default;
};
void solve () {
    ll n; cin >> n;
    vector<Point> ps(n);
    vector<Seg> ss(n);
    fo(i, 0, n) {
        cin >> ps[i].x >> ps[i].y;
    }
    fo(i, 0, n) {
        ss[i].a = ps[i];
        ss[i].b = ps[(i+1)%n];
    }
    ll mini = LLONG_MAX;
    ll mini_i = -1;
    fo(i, 0, n) {
        if (ss[i].a.x < mini) {
            mini_i = i;
            mini = ss[i].a.x;
        }
    }
    rotate(ss.begin(), ss.begin()+mini_i, ss.end());
    for (Seg _: ss) {
        clog << _.a.x << "," << _.a.y << " -> " << _.b.x << "," << _.b.y << endl;
    }
    ll mnozh = 0;
    double tg_first = (double)(ss[0].b.y-ss[0].a.y)/(double)(ss[0].b.x-ss[0].a.x);
    double tg_last = (double)(ss[n-1].a.y-ss[n-1].b.y)/(double)(ss[n-1].a.x-ss[n-1].b.x);
    double diff = tg_first-tg_last;
    clog << "Tangs: " << tg_first  << " " <<  tg_last << endl;
    assert(abs(diff) > 1e-8);
    if (diff > 0) {
        mnozh = 1;
    } else {
        mnozh = -1;
    }
    assert(mnozh != 0);
    /*
    0,0 -> 1,2
    1,2 -> 2,2
    2,2 -> 0,0
    Assertion failed: (false), function solve, file sol.cpp, line 78.
     */
    clog << "mnozh = " << mnozh << (mnozh == 1 ? " (dx > 0 -> krisha)" : " (dx < 0 -> krisha)") << endl;
    ll tot = 0;
    vector<vector<ll>> simplified;
    vector<pair<bool, bool>> predsledy;
    fo(i, 0, n) {
        clog << ss[i].a.x << "," << ss[i].a.y << " -> " << ss[i].b.x << "," << ss[i].b.y << endl;
        ll preddx;
//        ll preddy;
        if (i == 0) preddx = ss[n-1].b.x-ss[n-1].a.x;
        else preddx = ss[i-1].b.x-ss[i-1].a.x;
//        if (i == 0) preddy = ss[n-1].b.y-ss[n-1].a.y;
//        else preddy = ss[i-1].b.y-ss[i-1].a.y;
        ll dy = ss[i].b.y-ss[i].a.y;
        ll dx = ss[i].b.x-ss[i].a.x;
        if (mnozh*dx < 0) {
            clog << "dno" << endl;
            if (simplified.empty() || mnozh*preddx >= 0) {
                predsledy.emplace_back((i == 0 ? ss[n-1].a.y>ss[i].a.y : ss[i-1].a.y>ss[i].a.y), 0);
                simplified.emplace_back();
                clog << "+" << endl;
            }
            if (dy != 0) {
                simplified[simplified.size()-1].push_back(dy);
            }
            predsledy[predsledy.size()-1].second = (i == n-1 ? ss[0].b.y>ss[i].b.y : ss[i+1].b.y>ss[i].b.y);
        } else {
            clog << "krisha/vert" << endl;
        }
    }
    ll predsledy_i = 0;
    for (const auto& dno: simplified) {
        for (auto edge: dno) {
            clog << edge << "; ";
        }
        clog << "l: " << predsledy[predsledy_i].first << ", r: " << predsledy[predsledy_i].second << " ";
        if (dno.empty()) {
            if (predsledy[predsledy_i].first && predsledy[predsledy_i].second) {
                tot += 1;
                clog << " --> 1" << endl;
            } else {
                clog << " --> 0" << endl;
            }
            continue;
        }
        clog << endl;
        if (predsledy[predsledy_i].first) {
            tot += dno[0] > 0;
        }
        if (predsledy[predsledy_i].second) {
            tot += dno[dno.size()-1] < 0;
        }
        fo(i, 0, dno.size()-1) {
            if ((dno[i] < 0) && (dno[i+1] > 0)) {
                tot += 1;
            }
        }
        predsledy_i += 1;
    }
//    assert(tot != 0);
    cout << max(1ll, tot) << endl;
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cerr.tie(nullptr);
        clog.tie(nullptr);
    }
    ll tt = 1;
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}