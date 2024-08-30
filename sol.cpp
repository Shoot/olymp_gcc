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
uniform_int_distribution<ll> distrib(1, 5);
constexpr ll N = (ll)(2005);
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
void computeLIS(ll arr[], ll output[]) {
    vector<ll> lis;
    for (int i = 0; i < n; ++i) {
        auto it = std::lower_bound(lis.begin(), lis.end(), arr[i]);
        if (it == lis.end()) {
            lis.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
        output[i] = lis.size();
    }
}
ll count (const ll a[]) {
    ll tot = 1;
    fo(i, 1, n) {
        if (a[i] > a[i-1]) {
            tot += 1;
        }
    }
    return tot;
}
void solve () {
//    cin >> n;
    n = 5;
    ll a[n];
    fo(i, 0, n) {
        a[i] = distrib(rng);
        cout << a[i] << ' ';
//        cin >> a[i];
    }
     cout << endl;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    vector<ll> pref (n, 1);
    vector<ll> suff (n, 1);
    fo(i, 1, n) {
        if (a[i] > a[i-1]) {
            pref[i] = pref[i-1] + 1;
        } else {
            pref[i] = pref[i-1];
        }
    }
    roff(i, n-2, 0) {
        if (a[i] < a[i+1]) {
            suff[i] = suff[i-1] + 1;
        } else {
            suff[i] = suff[i-1];
        }
    }
    ll maxi = pref[n-1];
    if (a[0] >= a[1]) maxi = pref[n-1]+1;
    if (a[n-1] <= a[n-2]) maxi = pref[n-1]+1;
    fo(i, 0, n-2) {
        if (a[i+2] - a[i] > 1) {
            maxi = max(maxi, pref[i]+suff[i+2]+1);
        }
    }
    cout << maxi << endl;
    ll ogmaxi = 0;
    fo(i, 0, n) {
        ll og = a[i];
        forr(shit, -1000, 1000) {
            a[i] = shit;
            ogmaxi = max(ogmaxi, count(a));
        }
        a[i] = og;
    }
    cout << ogmaxi << endl;
    if (maxi != ogmaxi) assert(false);
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
    ll tt = 10000;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}