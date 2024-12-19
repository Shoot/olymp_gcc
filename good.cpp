#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
using namespace std;
//define endl "\n"
using ll = int;
const ll INF = 1e9;
mt19937 mt(time(0));
void solve() {
    ll n, k; cin >> n >> k;
    vector<vector<ll>> sm(n+1);
    for (ll i = 1; i <= n; i += 1) {
        ll p; cin >> p;
        if (p != i) {
            sm[p].push_back(i);
        }
    }
    /* после удаления ровно k ребер чтобы {просуммировать только те у которых остались оба ребра} -> max */
    /* компоненты из простых циклов?? */
    /* получается, уничтожая ребро, мы уничтожаем 2 или 1 или 0 вершины */
    // максимум это сначала уничтожаем двойные
}

int main(int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; i += 1) use_fast_io &= string(argv[i]) != "-local-no-fast-io";
    if (use_fast_io) ios::sync_with_stdio(false), cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}
