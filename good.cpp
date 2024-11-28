#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
using vvll = vector<vector<ll>>;
using vvpll = vector<vector<pll>>;
void solve() {
    ll INF = 1e18;
    ll n, m, k;
    cin >> n >> m >> k;
    vvpll sm(n+1);
    struct edge {
        ll u, v, w, idx;
    };
    vector<edge> edges(m);
    ll nvm = 0;
    for (auto &edge : edges) {
        nvm += 1;
        edge.idx = nvm;
        cin >> edge.u >> edge.v >> edge.w;
        edge.w = -edge.w;
        sm[edge.u].push_back(pll(edge.v, edge.w));
    }
    vll need(k);
    for (auto &x : need) cin >> x;
    vvll D(n+1, vll(n+1, INF));
    vvll EDGE(n+1, vll(n+1, INF));
    vvll nxt(n+1, vll(n+1, INF));
    for (ll i = 1; i <= n; i += 1) {
        D[i][i] = 0;
        nxt[i][i] = i;
    }
    for (const auto &[u, v, w, idx] : edges) {
        if (D[u][v] > w) {
            D[u][v] = w;
            EDGE[u][v] = idx;
            nxt[u][v] = v;
        }
    }
    vll ans;
    for (ll i = 1; i <= n; i += 1) {
        for (ll u = 1; u <= n; u += 1) {
            for (ll v = 1; v <= n; v += 1) {
                if (D[u][i] + D[i][v] < D[u][v]) {
                    if (D[u][i] < INF && D[i][v] < INF) {
                        // чтобы не делать тупых обновлений из-за отриц ребер
                        // то есть может получится < INF а пути нету!!
                        D[u][v] = D[u][i] + D[i][v];
                        nxt[u][v] = nxt[u][i];
                        if (D[u][v] < -INF) D[u][v] = -INF;
                    }
                }
            }
        }
    }
    bool FARM_IT = false;
    auto go_to = [&] (ll from, ll to) -> void {
        while (from != to) {
            ans.push_back(EDGE[from][nxt[from][to]]);
            from = nxt[from][to];
        }
    };
    for (ll i = 1; i < k; i += 1) {
        ll from = need[i-1];
        ll to = need[i];
        for (ll s = 1; s <= n; s += 1) {
            FARM_IT |= D[from][s] < INF && D[s][to] < INF && D[s][s] < 0;
        }
        go_to(from, to);
    }
    if (FARM_IT) {
        cout << "infinitely kind" << endl;
        return;
    }
    cout << ans.size() << endl;
    for (const auto &x : ans) {
        cout << x << ' ';
    }cout << endl;
}
int main()
{
    solve();
    return 0;
}