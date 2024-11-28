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
    ll n;
    cin >> n;
    vvll D(n, vll(n));
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            cin >> D[i][j];
            if (!D[i][j] && i != j) D[i][j] = INF;
        }
    }
    for (ll i = 0; i < n; i += 1) {
        for (ll u = 0; u < n; u += 1) {
            for (ll v = 0; v < n; v += 1) {
                if (D[u][i] + D[i][v] < D[u][v]) {
                    if (D[u][i] < INF && D[i][v] < INF) {
                        // чтобы не делать тупых обновлений из-за отриц ребер
                        // то есть может получится < INF а пути нету!!
                        D[u][v] = D[u][i] + D[i][v];
                        if (D[u][v] < -INF) D[u][v] = -INF;
                    }
                }
            }
        }
    }
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < n; j += 1) {
            bool got = false;
            for (ll k = 0; k < n; k++) {
                got |= (D[k][k] < 0) && (D[i][k] < INF) && (D[k][j] < INF);
            }
            if (got) {
                cout << 2 << ' ';
            } else if (D[i][j] == INF) {
                cout << 0 << ' ';
            } else {
                cout << 1 << ' ';
            }
        }
        cout << endl;
    }
}
int main()
{
    solve();
    return 0;
}