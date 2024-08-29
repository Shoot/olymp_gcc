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
ll color[2201];
ll newcomponent[2201];
void solve () {
    forr(i, 1, 200) {
        newcomponent[i] = 1;
    }
    ll n; cin >> n;
    vector<vector<ll>> sm (n+1);
    forr(i, 1, n) {
        string s;
        cin >> s;
        forr(j, i+1, n) {
            if (s[j-1] == '1') {
                sm[i].push_back(j);
                sm[j].push_back(i);
            }
        }
    }
    ll maxi = 0;
    forr(starting_point, 1, n) {
        queue<ll> comp_dfs_q;
        comp_dfs_q.push(starting_point);
        while (!comp_dfs_q.empty()) {
            ll curr = comp_dfs_q.front();
            comp_dfs_q.pop();
            if (curr <= 0 || curr > 200) {
                cout << -1;
                return;
            }
            if (sm[curr].empty() || sm[curr].size() > 200) {
                cout << -1;
                return;
            }
            newcomponent[curr] = 0;
            for (ll nxt: sm[curr]) {
                if (nxt <= 0 || nxt > 200) {
                    cout << -1;
                    return;
                }
                if (newcomponent[nxt] == 1) {
                    comp_dfs_q.push(nxt);
                }
            }
        }
        clog << "start = " << starting_point << endl;
        memset(color, 0, sizeof(color));
        queue<ll> q;
        color[starting_point] = 1;
        q.push(starting_point);
        ll color_count = 1;
        while (!q.empty()) {
            ll v = q.front();
            clog << "v = " << v << endl;
            q.pop();
            for(ll nei: sm[v]) {
                if (color[nei] == color[v]) {
                    cout << -1 << endl;
                    return;
                }
                if (color[nei] == 0) {
                    color[nei] = color[v]+1;
                    clog << nei << " = " << color[v]+1 << endl;
                    color_count = max(color_count, color[v]+1);
                    q.push(nei);
                } else if (color[nei] < color[v]) {
                    ll cycle_length = color[v]-color[nei]+1;
                    if (cycle_length % 2 == 1) {
                        cout << -1 << endl;
                        return;
                    }
                    color_count -= cycle_length/2-1;
                }
            }
        }
        maxi = max(maxi, color_count);
        clog << color_count << "!" << endl;
    }
    if (maxi == 0) cout << -1 << endl;
    else cout << maxi << endl;
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