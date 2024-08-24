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
const ll N = 3e5 + 1;
void copy_this () {
    ll n; cin >> n;
//    ll n, k; cin >> n >> k;
    ll a[n]; fo(i, 0, n) cin >> a[i];
//    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
bool dozhivet(ll kto, ll dokogo, ll k) {
    ll mod = 2*k;
    if ((kto+k)%mod <= (kto)%mod) {
        if (dokogo < (kto+k)%mod || dokogo >= (kto)%mod) return true;
        return false;
    }
    return (dokogo >= kto && (kto+k)%mod > dokogo);
}
ll removeDuplicates(ll arr[], ll n)
{
    if (!n) return n;
    ll j = 0;
    fo(i, 0, n-1){
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[n - 1];
    return j;
}
void solve() {
    ll n, k; cin >> n >> k;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    ll maxi = *max_element(a, a+n);
    ll ost[n]; fo(i, 0, n) ost[i] = a[i]%(2*k);
    sort(ost, ost+n);
    n = removeDuplicates(ost, n);
    set<ll> st;
    fo(i, 0, n) {
        if (dozhivet(ost[(i+1)%n], ost[i], k)) st.insert(ost[i]);
    }
    if (st.empty()) cout << -1 << endl;
    else {
        auto it = st.lower_bound(maxi%(2*k));
        if (it == st.end()) {
            cout << maxi-maxi%(2*k)+2*k+(*st.begin()) << endl;
        } else {
            cout << maxi-maxi%(2*k)+*it << endl;
        }

    }
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}