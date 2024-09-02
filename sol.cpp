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
ll replaces[200001];
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
    ll n; cin >> n;
    vector<ll> a(n);
    fo(i, 0, n) {
        cin >> a[i];
    }
    ll m; cin >> m;
    vector<ll> b(m);
    vector<ll> rb(m+1, 0);
    fo(i, 0, m) {
        cin >> b[i];
        rb[i+1] = replaces[b[i]]^rb[i];
    }
    ll k; cin >> k;
    vector<ll> c(k);
    vector<ll> rc(k+1, 0);
    fo(i, 0, k) {
        cin >> c[i];
        rc[i+1] = replaces[c[i]]^rc[i];
    }
    ll l=1, r=min(m, k);
    ll good = 0;
    while (l <= r) {
        ll mid = (l+r) >> 1;
        unordered_set<ll> b_st;
        unordered_set<ll> c_st;
        fo(i, 0, m+1-mid) {
            b_st.insert(rb[i+mid]-rb[i]);
        }
        fo(i, 0, k+1-mid) {
            c_st.insert(rc[i+mid]-rc[i]);
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
        unordered_set<ll> c_st;
        fo(i, 0, k+1-good) {
            c_st.insert(rc[i+good]-rc[i]);
        }
        fo(i, 0, m+1-good) {
            if (c_st.find(rb[i+good]-rb[i]) != c_st.end()) {
                forr(j, i, i+good-1) {
                    clog << b[j] << ' ';
                }
                clog << endl;
                break;
            }
        }
        cout << m-good+k-good << endl;
    } else {
        clog << "lets see" << endl;
    }
}
int32_t main (int32_t argc, char* argv[]) {
    forr(i, 1, 200000) {
        replaces[i] = distrib(rng);
    }
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