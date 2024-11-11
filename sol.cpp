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
//ostream& endl(ostream& os) {
//    return os << '\n';
//}
#define all(xxx) xxx.begin(), xxx.end()
#define watch(xxx) cout << "value of " << #xxx << " is " << xxx << endl;
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
uniform_int_distribution<ll> distrib(1ll, 10ll);
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
char idx_to_name[3];
void solve() {
    ll n; cin >> n;
    vvll A(3, vll(n));
    vvll VAL_BY_PR(3, vll(n));
    for (ll i = 0; i < 3; i += 1) for (ll j = 0; j < n; j += 1) {
        ll pr;
        cin >> pr;
        pr -= 1;
        A[i][j] = pr;
        VAL_BY_PR[i][pr] = j;
    }
    vpll path;
    vvll ST(3, vll(4*n+10));
    auto merge = [&] (ll cv1, ll cv2, vll& a) {
        if (cv1 == -1) return cv2;
        if (cv2 == -1) return cv1;
        if (a[cv1] >= a[cv2]) return cv1;
        return cv2;
    };
    auto build = [&] (auto f, vll&a, vll& tree, ll v, ll tl, ll tr) -> void {
        if (tl == tr) {
            tree[v] = tl;
            return;
        }
        ll tm = (tl+tr) >> 1;
        f(f, a, tree, 2*v+1, tl, tm);
        f(f, a, tree, 2*v+2, tm+1, tr);
        tree[v] = merge(tree[2*v+1], tree[2*v+2], a);
    };
    for (ll i = 0; i < 3; i += 1) build(build, VAL_BY_PR[i], ST[i], 0, 0, n-1);
    auto set_point = [&] (auto f, vll& a, vll& tree, ll v, ll tl, ll tr, ll pos, ll val) -> void {
        if (tl == tr) {
            a[pos] = val;
            return ;
        }
        ll tm = (tl+tr) >> 1;
        if (pos <= tm) {
            f(f, a, tree, 2*v+1, tl, tm, pos, val);
        } else {
            f(f, a, tree, 2*v+2, tm+1, tr, pos, val);
        }
        tree[v] = merge(tree[2*v+1], tree[2*v+2], a);
    };
    auto get_max_on_segment = [&] (auto f, vll& a, vll& tree, ll v, ll tl, ll tr, ll l, ll r) -> ll {
        if (tl == l && tr == r) {
            return tree[v];
        }
        ll tm = (tl+tr) >> 1;
        ll left = -1;
        ll right = -1;
        if (l <= tm) {
            left = f(f, a, tree, 2*v+1, tl, tm, l, min(r, tm));
        }
        if (r >= tm+1) {
            right = f(f, a, tree, 2*v+2, tm+1, tr, max(l, tm+1), r);
        }
        return merge(left, right, a);
    };
    bool found = false;
    auto dfs = [&] (auto f, ll v) -> void {
        if (v == n-1) {
            found = true;
            return;
        }
//        cout << v << endl;
        for (ll i = 0; i < 3; i += 1) set_point(set_point, VAL_BY_PR[i], ST[i], 0, 0, n-1, A[i][v], -1);
        for (ll i = 0; i < 3; i += 1) {
            bool nvm = false;
            while (!nvm) {
                // максимальное с меньшим приоритетом
                ll nxt = get_max_on_segment(get_max_on_segment, VAL_BY_PR[i], ST[i], 0, 0, n-1, 0, A[i][v]);
//                    watch(VAL_BY_PR[i][nxt]);
                if (VAL_BY_PR[i][nxt] > v) {
//                watch(VAL_BY_PR[i][nxt]);
                    // can get smth better off ith guy
                    path.push_back(pll(i, VAL_BY_PR[i][nxt]));
                    f(f, VAL_BY_PR[i][nxt]);
                    if (found) return;
                    path.pop_back();
                } else {
                    nvm = true;
                }
            }
        }
    };
    dfs(dfs, 0);
    if (!found) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << path.size() << endl;
        for (const auto &[i, j] : path) {
            cout << idx_to_name[i] << " " << j+1 << endl;
        }
    }
}


int32_t main(int32_t argc, char* argv[]) {
    idx_to_name[0] = 'q';
    idx_to_name[1] = 'k';
    idx_to_name[2] = 'j';
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
    cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}