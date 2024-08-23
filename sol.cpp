#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define all(value) value.begin(), value.end()
#define fo(x, st, fi) for(ll x = st; x < fi; x++)
#define forr(x, st, fi) for(ll x = st; x <= fi; x++)
#define endl '\n'
#ifdef LOCAL
#include <algo/debug.h>
#else
#define debug(...) 68
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
const ll N = 3e5 + 1;
bitset<N> used;
void solve() {
    ll n; cin >> n;
    ll a[n];
    vector<ll> last_occurrence(n+1, N);
    fo(i, 0, n) {
        cin >> a[i];
        last_occurrence[a[i]] = i;
    }
    priority_queue<ll, vector<ll>, greater<>> last_occurrences(last_occurrence.begin(), last_occurrence.end());
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> mini;
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, less<>> maxi;
    used.reset();
    forr(i, 0, last_occurrences.top()) { // last_occurrences.top() == min (next el rightmost position)
        maxi.push({a[i], -i});
        mini.push({a[i], i});
        clog << "new: " << a[i] << " (init)" << endl;
        assert(a[i] <= n);
    }
    vector<ll> b;
    ll nxt_el_window_l;
    while(!mini.empty()) {
        auto [x, pos] = (b.size() % 2 == 0 ? maxi.top() : mini.top());
        if (b.size() % 2 == 0) {
            maxi.pop();
            pos = -pos;
            clog << "maxi = " << x << endl;
        } else {
            mini.pop();
            clog << "mini = " << x << endl;
        }
        nxt_el_window_l = pos + 1; used[x] = true; b.push_back(x);
        clog << "new pos: " << nxt_el_window_l << endl;
        while(last_occurrences.top() != N and used[a[last_occurrences.top()]]) {
            ll j = last_occurrences.top(); last_occurrences.pop();
            for(ll k = j + 1; k <= min(last_occurrences.top(), n - 1); k++) {
                maxi.push({a[k], -k});
                mini.push({a[k], k});
                clog << "new: " << a[k] << endl;
            }
        }
        while(!maxi.empty() and (used[maxi.top()[0]] or -maxi.top()[1] < nxt_el_window_l)) {
            clog << "[maxi]fuck " << maxi.top()[0] << " at " << -maxi.top()[1] << endl;
            maxi.pop();
        }
        while(!mini.empty() and (used[mini.top()[0]] or mini.top()[1] < nxt_el_window_l)) {
            clog << "[mini]fuck " << mini.top()[0] << endl;
            mini.pop();
        }
    }

    cout << b.size() << endl;
    for(ll j: b) cout << j << " ";
    cout << endl;
}
int32_t main (int32_t argc, char* argv[]) {
//    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//    uniform_int_distribution<ll> distrib(1, LLONG_MAX);
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}