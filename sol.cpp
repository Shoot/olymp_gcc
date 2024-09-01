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
uniform_int_distribution<ll> distrib(1, 11);
constexpr ll N = (ll)(1 << 3);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/

ll n;
ll x;
ll count(ll l, ll r, const ll a[], const ll b[]) {
    clog << l << " to " << r << endl;
    if (l == r) {
        if (a[l]+b[l] <= x) {
            clog << l << " to " << r << ": " << 1 << endl;
            return 1;
        } else {
            clog << l << " to " << r << ": " << 0 << endl;
            return 0;
        }
    }
    ll tot = 0;
    ll mid = (l+r) >> 1;
    vector<ll> rs(r-(mid+1)+1);
    vector<ll> rm(r-(mid+1)+1);
    vector<ll> ls(r-(mid+1)+1);
    vector<ll> lm(r-(mid+1)+1);
    ll cum = 0;
    ll mini = LLONG_MAX;
    forr(i, 0, r-(mid+1)) {
        cum += a[i+mid+1];
        rs[i] = cum;
        clog << "rs: " << (ll)(cum%10000) << endl;
        mini = min(mini, b[i+mid+1]);
        rm[i] = mini;
    }
    cum = 0;
    mini = LLONG_MAX;
    forr(i, 0, r-(mid+1)) {
        clog << i << " " << mid-i << endl;
        cum += a[mid-i];
        ls[i] = cum;
        mini = min(mini, b[mid-i]);
        lm[i] = mini;
    }
    ordered_set<ll> rs_st;
    ordered_set<ll> ls_st;
    fo(i, 0, r-(mid+1)) {
        cout << rs[i] << endl;
        cout << ls[i] << endl;
        rs_st.insert(rs[i]);
        ls_st.insert(ls[i]);
    }
    fo(i, 0, n) {
        tot += rs_st.order_of_key(-1);
//        tot += rs_st.order_of_key(x-lm[i]-ls[i]);
    }
//    fo(i, 0, n) {
//        tot += ls_st.order_of_key(x-rm[i]-rs[i]);
//    }
    clog << l << " to " << r << ": " << tot << endl;
    return tot + count(l, mid, a, b)+count(mid+1, r, a, b);
}
ll a[N];
ll b[N];
void solve () {
    cin >> n >> x;
    ll oldn = n;
    n = N;
    fo(i, 0, oldn) {
        cin >> a[i];
    }
    fo(i, 0, oldn) {
        cin >> b[i];
    }
    forr(i, oldn, N-1) {
        a[i] = INT_MAX;
    }
    forr(i, oldn, N-1) {
        b[i] = INT_MAX;
    }
    cout << count(0, N-1, a, b) << endl;
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
//    cin >> tt;
    while (tt--) solve();
    return 0;
}