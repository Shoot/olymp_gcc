#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
void solve() {
    ll n, q; cin >> n >> q;
    vector<ll> p(n+1);
    iota(p.begin(), p.end(), 0ll);
    struct Change {

    };
    stack<Change> stck;
    for (ll i = 0; i < n; i += 1) {

    }
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