#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, st, fi) for(ll x = st; x < fi; x++)
#define forr(x, st, fi) for(ll x = st; x <= fi; x++)
#define rrof(x, st, fi) for(ll x = st; x >= fi; x--)
#define roff(x, st, fi) for(ll x = st; x >= fi; x--)
#define of(x, st, fi) for(ll x = st; x > fi; x--)
#define ro(x, st, fi) for(ll x = st; x > fi; x--)
#define yes(x) (x ? "YES" : "NO")
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
const ll N = 1e6 + 1;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
void solve() {
    ll k; cin >> k;
    string s; cin >> s;
    ll n = (ll)s.size();
    ll pref[n+1];
    pref[0] = 0;
    forr(i, 1, n) pref[i] = pref[i-1]+ s[i-1]-'0';
//    ll prefmap[N];
//    memset(prefmap, 0, sizeof(prefmap));
    map<ll, ll> prefmap;
    prefmap[0] = 1;
    ll ans = 0;
    forr(i, 1, n) {
        if (pref[i] >= k) {
            ans += prefmap[pref[i]-k];
        }
        prefmap[pref[i]] += 1;
    }
    cout << ans << endl;
}
int32_t main (int32_t argc, char* argv[]) {
//    mt19937 rng(chrono::steady_clock::now().time_since_epoch().ans());
//    uniform_int_distribution<ll> distrib(1, LLONG_MAX);
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
//    cin >> tt;
    while (tt--) solve();
    return 0;
}