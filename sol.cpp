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
constexpr ll N = (ll)(2e4);
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
    for (Seg _: ss) {
        clog << _.a.x << "," << _.a.y << " -> " << _.b.x << "," << _.b.y << endl;
    }
    clog << endl;
    rotate(ss.begin(), ss.begin()+mini_i, ss.end());
    for (Seg _: ss) {
        clog << _.a.x << "," << _.a.y << " -> " << _.b.x << "," << _.b.y << endl;
    }
    ll mnozh = 0;
    double tg_first = (double)(ss[0].b.y-ss[0].a.y)/(double)(ss[0].b.x-ss[0].a.x);
    double tg_last = (double)(ss[n-1].a.y-ss[n-1].b.y)/(double)(ss[n-1].a.x-ss[n-1].b.x);
    double diff = (double)(ss[0].b.y-ss[0].a.y)/(double)(ss[0].b.x-ss[0].a.y) - (double)(ss[n-1].a.y-ss[n-1].b.y)/(double)(ss[n-1].a.x-ss[n-1].b.x);
    assert(abs(diff) > 1e-8);
    if (diff > 0) {
        mnozh = 1;
    } else {
        mnozh = -1;
    }
    clog << "Tangs: " << tg_first  << " " <<  tg_last << endl;
    assert(mnozh != 0);
    /*
    0,0 -> 1,2
    1,2 -> 2,2
    2,2 -> 0,0
    Assertion failed: (false), function solve, file sol.cpp, line 78.
     */
    clog << "mnozh = " << mnozh << (mnozh == 1 ? " (dx > 0 -> krisha)" : " (dx < 0 -> krisha)") << endl;
    assert(mnozh);
    ll tot = 0;
    fo(i, 0, n) {
        clog << ss[i].a.x << "," << ss[i].a.y << " -> " << ss[i].b.x << "," << ss[i].b.y << endl;
        ll dx = ss[i].b.x-ss[i].a.x;
        ll preddx, preddy;
        if (i == 0) preddx = ss[n-1].b.x-ss[n-1].a.x;
        else preddx = ss[i-1].b.x-ss[i-1].a.x;
        ll dy = ss[i].b.y-ss[i].a.y;
        if (i == 0) preddy = ss[n-1].b.y-ss[n-1].a.y;
        else preddy = ss[i-1].b.y-ss[i-1].a.y;
        if (mnozh*dx > 0) {
            clog << "krisha" << endl;
            if (mnozh*preddx < 0 && preddy <= 0 && dy > 0) {
                clog << "adding 1 specialkrisha" << endl;
                tot += 1;
            }
        } else if (mnozh*dx < 0) {
            clog << "dno" << endl;
            if (mnozh*preddx < 0) {
                clog << "pred = dno" << endl;
                if (preddy <= 0 && dy > 0) {
                    clog << "adding 1" << endl;
                    tot += 1;
                }
            }
        } else {
            clog << "vert" << endl;
            if (mnozh*preddx < 0 && preddy <= 0 && dy > 0) {
                clog << "adding 1 specialvert" << endl;
                tot += 1;
            }
            continue;
        }
    }
    assert(tot != 0);
    cout << tot << endl;
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