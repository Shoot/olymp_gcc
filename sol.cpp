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
constexpr ll MOD = 998244353;
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
    vector<vector<ll>> sm (n+1);
    forr(i, 1, n) {
        string s;
        cin >> s;
        forr(j, i+1, s.size()) {
            if (s[j-1] == '1') {
                sm[i].push_back(j);
                sm[j].push_back(i);
            }
        }
    }
    ll maxi = 0;
    unordered_map<ll, ll> cnt;
    forr(i, 1, n){
        maxi = max(maxi, (ll)sm[i].size());
        cnt[(ll)sm[i].size()]+=1;
    }
    if (maxi > 2) {
        cout << -1 << endl;
        return;
    }
    forr(i, 1, n) {
        clog << i << ": ";
        for (ll j: sm[i]) {
            clog << j << ' ';
        }
        clog << endl;
    }
    for (auto [i, j]: cnt) {
        clog << i << " x " << j << endl;
    }
    while (cnt[1] > 0) {
        forr(i, 1, n) {
            if ((ll)sm[i].size() == 1) {
                queue<ll> q;
                q.push(i);
                while (!q.empty()) {
                    ll de = q.back(); q.pop();
                    clog << "new: " << de << endl;
                    clog << "size: " << (ll)sm[de].size() << endl;
                    if (sm[de].empty()) continue;
                    for (ll nxt: sm[de]) {
                        clog << "nxt: " << nxt << endl;
                        q.push(nxt);
                    }
                    cnt[(ll)sm[de].size()] -= 1;
                    sm[de].clear();
                }
            }
        }
    }
    for (auto [i, j]: cnt) {
        assert(j >= 0);
    }
    if (cnt[2] > 0) {
        cout << -1 << endl;
    } else {
        cout << n << endl;
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
        clog.tie(nullptr);
    }
    ll tt = 1;
//    fo(i, 0, 1) skip.insert(distrib(rng));
//    cin >> tt;
    while (tt--) solve();
    return 0;
}