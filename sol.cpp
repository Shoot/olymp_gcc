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
    ll n, m; cin >> n >> m;
    vvpll sm(n+1);
    vvpll smrev(n+1);
    vvll cnt_by_v(n+1, vll(2));
    vvll cnt_by_v_rev(n+1, vll(2));
    for (ll i = 0; i < m; i += 1) {
        ll u, v; char c;
        cin >> u >> v >> c;
        sm[u].push_back(make_pair(v, c-'a'));
        smrev[v].push_back(make_pair(u, c-'a'));
        cnt_by_v[u][c-'a'] += 1;
        cnt_by_v_rev[v][c-'a'] += 1;
    }
    bitset<1'000'000> seen;
    bool FOUND = false;
    auto find_aa_bb = [&] (auto f, ll v) -> void {
        if (FOUND) return;
        if (cnt_by_v[v][0] && cnt_by_v_rev[v][0]) {
            ll one = -1, another = -1;
            for (const auto &[u, c] : sm[v]) {
                if (one != -1) break;
                if (c == 0) {
                    one = u;
                }
            }
            for (const auto &[u, c] : smrev[v]) {
                if (another != -1) break;
                if (c == 0) {
                    another = u;
                }
            }
            FOUND = true;
            cout << 3 << endl;
            cout << another << " " << v << " " << one << endl;
            // aa
        } else if (cnt_by_v[v][1] && cnt_by_v_rev[v][1]) {
            // bb
            ll one = -1, another = -1;
            for (const auto &[u, c] : sm[v]) {
                if (one != -1) break;
                if (c == 1) {
                    one = u;
                }
            }
            for (const auto &[u, c] : smrev[v]) {
                if (another != -1) break;
                if (c == 1) {
                    another = u;
                }
            }
            FOUND = true;
            cout << 3 << endl;
            cout << another << " " << v << " " << one << endl;
        }
    };
    for (ll i = 1; i <= n; i += 1) find_aa_bb(find_aa_bb, i);
    if (FOUND) return;
    // abab
    set<ll> sequence;
    vll ans;
    auto find_four = [&] (auto f, ll v) -> void {
        sequence.insert(v);
        ans.push_back(v);
        if (sequence.size() == 5) {
            FOUND = true;
            return;
        }
        for (const auto &[u, c] : sm[v]) if (sequence.find(u) == sequence.end()) {
            f(f, u);
            if (!FOUND) ans.pop_back(), sequence.erase(u);
        }
    };
    for (ll i = 1; i <= n; i += 1) {
        sequence.clear();
        ans.clear();
        find_four(find_four, i);
        if (sequence.size() == 5) {
            cout << 5 << endl;
            cout << ans << endl;
            return;
        }
    }
    cout << -1 << endl;
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