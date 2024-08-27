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
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(1e5+1);
//constexpr ll MOD = 998244353;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll last[N];
void solve () {
    memset(last, -1, sizeof(last));
    ll n, m, vmest; cin >> n >> m >> vmest;
    ll prev = -1;
    ll cnt = 0;
    unordered_map<ll, vector<pair<ll, ll>>> mp;
    fo(i, 0, n) {
        ll x; cin >> x;
        if (x != prev) {
            if (prev != -1) {
                if (last[prev] == -1) mp[prev].emplace_back(0, cnt);
                else mp[prev].emplace_back(i-last[prev]-cnt, cnt);
                last[prev] = i;
            }
            cnt = 1;
        } else {
            cnt += 1;
        }
        prev = x;
    }
    if (last[prev] == -1) mp[prev].emplace_back(0, cnt);
    else mp[prev].emplace_back(n-last[prev]-cnt, cnt);
    ll maxi = 0;
    for (auto [i, v]: mp) {
        clog << i << ": " << endl;
        for (auto [l, c] : v) {
            clog << l << " " << c << endl;
        }
        ll st = 0;
        ll fi = 0;
        ll current_balance = vmest;
        ll total = v[0].second;
        while (st < v.size()) {
            while (current_balance >= 0 && fi+1 < v.size()) {
                clog << st << " -2> " << fi << " = " << total << endl;
                maxi = max(maxi, total);
                fi += 1;
                total += v[fi].second;
                current_balance -= v[fi].first;
            }
            if (current_balance >= 0) {
                clog << st << " -3> " << fi << " = " << total << endl;
                maxi = max(maxi, total);
            }
            bool stdv = false;
            while (current_balance < 0 && st+1 < v.size()) {
                clog << st << " -<> " << fi << endl;
                current_balance += v[st+1].first;
                total -= v[st].second;
                st += 1;
                stdv = true;
            }
            if (!stdv) st += 1;
        }
    }
    cout << maxi << endl;
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
    while (tt--) solve();
    return 0;
}