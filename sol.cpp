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
void solve () {
    ll n; cin >> n;
    ll a[n];
    fo(i, 0, n) {
        cin >> a[i];
    }
    ll perm[n];
    fo(i, 0, n) {
        perm[i] = i;
    }
    ll perm_ind_by_val[n];
    ll maxi = 0;
    vector<vector<ll>> bests;
    while (next_permutation(perm, perm+n)) {
        fo(i, 0, n) {
            perm_ind_by_val[perm[i]] = i;
        }
        ll tot = 0;
        fo(i, 0, n) {
            tot += a[i]*(abs(i-perm_ind_by_val[i]));
        }
        if (tot > maxi) {
            maxi = tot;
            bests.clear();
        }
        if (tot >= maxi) {
            bests.emplace_back();
            bests[bests.size()-1].resize(n);
            fo(i, 0, n) {
                bests[bests.size()-1][i] = a[perm[i]];
            }
        }
    }
    cout << "(OG) BEST SCORE: " << maxi << endl;
    cout << "NUMBER OF PERMS: " << bests.size() << endl;

    vector<vector<ll>> dp(n+1, vector<ll>(n, 0)); // dp[i][j] = max sum considering first i elements with j as the current index

    fo(i, 1, n+1) {
        fo(j, 0, n) {
            dp[i][j] = max(dp[i][j], dp[i-1][j] + a[i-1] * abs(i-1 - j));
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + a[i-1] * abs(i-1 - (j-1)));
            }
        }
    }

    ll result = 0;
    fo(j, 0, n) {
        result = max(result, dp[n][j]);
    }

    cout << "BEST SCORE: " << result << endl;
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