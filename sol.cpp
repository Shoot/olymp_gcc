#include <bits/stdc++.h>
using namespace std;
using vbo = vector<bool>;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
using ld = long double;
using qll = queue<ll>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using vvpll = vector<vector<pll>>;
using qld = queue<ld>;
using vld = vector<ld>;
using qpll = queue<pll>;
using vpll = vector<pll>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
ostream& endl(ostream& os) {
    return os << '\n';
}
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;

void solve() {
    ll n, m; cin >> n >> m;
    vector<vvpll> sm(n, vvpll(m));
    vector<string> d(n);
    for (auto &x : d) {
        cin >> x;
    }
    vvll ok(n, vll(m));
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            if (d[i][j] == '.') {
                ok[i][j] = true;
            }
        }
    }
    vector<pair<pll, pll>> edges;
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            if (!ok[i][j]) continue;
            if (i > 0 && ok[i-1][j]) sm[i][j].push_back(pll(i-1, j)), edges.push_back(make_pair(pll(i,j), pll(i-1,j)));
            if (j > 0 && ok[i][j-1]) sm[i][j].push_back(pll(i, j-1)), edges.push_back(make_pair(pll(i,j), pll(i,j-1)));
            if (j+1 < m && ok[i][j+1]) sm[i][j].push_back(pll(i, j+1)), edges.push_back(make_pair(pll(i,j), pll(i,j+1)));
            if (i+1 < n && ok[i+1][j]) sm[i][j].push_back(pll(i+1, j)), edges.push_back(make_pair(pll(i,j), pll(i+1,j)));
        }
    }
    vvll seen(n, vll(m));
    vvll depth(n, vll(m));
    vvll up_in_subtree(n, vll(m));
    auto dfs = [&] (auto f, pll v, pll par) -> void {
        if (par != v) depth[v.first][v.second] = depth[par.first][par.second] + 1;
        seen[v.first][v.second] = true;
        up_in_subtree[v.first][v.second] = depth[v.first][v.second];
        for (const auto &x : sm[v.first][v.second]) {
            if (x != par) {
                if (seen[x.first][x.second]) {
                    up_in_subtree[v.first][v.second] = min(up_in_subtree[v.first][v.second], depth[x.first][x.second]);
                }
            }
        }
        for (const auto &x : sm[v.first][v.second]) {
            if (!seen[x.first][x.second]) {
                f(f, x, v);
                up_in_subtree[v.first][v.second] = min(up_in_subtree[v.first][v.second], up_in_subtree[x.first][x.second]);
            }
        }
    };
    for (int i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            if (!seen[i][j]) {
                depth[i][j] = 1;
                dfs(dfs, pll(i,j), pll(i,j));
            }
        }
    }
    for (auto &x : d) {
        for (auto &y : x) {
            if (y == '.') {
                y = 'X';
            }
        }
    }
//    cout << up_in_subtree[0][0] << endl;
//    cout << up_in_subtree[0][1] << endl;
//    cout << up_in_subtree[1][0] << endl;
//    cout << up_in_subtree[1][1] << endl;
    for (const auto &[u, v] : edges) {
        if (depth[u.first][u.second] >= up_in_subtree[v.first][v.second] && depth[u.first][u.second] < depth[v.first][v.second]) {
            d[v.first][v.second] = '.';
            d[u.first][u.second] = '.';
        }
    }
    for (const auto &x : d) {
        cout << x << endl;
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(17);
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
        }
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

    while (tt--) {
        solve();
    }
    return 0;
}