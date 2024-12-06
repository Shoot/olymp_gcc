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
    ll rx, ry; cin >> rx >> ry; rx -= 1; ry -= 1;
    ll fx, fy; cin >> fx >> fy; fx -= 1; fy -= 1;
    vvll ok(n, vll(m, true));
    ll shitty; cin >> shitty;
    for (ll i = 0; i < shitty; i += 1) {
        ll x, y; cin >> x >> y; x -= 1; y -= 1;
        ok[x][y] = false;
    }
    ll d[100][100][4];
    const ll FROM_UP = 0;
    const ll FROM_RIGHT = 1;
    const ll FROM_DOWN = 2;
    const ll FROM_LEFT = 3;
    ll dx[4] = {1, 0, -1, 0};
    ll dy[4] = {0, -1, 0, 1};
    ll shit[4] = {3, 0, 1, 2};
    const ll INF = 1e18;
    for (ll i = 0; i < 100; i += 1) {
        for (ll j = 0; j < 100; j += 1) {
            d[i][j][FROM_UP] = INF;
            d[i][j][FROM_DOWN] = INF;
            d[i][j][FROM_LEFT] = INF;
            d[i][j][FROM_RIGHT] = INF;
        }
    }
    d[rx][ry][FROM_UP] = 0;
    d[rx][ry][FROM_DOWN] = 0;
    d[rx][ry][FROM_LEFT] = 0;
    d[rx][ry][FROM_RIGHT] = 0;
    qpll q; q.push(pll(rx,ry));
    while (!q.empty()) {
        ll x = q.front().first;
        ll y = q.front().second;
        q.pop();
        for (ll from = 0; from < 4; from += 1) {
            if (d[x][y][from] == INF) continue;
            for (ll i = 0; i < 4; i += 1) {
                if (i == from) continue;
                if (x + dx[i] < 0 || x + dx[i] >= n) continue;
                if (y + dy[i] < 0 || y + dy[i] >= m) continue;
                if (!ok[x+dx[i]][y+dy[i]]) continue;
                ll nxt = d[x][y][from] + 1;
                if (nxt < d[x+dx[i]][y+dy[i]][shit[i]]) {
                    d[x+dx[i]][y+dy[i]][shit[i]] = nxt;
                    q.push(pll(x+dx[i], y+dy[i]));
                }
            }
        }
    }
    ll mini = INF;
    for (ll i = 0; i < 4; i += 1) {
        mini = min(mini, d[fx][fy][i]);
    }
    if (mini == INF) {
        mini = -1;
    }
    cout << mini << endl;
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