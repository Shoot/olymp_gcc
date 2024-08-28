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
int count_unique_strings(const string& S) {
    int n = (int)S.size();
    unordered_set<string> unique_strings;
    unique_strings.insert(S);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            string prefix = S.substr(0, i);
            string to_reverse = S.substr(i, j - i + 1);
            string suffix = S.substr(j + 1);
            reverse(to_reverse.begin(), to_reverse.end());
            string new_string = prefix;
            new_string += to_reverse + suffix;
            unique_strings.insert(new_string);
        }
    }

    return (int)unique_strings.size();
}
void solve () {
    string s; cin >> s;
    ll n = (ll)s.size();
    ll kol[1000];
    memset(kol, 0, sizeof(kol));
    set<char> st;
    for (char j : s) {
        kol[j-'a'] += 1;
        st.insert(j);
    }
    ll res = n*(n-1)/2+1;
    fo(i, 0, 1000) {
        res -= kol[i]*(kol[i]-1)/2;
    }
    if (st.size() == 1) {
        assert(n > 10000 || res == 1);
        cout << 1 << endl;
//        clog << res << endl;
        return;
    }
//        assert(count_unique_strings(s) == res+1);
    cout << res << endl;
//    cout << count_unique_strings(s) << endl;
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