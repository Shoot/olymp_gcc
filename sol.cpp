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
uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr ll N = (ll)(1e15);
constexpr ll MOD99 = 998244353;
constexpr ll MOD7 = 1e9 + 7;
ll maxi_init = 1e9;
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
    ll k; cin >> k;
    vector<pair<ll, ll>> DELETE;
    fo(ii, 0, k) {
        ll n, m; cin >> n >> m;
        vector<pair<ll, ll>> a (n+1);
        forr(i, 0, n) {
            a[i].first = maxi_init;
            a[i].second = maxi_init;
        }
        vector<vector<ll>> sm(n+1);
        fo(i, 0, m) {
            ll u, v; cin >> u >> v;
            sm[u].push_back(v);
            sm[v].push_back(u);
        }
        queue<pair<ll, ll>> q;
        q.push(make_pair(1, 0));
        while(!q.empty()) {
            auto tp = q.front();
//            clog << "got " << tp.first << " " << tp.second << endl;
            q.pop();
            if (tp.second % 2 == 0 && a[tp.first].first == maxi_init) {
                a[tp.first].first = tp.second;
//                clog << "setting " << tp.first << "[0]=" << tp.second << endl;
            } else if (tp.second % 2 == 1 && a[tp.first].second == maxi_init) {
                a[tp.first].second = tp.second;
//                clog << "setting " << tp.first << "[1]=" << tp.second << endl;
            } else {
                continue;
            }
            for (ll nxt: sm[tp.first]) {
                q.push(make_pair(nxt, tp.second+1));
            }
        }
        if (DELETE.empty()) {
            forr(i, 1, n) {
                DELETE.push_back(a[i]);
            }
        } else {
            vector<pair<ll, ll>> DELETE2;
            for(auto [i, j]: DELETE) {
                forr(iii, 1, n) {
                    DELETE2.push_back(make_pair(max(i, a[iii].first), max(j, a[iii].second)));
                }
            }
            DELETE = DELETE2;
        }
    }
    ll OG = 0;
    for(auto [i, j]: DELETE) {
        ll l = min(i, j);
        if (l != maxi_init) {
            OG += l;
        }
    }
    cout << "OG = " << OG << endl;
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