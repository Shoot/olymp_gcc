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
    ll n;
    cin >> n;
    vll beauty(n+1);
    vll depth_by_v(n+1);
    vll time_in_by_v(n+1);
    vll time_out_by_v(n+1);
    for (ll i = 1; i <= n; i += 1) {
        cin >> beauty[i];
    }
    vvll sm(n+1);
    for (ll i = 2; i <= n; i += 1) {
        ll p;
        cin >> p;
        sm[p].push_back(i);
    }
    const ll N = 1e5+1;
    bitset<N> seen;
    ll time = 0;
    vll euler_tour(n+n-1);
    function<void(ll,ll)> dfs = [&] (ll v, ll d) {
        depth_by_v[v] = d;
        seen[v] = true;
        time_in_by_v[v] = time;
        time_out_by_v[v] = time;
        euler_tour[time++] = v;
        for (const auto &x : sm[v]) {
            dfs(x, d+1);
            time_out_by_v[v] = time;
            euler_tour[time++] = v;
        }
    };
    dfs(1,0);
//    for (const auto &x : euler_tour) {
//        cout << x << ' ';
//    }
//    cout << endl;
    assert(time == euler_tour.size());
    vpll queries;
    map<pll,ll> answer;
    struct node {
        ll maxi=0;
    };
    vector<node> st(4*(n+1)+5);
    auto inc = [&] (auto f, ll pos, ll val, ll tl, ll tr, ll v = 0) -> void {
        if (tl == pos && tr == pos) {
            st[v].maxi += val;
        } else {
            ll mid = (tl+tr) >> 1;
            if (pos <= mid) {
                f(f, pos, val, tl, mid, 2*v+1);
            } else {
                f(f, pos, val, mid+1, tr, 2*v+2);
            }
            st[v].maxi = max(st[2*v+1].maxi, st[2*v+2].maxi);
        }
    };
    unordered_map<ll, ll> times_counted;
    for (auto &v : euler_tour) {
        times_counted[v] += 1;
        if (times_counted[v] == 1) inc(inc, depth_by_v[v], beauty[v], 0, n);
//        curr_value_by_depth[depth_by_v[v]] += beauty[v];
//        cout << depth_by_v[v] << "+= " << beauty[v] << endl;
    }
    for (ll v = 2; v <= n; v += 1) {
        queries.push_back(pll(time_in_by_v[v], time_out_by_v[v]));
        // delete subtree of v
        // max sum on one layer
    }
    auto queries_natural = queries;
    const ll K = 500;
    sort(all(queries), [&] (pll a, pll b) {
        if (a.first/K == b.first/K) return a.second < b.second;
        return a.first/K < b.first/K;
    });

    ll curr_l = -1; // first included -1
    ll curr_r = -1; // last included
    for (auto const &[l,r] : queries) {
        while (curr_l < l-1) {
            times_counted[euler_tour[curr_l+1]] += 1;
            if (times_counted[euler_tour[curr_l+1]] == 1)
                inc(inc, depth_by_v[euler_tour[curr_l+1]], beauty[euler_tour[curr_l+1]], 0, n);
//            curr_value_by_depth[depth_by_v[euler_tour[curr_l+1]]] += beauty[euler_tour[curr_l+1]];
//            cout << "-" << euler_tour[curr_l+1] << endl;
            curr_l += 1;
        }
        while (curr_l > l-1) {
            times_counted[euler_tour[curr_l]] -= 1;
            if (times_counted[euler_tour[curr_l]] == 0)
                inc(inc, depth_by_v[euler_tour[curr_l]], -beauty[euler_tour[curr_l]], 0, n);
//            curr_value_by_depth[depth_by_v[euler_tour[curr_l]]] -= beauty[euler_tour[curr_l]];
//            cout << "+" << euler_tour[curr_l] << endl;
            curr_l -= 1;
        }
        while (curr_r < r) {
            times_counted[euler_tour[curr_r+1]] -= 1;
            if (times_counted[euler_tour[curr_r+1]] == 0)
                inc(inc, depth_by_v[euler_tour[curr_r+1]], -beauty[euler_tour[curr_r+1]], 0, n);
//            curr_value_by_depth[depth_by_v[euler_tour[curr_r+1]]] -= beauty[euler_tour[curr_r+1]];
//            cout << "+" << euler_tour[curr_r+1] << endl;
            curr_r += 1;
        }
        while (curr_r > r) {
            times_counted[euler_tour[curr_r]] += 1;
            if (times_counted[euler_tour[curr_r]] == 1)
                inc(inc, depth_by_v[euler_tour[curr_r]], beauty[euler_tour[curr_r]], 0, n);
//            curr_value_by_depth[depth_by_v[euler_tour[curr_r]]] += beauty[euler_tour[curr_r]];
//            cout << "-" << euler_tour[curr_r] << endl;
            curr_r -= 1;
        }
        ll curr_ans = st[0].maxi;
//        cout << l << " " << r << ": " << curr_ans << endl;
        answer[pll(l,r)] = curr_ans;
    }
    for (auto const &[i,j] : queries_natural) {
        cout << answer[pll(i,j)] << ' ';
    }
    cout << endl;
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
    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}