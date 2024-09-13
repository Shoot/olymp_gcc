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
    vector<bool> done_temp_classification(n, false);
    vector<ll> comp_number_by_v (n);
    fo(i, 0, n) {
        if (done_temp_classification[i]) continue;
        queue<ll> q;
        q.push(i);
        while (!q.empty()) {
            ll top = q.front();
            q.pop();
            if (done_temp_classification[top]) continue;
            done_temp_classification[top] = true;
            comp_number_by_v[top] = i;
            if (outcoming[top] != -1) {
                q.push(outcoming[top]);
            }
            for (auto v: incoming[top]) {
                q.push(v);
            }
        }
    }
    vector<vector<ll>> queries_by_comp (n);
    ll queries; cin >> queries;
    fo(i, 0, queries) {
        ll obed;
        cin >> obed;
        obed -= 1;
        queries_by_comp[comp_number_by_v[obed]].push_back(obed);
    }
    ll tot = 0;
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
        clog << "queries: ";
        for (ll v: queries_by_comp[i]) {
            clog << v << " ";
        }
        clog << endl;
        vector<vector<ll>> palki (starts.size());
        vector<ll> number_of_palka_by_v (n, -1);
        fo(ii, 0, starts.size()) {
            ll start = starts[ii];
            while (!is_cycle[start]) {
                palki[ii].push_back(start);
                number_of_palka_by_v[start] = ii;
                start = outcoming[start];
            }
        }
        vector<vector<ll>> queries_by_number_of_palka (starts.size());
        vector<ll> cycle_queries;
        for (ll v: queries_by_comp[i]) {
            if (number_of_palka_by_v[v] == -1) break;
            queries_by_number_of_palka[number_of_palka_by_v[v]].push_back(v);
        }
        for (ll v: queries_by_comp[i]) {
            if (number_of_palka_by_v[v] == -1) cycle_queries.push_back(v);
        }
        fo(iii, 0, starts.size()) {
            auto palka = palki[iii];
            vector<ll> order_in_palka_by_v (n);
            clog << "    palka: ";
            fo(iiii, 0, palka.size()) {
                order_in_palka_by_v[palka[iiii]] = iiii;
                clog << palka[iiii] << " ";
            }
            clog << endl;
            clog << "        queries of that palka: ";
            for (ll v: queries_by_number_of_palka[iii]) {
                clog << v << " ";
            }
            clog << endl;
            ll last_query_order_in_palka = 0;
            for (ll v: queries_by_number_of_palka[iii]) {
                clog << "для v = " << v << ": ";
                ll order = order_in_palka_by_v[v];
                if (order <= last_query_order_in_palka) {
                    clog << endl;
                    continue;
                }
                tot += (order-last_query_order_in_palka)*(last_query_order_in_palka+1);
                clog << "contribution1 = " << (order-last_query_order_in_palka)*(last_query_order_in_palka+1);
                ll diff_minus_1 = order-last_query_order_in_palka-1;
                if (diff_minus_1 > 0) {
                    tot += diff_minus_1*(diff_minus_1+1)/2;
                    clog << ", contribution2 = " << diff_minus_1*(diff_minus_1+1)/2;
                }
                last_query_order_in_palka = order;
                clog << endl;
            }
        }
        clog << "cycle queries: ";
        for (ll v: cycle_queries) {
            clog << v << " ";
        }
        clog << endl;
    }
    cout << tot << endl;
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