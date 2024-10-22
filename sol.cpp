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
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
template <class T, class S> inline bool chmax(T &a, const S &b) { return (a < b ? a = b, 1 : 0); }
template <class T, class S> inline bool chmin(T &a, const S &b) { return (a > b ? a = b, 1 : 0); }
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
void scan(ll &a) { cin >> a; }
void scan(char &a) { cin >> a; }
void scan(double &a) { cin >> a; }
void scan(long double &a) { cin >> a; }
void scan(string &a) { cin >> a; }
template <class T, class S> void scan(pair<T, S> &p) { scan(p.first), scan(p.second); }
template <class T> void scan(vector<T> &a) {for(auto &i : a) scan(i);}
template <class T> void scan(T &a) { cin >> a; }
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
#ifdef LOCAL
#include <algo/debug.h>
#else
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distrib(1ll, 12ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 998244353;
void in(vector<ll> & a) {
    for (auto & zero_leaf : a) cin >> zero_leaf;
}
void in(vector<ll> & a, ll l, ll r) {
    for (ll i=l; i < r; i+=1) {
        cin >> a[i];
    }
}
void inn(vector<ll> & a, ll l, ll rr) {
    for (ll i=l; i <= rr; i+=1) {
        cin >> a[i];
    }
}
ll powm(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MOD;
        b >>= 1;
        a = (a*a) % MOD;
    }
    return d;
}
ll powm(ll a, ll b, ll MODD) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a) % MODD;
        b >>= 1;
        a = (a*a) % MODD;
    }
    return d;
}
ll poww(ll a, ll b) {
    assert(b >= 0);
    ll d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ld poww(ld a, ll b) {
    assert(b >= 0);
    ld d = 1;
    while (b) {
        if (b&1) d = (d*a);
        b >>= 1;
        a = (a*a);
    }
    return d;
}
ll mul(ll a, ll b) {
    return (a*b)%MOD;
}
ll mul(ll a, ll b, ll MODD) {
    return (a*b)%MODD;
}
ll sum(ll a, ll b) {
    return (a+b)%MOD;
}
ll sum(ll a, ll b, ll MODD) {
    return (a+b)%MODD;
}
ll sub(ll a, ll b) {
    return (a-(b%MOD)+MOD)%MOD;
}
ll sub(ll a, ll b, ll MODD) {
    return (a-(b%MODD)+MODD)%MODD;
}
ll fj0dsq983gf8(ll index, vector<ll> & tree)  {
    index += 1;
    ll sum = 0;
    while (index > 0) {
        sum += tree[index-1];
        index -= index & -index;
    }
    return sum;
} // zero-indexed!!!
ll get_sum_ft(ll left, ll right, vector<ll> & tree) {
    ll n = (ll)tree.size();
    if (left > right) return 0;
    assert(left <= right);
    if (right >= n) {
        clog << "FENWICK ALERT: R >= tree.size() (IT'S ZERO INDEXED !!!)" << endl;
        right = n-1;
    }
    ll dist_from_last_bfs = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        dist_from_last_bfs -= fj0dsq983gf8(left - 1, tree);
    }
    return dist_from_last_bfs;
} // zero-indexed!!!
void inc_ft(ll index, ll inc, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(index >= 0);
    assert(index < n);
    index += 1;
    while (index < n) {
        tree[index] += inc;
        index += index & -index;
    }
} // zero-indexed!!!
void build_ft(vector<ll> & a, vector<ll> & tree) {
    ll n = (ll)tree.size();
    assert(tree.size() == a.size());
    for (ll i = 0; i < n; i++) {
        tree[i] += a[i];
        ll good = i | (i + 1);
        if (good < n) tree[good] += tree[i];
    }
} // zero-indexed!!!
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
void solve() {
    ll n, q;
    cin >> n >> q;
    vvll sm(n+1);
    for (ll i = 0; i < n-1; i += 1) {
        ll u, v;
        cin >> u >> v;
        sm[u].push_back(v);
        sm[v].push_back(u);
    }
    // lca precompute using euler tour
    vll euler_tour;
    bitset<100001> seen;
    vll depth;
    vll time_in(n+1);
    ll time = 0;
    function<void(ll, ll)> dfs_euler_tour = [&] (ll v, ll d) {
        seen[v] = true;
        euler_tour.push_back(v);
        depth.push_back(d);
        time_in[v] = time++;
        for (auto &x : sm[v]) if (!seen[x]) {
            dfs_euler_tour(x, d+1);
            euler_tour.push_back(v);
            depth.push_back(d);
            time++;
        }
    };
    dfs_euler_tour(1, 0);
//    for (auto &y : euler_tour) {
//        cout << y << ' ';
//    }
//    cout << endl;
//    for (auto &y : depth) {
//        cout << y << ' ';
//    }
//    cout << endl;
    // find euler_tour(min_element(depth[  time_in[u], ... time_in[v]  ])-h.begin())
    ll sz = ll(depth.size());
    vvll st(20, vll(sz));
    st[0] = depth;
    for (ll i = 1; i < 20; i += 1) {
        for (ll j = 0; j < sz; j += 1) {
            ll nxt = j + (1ll << (i-1));
            if (nxt >= sz) break;
            st[i][j] = min(st[i-1][j], st[i-1][nxt]);
        }
    }
    function<ll(ll,ll)> lca_d = [&] (ll u, ll v) {
        if (time_in[u] > time_in[v]) {
            swap(u,v);
        }
        ll l = time_in[u];
        ll r = time_in[v];
        if (l == r) return depth[l];
        ll power_of_two = ll(log2l(r-l+1));
//        cout << l << " " << r << ": " << power_of_two << endl;
//        ll OG = 1e9;
//        for (ll i = l; i <= r; i += 1) {
//            OG = min(OG, depth[i]);
//        }
        ll my_ans = min(st[power_of_two][l], st[power_of_two][r-(1ll << power_of_two)+1]);
        return my_ans;
    };
    function<ll(ll,ll)> dist = [&] (ll u, ll v) {
        auto lca_depth = lca_d(u,v);
        auto u_depth = depth[time_in[u]];
        auto v_depth = depth[time_in[v]];
        return abs(lca_depth-u_depth)+abs(lca_depth-v_depth);
    };
    const ll K = 320;
    ll prev = -1;
    qll qq;
    vll vertices_to_bfs;
    vertices_to_bfs.push_back(1);
    vll dist_from_last_bfs(n+1, 1e9);
    dist_from_last_bfs[1] = 0;
    bitset<100001> seen_bfs;
    function<void(void)> bfs = [&] () {
        while (!qq.empty()) {
            auto tp = qq.front();
            qq.pop();
            seen_bfs[tp] = true;
            for (const auto &x : sm[tp]) if (!seen_bfs[x]) {
                seen_bfs[x] = true;
                dist_from_last_bfs[x] = min(dist_from_last_bfs[x], dist_from_last_bfs[tp]+1);
                qq.push(x);
            }
        }
    };
    for (ll i = 0; i < q; i +=1){
        ll type; cin >> type;
        ll v; cin >> v;
        if (type == 1) {
            vertices_to_bfs.push_back(v);
            dist_from_last_bfs[v] = 0;
            // color_red
        } else {
            // closest_red
            // поднимаемся вверх пока не найдем вершину с актуальным значением,
            // mini = min(mini, podn+relevant_value)
            ll mini = dist_from_last_bfs[v];
            for (const auto &x : vertices_to_bfs) {
                mini = min(mini, dist(v, x));
            }
            cout << mini << endl;
        }
        if (i/K != prev) {
            for (const auto &x : vertices_to_bfs) {
                qq.push(x);
            }
            vertices_to_bfs.clear();
            seen_bfs.reset();
            bfs();
            prev = i/K;
        }
    }
}
int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << setprecision(17);
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