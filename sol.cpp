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
void solve () {
    ll n;
    cin >> n;
//    n = 3;
    ll a[n];
    fo(i, 0, n) {
//        a[i] = distrib(rng);
//        cout << a[i] << ' ';
        cin >> a[i];
    }
//    cout << endl;
//    ll perm[n];
//    fo(i, 0, n) {
//        perm[i] = i;
//    }
//    ll perm_ind_by_val[n];
//    ll maxi = 0;
//    vector<vector<ll>> bests;
//    while (next_permutation(perm, perm+n)) {
//        fo(i, 0, n) {
//            perm_ind_by_val[perm[i]] = i;
//        }
//        ll tot = 0;
//        fo(i, 0, n) {
//            tot += a[i]*(abs(i-perm_ind_by_val[i]));
//        }
//        if (tot > maxi) {
//            maxi = tot;
//            bests.clear();
//        }
//        if (tot >= maxi) {
//            bests.emplace_back();
//            bests[bests.size()-1].resize(n);
//            fo(i, 0, n) {
//                bests[bests.size()-1][i] = a[perm[i]];
//            }
//        }
//    }
//    cout << "(OG) BEST SCORE: " << maxi << endl;
//    cout << "NUMBER OF PERMS: " << bests.size() << endl;
//    for(const auto& best_perm: bests) {
//        for(ll x : best_perm) {
//            cout << x << ' ';
//        }
//        cout << endl;
//    }

    vector<pair<ll, ll>> x (n);
    fo(i, 0, n) {
        x[i].first = a[i];
        x[i].second = i;
    }
    ll dp[2001][2001];
    forr(i, 0, 2000) {
        forr(j, 0, 2000) {
            dp[i][j] = 0;
        }
    }
    sort(all(x), greater<>());
    forr(hod, 1, n) {
        forr(l, 0, hod) {
            ll r = hod-l;
            if (l != 0) {
                dp[l][r] = max(dp[l][r],
                               dp[l-1][r]+abs(x[hod-1].second-(l-1))*x[hod-1].first
                               );
//                clog << "1.[" << l << "]" << "[" << r << "] = " << dp[l][r] << endl;
            }
            if (r != 0) {
                dp[l][r] = max(dp[l][r],
                               dp[l][r-1]+abs(x[hod-1].second-(n-1-(r-1)))*x[hod-1].first
                               );
//                clog << "2.[" << l << "]" << "[" << r << "] = " << dp[l][r] << endl;
            }
        }
    }
    ll mymaxi = 0;
    forr(l, 0, n) {
        ll r = n-l;
        mymaxi = max(mymaxi, dp[l][r]);
    }
    cout << mymaxi << endl;
//    ll res[n];
//    ll leftmost = 0;
//    ll rightmost = n-1;
//    ll mytot = 0;
//    fo(i, 0, n) {
//        clog << x[i].first << " @ " << x[i].second << endl;
//        if (abs(x[i].second-leftmost) > abs(x[i].second-rightmost)) {
//            mytot += abs(x[i].second-leftmost)*x[i].first;
//            res[leftmost] = x[i].first;
//            clog << "Left: " << leftmost << endl;
//            leftmost+=1;
//        } else {
//            mytot += abs(x[i].second-rightmost)*x[i].first;
//            res[rightmost] = x[i].first;
//            clog << "Right: " << rightmost << endl;
//            rightmost-=1;
//        }
//    }
//    cout << "my perm: ";
//    fo(i, 0, n) {
//        cout << res[i] << ' ';
//    }
//    cout << endl;
//    cout << "my score: " << mytot << endl;
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