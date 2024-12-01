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
template <class T, class S> inline bool chmax(T &best, const S &b) { return (best < b ? best = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &best, const S &b) { return (best > b ? best = b, 1 : 0); }
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& A) {
    os << A.fi << " " << A.se;
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& A) {
    for (size_t i = 0; i < A.size(); i++) {
        if (i) os << " ";
        os << A[i];
    }
    return os;
}
void scan(ll &best) { cin >> best; }
void scan(char &best) { cin >> best; }
void scan(double &best) { cin >> best; }
void scan(long double &best) { cin >> best; }
void scan(string &best) { cin >> best; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &best) {for(auto &i : best) scan(i);}
template <class T> void scan(T &best) { cin >> best; }
void IN() {}
template <class Head, class... Tail> void IN(Head &head, Tail &...tail) {
    scan(head);
    IN(tail...);
}
void print() {
    cout << "\n";
}
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
    cout << head;
    if (sizeof...(Tail)) cout << " ";
    print(forward<Tail>(tail)...);
}
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(0ll, 5ll);
//constexpr ll MOD = 819356875157278019ll;
constexpr ll MOD = 1e9+7;
void in(vector<ll> & best) {
    for (auto & zero_leaf : best) cin >> zero_leaf;
}
void in(vector<ll> & best, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> best[i];
    }
}
void inn(vector<ll> & best, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> best[i];
    }
}
ll powm(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MOD;
        b >>= 1;
        best = (best*best) % MOD;
    }
    return d;
}
ll powm(ll best, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best) % MODD;
        b >>= 1;
        best = (best*best) % MODD;
    }
    return d;
}
ll poww(ll best, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ld poww(ld best, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*best);
        b >>= 1;
        best = (best*best);
    }
    return d;
}
ll mul(ll best, ll b) {
    return (best*b)%MOD;
}
ll mul(ll best, ll b, ll MODD) {
    return (best*b)%MODD;
}
ll sum(ll best, ll b) {
    return (best+b)%MOD;
}
ll sum(ll best, ll b, ll MODD) {
    return (best+b)%MODD;
}
ll sub(ll best, ll b) {
    return (best-(b%MOD)+MOD)%MOD;
}
ll sub(ll best, ll b, ll MODD) {
    return (best-(b%MODD)+MODD)%MODD;
}
void solve() {
    ll n, q; cin >> n >> q;
    vll a(n);
    map<ll,set<ll>> positions;
    for (ll i = 0; i < n; i += 1) {
        cin >> a[i];
        positions[a[i]].insert(i);
    }
    map<ll,ll> total;
    multiset<pll> total_values;
    for (auto &[val, st] : positions) {
        ll prev_pos = -1;
        for (const auto &pos : st) {
            ll sz = pos-prev_pos-1;
            total[val] += sz*(sz+1)/2;
            prev_pos = pos;
        }
        ll sz = n-prev_pos-1;
        total[val] += sz*(sz+1)/2;
        st.insert(-1);
        st.insert(n);
    }
    for (const auto &[c, kol] : total) {
        total_values.insert(pll(kol, c));
    }
    for (ll ii = 0; ii < q; ii += 1) {
        ll idx, val;
        cin >> idx >> val;
        if (!total.contains(val)) {
            positions[val].insert(-1);
            positions[val].insert(n);
            ll sz = n-(-1)-1;
            total[val] = sz*(sz+1)/2;
            total_values.insert(pll(total[val], val));
        }
        idx -= 1;
        if (a[idx] != val) {
            positions[a[idx]].erase(idx);
            auto nxt = positions[a[idx]].upper_bound(idx);
            auto prev = nxt; prev--;
            total_values.erase(total_values.find(pll(total[a[idx]], a[idx])));
            ll sz_l = idx-*prev-1;
            total[a[idx]] -= sz_l*(sz_l+1)/2;
            ll sz_r = *nxt-idx-1;
            total[a[idx]] -= sz_r*(sz_r+1)/2;
            ll sz_new = *nxt-*prev-1;
            total[a[idx]] += sz_new*(sz_new+1)/2;
            total_values.insert(pll(total[a[idx]], a[idx]));

            a[idx] = val;
            positions[a[idx]].insert(idx);
            auto nxtt = positions[a[idx]].upper_bound(idx);
            auto prevv = nxtt; prevv--; prevv--;
            total_values.erase(total_values.find(pll(total[a[idx]], a[idx])));
            ll sz_prevv = *nxtt-*prevv-1;
            total[a[idx]] -= sz_prevv*(sz_prevv+1)/2;
            ll nwl = idx-*prevv-1;
            total[a[idx]] += nwl*(nwl+1)/2;
            ll nwr = *nxtt-idx-1;
            total[a[idx]] += nwr*(nwr+1)/2;
            total_values.insert(pll(total[a[idx]], a[idx]));
        }
        cout << total_values.begin()->first << endl;
//        cout << total_values.begin()->first << "(" << total_values.begin()->second << ")" << endl;
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