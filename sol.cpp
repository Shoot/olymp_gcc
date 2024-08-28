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
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2e5+1);
//constexpr ll MOD = 998244353;
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
    ll x, t;
};
void solve () {
    ll n; cin >> n;
    map<ll, pair<ll, ll>> shit;
    fo(i, 0, n) {
        ll x, t; cin >> x >> t;
        if (!shit.contains(t)) {
            shit[t].first = x;
            shit[t].second = x;
        } else {
            shit[t].first = min(shit[t].first, x);
            shit[t].second = max(shit[t].second, x);
        }
    }
    shit[0] = make_pair(0, 0);
    shit[LLONG_MAX] = make_pair(0, 0);
    vector<pair<ll, ll>> yea (shit.size());
    ll h = 0;
    for (auto [i, j] : shit) {
        yea[h] = j;
        h += 1;
    }
    ll ltot = 0;
    ll rtot = 0;
    roff(i, yea.size()-2, 0) {
        ll ltot_n = (yea[i].second-yea[i].first)+min(abs(yea[i+1].second-yea[i].second)+rtot,
                                                abs(yea[i+1].first-yea[i].second)+ltot);
        ll rtot_n = rtot = (yea[i].second-yea[i].first)+min(abs(yea[i+1].second-yea[i].first)+rtot,
                                                abs(yea[i+1].first-yea[i].first)+ltot);
        ltot = ltot_n;
        rtot = rtot_n;
        clog << ltot << " " << rtot << endl;
    }
    assert(ltot == rtot);
    cout << ltot << endl;
//    ll x=0;
//    ll tot = 0;
//    for (const auto& v : a) {
//        if (abs(x-v[0].x) > abs(x-v[(ll)v.size()-1].x)) {
//            roff(i, v.size()-1, 0) {
//                tot += abs(v[i].x-x);
//                x = v[i].x;
//            }
//        } else {
//            forr(i, 0, v.size()-1) {
//                tot += abs(v[i].x-x);
//                x = v[i].x;
//            }
//        }
//    }
//    cout << tot+x << endl;
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
    while (tt--) solve();
    return 0;
}