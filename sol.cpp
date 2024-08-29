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
ll color[201];
ll newcomponent[201];
void solve () {
    forr(i, 1, 200) {
        newcomponent[i] = 1;
    }
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
//    ll reb_DELETE; cin >> reb_DELETE;
//    while (reb_DELETE--) {
//        ll x_DELETE, y_DELETE; cin >> x_DELETE >> y_DELETE;
//        sm[x_DELETE].push_back(y_DELETE);
//        sm[y_DELETE].push_back(x_DELETE);
//    }
    ll tot = 0;
    forr(i, 1, n) { // comp search
        if (newcomponent[i] == 1) {
            unordered_set<ll> comp_pool;
            queue<ll> comp_dfs_q;
            comp_dfs_q.push(i);
            while (!comp_dfs_q.empty()) {
                ll curr = comp_dfs_q.front();
                comp_dfs_q.pop();
                newcomponent[curr] = 0;
                comp_pool.insert(curr);
                for (ll nxt: sm[curr]) {
                    if (newcomponent[nxt] == 1) {
                        comp_dfs_q.push(nxt);
                    }
                }
            }
            clog << "comp pool length: " << comp_pool.size() << endl;
            ll maxi = 0;
            for(ll starting_point: comp_pool) clog << starting_point << ' ';
            clog << endl;
            for(ll starting_point: comp_pool) {
                clog << "start = " << starting_point << endl;
                memset(color, 0, sizeof(color));
                bool wrong = false;
                queue<ll> q;
                color[starting_point] = 1;
                q.push(starting_point);
                ll current_number = 1;
                while (!q.empty()) {
                    ll v = q.front();
                    clog << "v = " << v << endl;
                    q.pop();
                    bool plus = false;
                    for(ll nei: sm[v]) {
                        if (color[nei] == 0) {
                            color[nei] = current_number+1;
                            clog << nei << " = " << current_number+1 << endl;
                            q.push(nei);
                            plus = true;
                        }
                        if (abs(color[v]-color[nei]) != 1) {
                            clog << color[v] << " vs. " << color[nei] << endl;
                            wrong = true;
                        }
//                assert(color[v] != clor[nei]);
                    }
                    if (plus) current_number += 1;
                }
                if (!wrong) {
                    maxi = max(maxi, current_number);
                    clog << current_number << "!" << endl;
                }
            }
            if (maxi == 0) {
                cout << -1 << endl;
                return;
            }
            assert(maxi > 0);
            tot += maxi;
        } else {
            clog << i << " isnt new comp " << endl;
        }
    }
    assert(tot > 0);
    cout << tot << endl;
//    forr(i, 1, n) {
//        clog << i << ": ";
//        for (ll j: sm[i]) {
//            clog << j << ' ';
//        }
//        clog << endl;
//    }
//    for (auto [i, j]: cnt) {
//        clog << i << " x " << j << endl;
//    }
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