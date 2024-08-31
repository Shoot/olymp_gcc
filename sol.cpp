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
uniform_int_distribution<ll> distrib(1, 10);
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
ll x;
void solve () {
    cin >> n >> x;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    ll b[n]; fo(i, 0, n) cin >> b[i];
    ll b_pref[n];
    b_pref[0] = 0;
    forr(i, 1, n) b_pref[i] = b_pref[i-1]+b[i-1];
    stack<ll> stck;
    ll nxt[n];
    roff(i, n-1, 0) {
        while(!stck.empty() && a[stck.top()] >= a[i]) {
            stck.pop();
        }
        if (!stck.empty()) {
            nxt[i] = stck.top()-1;
        } else {
            nxt[i] = n - 1;
        }
        stck.push(i);
    }
    clog << "array \"nxt min decrease wont be until\": " << endl;
    fo(i, 0, n) {
        clog << nxt[i] << ' ';
    }
    clog << endl;
    ll tot = 0;
    fo(i, 0, n) {
        ll this_one = 0;
        ll vozr_end_by_ind = i-1;
        while (vozr_end_by_ind != n-1) {
            clog << "new vozr_end_by_ind: " << vozr_end_by_ind << endl;
            ll minim = a[vozr_end_by_ind+1];
            ll l = vozr_end_by_ind+1, r = nxt[vozr_end_by_ind+1];

            ll good = -666;
            while (l <= r) {
                ll mid = (l+r) >> 1;
                if (b_pref[mid+1]-b_pref[i]+minim <= x) {
                    l = mid + 1;
                    good = mid;
                } else {
                    r = mid-1;
                }
            }
            if (good != -666) {
                this_one += good-vozr_end_by_ind;
                clog << "contrib: " << good-vozr_end_by_ind << endl;
                clog << "(good: " << good << ")" << endl;
            }
            vozr_end_by_ind = nxt[vozr_end_by_ind+1];
        }
        clog << i << " contributes " << this_one << endl;
        tot += this_one;
    }
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
//    cin >> tt;
    while (tt--) solve();
    return 0;
}