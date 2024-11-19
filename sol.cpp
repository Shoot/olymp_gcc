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
uniform_int_distribution<ll> distrib(0ll, 10ll);
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
    ll n, d; cin >> n >> d;
    vll a(n); for (auto &x : a) cin >> x;
    vll b = a;
    sort(all(b));
    vpll shit(n);
    for (ll i = 0; i < n; i += 1) {
        shit[i].first = a[i];
        shit[i].second = i;
    }
    sort(all(shit));
    vll rel_by_ind(n);
    for (ll i = 0; i < n; i += 1) {
        rel_by_ind[shit[i].second] = i;
    }
    vll to(n, -1);
    struct Node {
        ll val=-1e18;
        ll ind=-1;
        auto operator<=>(const Node& other) const = default;
    };
    vector<Node> tree(4*n+10);
    auto merge = [&] (Node a, Node b) -> Node {
        if (a.val >= b.val) return a;
        return b;
    };
    auto set_point = [&] (auto f, ll v, ll tl, ll tr, ll pos, ll val) -> void {
        if (tl == tr) {
            tree[v].val = val;
            tree[v].ind = pos;
            return;
        }
        ll tm = (tl+tr) >> 1;
        if (pos <= tm) {
            f(f, 2*v+1, tl, tm, pos, val);
        } else {
            f(f, 2*v+2, tm+1, tr, pos, val);
        }
        tree[v] = merge(tree[2*v+1], tree[2*v+2]);
    };
    auto get_segment = [&] (auto f, ll v, ll tl, ll tr, ll l, ll r) -> Node {
        if (tl == l && tr == r) {
            return tree[v];
        }
        ll tm = (tl+tr) >> 1;
        Node ans;
        if (l <= tm) {
            ans = merge(ans,
            f(f, 2*v+1, tl, tm, l, min(tm, r)));
        }
        if (r >= tm+1) {
            ans = merge(ans,
            f(f, 2*v+2, tm+1, tr, max(tm+1, l), r));
        }
        return ans;
    };
    for (ll i = n-1; i >= 0; i -= 1) {
        ll x = a[i];
        ll rel_x = rel_by_ind[i];
        ll from_less_or_eq = upper_bound(all(b), x-d)-b.begin()-1;
        ll start = 0;
        ll from_more_or_eq = lower_bound(all(b), x+d)-b.begin();
        ll finish = b.size()-1;
//        for (ll j = start; j <= from_less_or_eq; j += 1) {
//            if (val[j]+1 > val[rel_x]) {
//                val[rel_x] = val[j]+1;
//                to[i] = shit[j].second;
//            }
//        }
//        for (ll j = from_more_or_eq; j <= finish; j += 1) {
//            if (val[j]+1 > val[rel_x]) {
//                val[rel_x] = val[j]+1;
//                to[i] = shit[j].second;
//            }
//        }
        Node res(0, -1);
        if (start <= from_less_or_eq) res = merge(res, get_segment(get_segment, 0, 0, n-1, start, from_less_or_eq));
        if (from_more_or_eq <= finish) res = merge(res, get_segment(get_segment, 0, 0, n-1, from_more_or_eq, finish));
        to[i] = shit[res.ind].second;
        set_point(set_point, 0, 0, n-1, rel_x, max(res.val+1, 1ll));
    }
    Node root = get_segment(get_segment, 0, 0, n-1, 0, n-1);
    cout << root.val << endl;
    ll start = shit[root.ind].second;
    cout << start+1 << ' ';
    while (root.val-- > 1) {
        start = to[start];
        cout << start+1 << ' ';
    }
    cout << endl;
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