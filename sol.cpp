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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 4ll);
//constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 1e9+7;
/*\
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll powm(ll a, ll b){
    assert(b >= 0);
    ll d = 1;
    while(b){
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> incoming(n);
    vector<ll> outcoming(n, -1);
    vector<bool> done(n, false);
    fo(i, 0, n) {
        ll x;
        cin >> x;
        x -= 1;
        incoming[x].push_back(i);
        outcoming[i] = x;
    }
    fo(i, 0, n) {
        if (done[i]) continue;
        vector<ll> component;
        queue<ll> q;
        q.push(i);
        vector<ll> starts;
        while (!q.empty()) {
            ll top = q.front();
            q.pop();
            if (done[top]) continue;
            done[top] = true;
            component.push_back(top);
            if (outcoming[top] != -1) {
                q.push(outcoming[top]);
            }
            for (auto v: incoming[top]) {
                q.push(v);
            }
            if (incoming[top].empty()) {
                starts.push_back(top);
            }
        }
        assert(!starts.empty());
        ll curr_v = starts[0];
        vector<bool> done_temp(n, false);
        while (!done_temp[curr_v]) {
            done_temp[curr_v] = true;
            curr_v = outcoming[curr_v];
        }
        ll cycle_zamk = curr_v;
        vector<bool> is_cycle(n, false);
        vector<ll> cycle;
        while (!is_cycle[cycle_zamk]) {
            cycle.push_back(cycle_zamk);
            is_cycle[cycle_zamk] = true;
            cycle_zamk = outcoming[cycle_zamk];
        }
        clog << "component " << i << " cycle is ";
        for(ll v: cycle) {
            clog << v << ' ';
        }
        clog << endl;
        vector<vector<ll>> palki (starts.size());
        fo(ii, 0, starts.size()) {
            ll start = starts[ii];
            while (!is_cycle[start]) {
                palki[ii].push_back(start);
                start = outcoming[start];
            }
        }
        for (auto palka: palki) {
            clog << "    palka: ";
            for (ll v: palka) {
                clog << v << " ";
            }
            clog << endl;
        }
    }
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