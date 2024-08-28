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
    ll pref[n]; fo(i, 0, n) cin >> pref[i];
    vector<ll> pref(n); fo(i, 0, n) cin >> pref[i];
}
*/
ll shit(const vector<ll>& pref) {

    return max(ans, suff[0]);
}

void solve () {
    ll n; cin >> n;
    vector<ll> pref(n); fo(i, 0, n) cin >> pref[i];
    vector<int> pref(n, 1);
    vector<int> suff(n+1, 1);
    int ans = 1;
    fo(i, 1, n) {
        if (pref[i] > pref[i - 1]) {
            pref[i] = pref[i - 1] + 1;
            ans = max(ans, pref[i]);
        }
    }
    if (ans != n)
        ++ans;
    suff[n] = 0;
    roff (i, n-1, 1) {
        if (pref[i - 1] < pref[i])
            suff[i] = suff[i + 1] + 1;
    }
    roff (i, n-2, 1) {
        if (pref[i + 1] - pref[i - 1] > 1) ans = max(ans, pref[i - 1] + suff[i + 1] + 1);
    }
    assert(shit(pref) == max(ans, suff[0]));
    cout << shit(pref) << endl;
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