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
struct shit {
    ll opens=0, closes=0, i=0;
};
void solve () {
    ll n; cin >> n;
    vector<shit> a(n);
    ll i=0;
    string test[n+1];
    for(shit & x: a) {
        i += 1;
        cin >> test[i];
        ll this_closes=0;
        ll this_opens=0;
        for (char j: test[i]) {
            if (j == ')' && this_opens == 0) {
                this_closes += 1;
                continue;
            }
            if (j == ')') {
                this_opens -= 1;
                continue;
            }
            if (j == '(') {
                this_opens += 1;
            }
        }
        x.opens = this_opens;
        x.closes = this_closes;
        x.i = i;
    }
    sort(all(a), [] (shit a, shit b) {
        if (a.opens == 0 && b.opens != 0) return false;
        if (b.opens == 0 && a.opens != 0) return true;
        if (a.closes == b.closes) return a.opens > b.opens;
        return a.closes < b.closes;
    });
    ll curr = 0;
    for(shit & x: a) {
        clog << x.opens << " " << x.closes << " (" << x.i << ")" << endl;
        curr += x.closes;
        if (curr > 0) {
            cout << -1 << endl;
            return;
        }
        curr -= x.opens;
    }
    if (curr != 0) {
        cout << -1 << endl;
        return;
    }
    ll curr_test = 0;
    for(shit & x: a) {
        cout << x.i << " ";
        for (char j: test[x.i]) {
            curr_test += (j == '(');
            curr_test -= (j == ')');
            assert(curr_test >= 0);
        }
    }
    cout << endl;
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