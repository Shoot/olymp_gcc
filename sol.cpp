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
uniform_int_distribution<ll> distrib(1ll, 1000000000000000000ll);
constexpr ll N = (ll)(1e15);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
ll powm(ll a, ll b, ll MOD){
    ll d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll p = 200001;
ll revp7 = powm(p, MOD7-2, MOD7);
ll revp99 = powm(p, MOD99-2, MOD99);
vector<ll> pp(200001, 1);
vector<ll> pp_rev7(200001, 1);
vector<ll> pp_rev99(200001, 1);
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
    fo(i, 1, 200001) {
        pp[i] = (pp[i-1]*p)%MOD7;
    }
    fo(i, 1, 200001) {
        pp_rev7[i] = (pp_rev7[i-1]*revp7)%MOD7;
    }
    ll n; cin >> n;
    vector<ll> a(n);
    fo(i, 0, n) {
        cin >> a[i];
    }
    clog << "got that" << endl;
    ll m; cin >> m;
    vector<ll> b(m);
    vector<ll> rb(m+1, 0);
    fo(i, 0, m) {
        cin >> b[i];
        rb[i+1] = (rb[i]+b[i]*pp[i])%MOD7;
    }
    ll k; cin >> k;
    vector<ll> c(k);
    vector<ll> rc(k+1, 0);
    fo(i, 0, k) {
        cin >> c[i];
        rc[i+1] = (rc[i]+c[i]*pp[i])%MOD7;
    }
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<ll> b_st;
        unordered_set<ll> c_st;
        fo(i, 0, m+1-mid) {
            b_st.insert(((rb[i+mid]-rb[i])*pp_rev7[i])%MOD7);
        }
        fo(i, 0, k+1-mid) {
            c_st.insert(((rc[i+mid]-rc[i])*pp_rev7[i])%MOD7);
        }
        bool intersected = false;
        for (const ll& element : b_st) {
            if (c_st.find(element) != c_st.end()) {
                intersected = true;
                break;
            }
        }
        if (intersected) {
            good = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    if (good > 0) {
        cout << m-good+k-good << endl;
    } else {
        clog << "lets see" << endl;
        ll dp[200001];
        forr(i, 1, 200000) {
            dp[i] = INT_MAX;
        }
        fo(i, 0, m) {
            dp[b[i]] = m-1;
        }
//        ll start = -1;
//        fo(i, 0, n) {
//            if (dp[a[i]] == m-1) {
//                start = i;
//                break;
//            }
//        }
//        assert(start != -1);
//        roff(i, start-1, 0) {
//            dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
//        }
//        forr(i, start+1, n-1) {
//            dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
//        }
        while(true) {
            forr(i, 1, n-1) {
                dp[a[i]] = min(dp[a[i]], dp[a[i-1]]+2);
            }
            roff(i, n-2, 0) {
                dp[a[i]] = min(dp[a[i]], dp[a[i+1]]+2);
            }
            bool enough = true;
            forr(i, 1, n-1) {
                if (dp[a[i]] != min(dp[a[i]], dp[a[i-1]]+2)) {
                    enough = false;
                }
            }
            roff(i, n-2, 0) {
                if (dp[a[i]] != min(dp[a[i]], dp[a[i+1]]+2)) {
                    enough = false;
                }
            }
            if (enough) break;
        }

        fo(i, 0, k) {
            assert(dp[b[i]] == m-1);
        }
        fo(i, 0, n) {
            clog << dp[a[i]] << ' ';
        }
        clog << endl;
        ll res = INT_MAX;
        fo(i, 0, k) {
            res = min(res, dp[c[i]]+k-1);
        }
        cout << res << endl;
    }
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
        //clog.tie(nullptr);
    }
    ll tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}