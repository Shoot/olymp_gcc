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

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<string> a(n);
    vll leftmost_snizu(n);
    vll leftmost_sverhu(n);
    vll rightmost_snizu(n);
    vll rightmost_sverhu(n);
    for (ll i = 0; i < n; i += 1) cin >> a[i];
    vvll points(n);
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) {
            if (a[i][j] == '*') points[i].push_back(j);
        }
//        if (points[i].empty() && i > 0 && !points[i-1].empty()) {
//            points[i].push_back(points[i-1].front());
//        }
    }
    ll curr_leftmost = 1e18;
    ll curr_rightmost = -1e18;
    for (ll i = 0; i < n; i += 1) {
        for (ll j = 0; j < m; j += 1) if (a[i][j] == '*') {
            curr_leftmost = min(curr_leftmost, j);
            curr_rightmost = max(curr_rightmost, j);
        }
        leftmost_sverhu[i] = curr_leftmost;
        rightmost_sverhu[i] = curr_rightmost;
    }
    curr_leftmost = 1e18;
    curr_rightmost = -1e18;
    for (ll i = n-1; i >= 0; i -= 1) {
        for (ll j = 0; j < m; j += 1) if (a[i][j] == '*') {
            curr_leftmost = min(curr_leftmost, j);
            curr_rightmost = max(curr_rightmost, j);
        }
        leftmost_snizu[i] = curr_leftmost;
        rightmost_snizu[i] = curr_rightmost;
    }
    vpll shit;
    ll best_used = 1e18;
    for (ll i = 0; i < n; i += 1) if (!points[i].empty()) {
        ll l = points[i].front();
        ll r = points[i].back();
        if (leftmost_sverhu[i] >= l && rightmost_sverhu[i] <= r) {
            // сверху втупую включаем все
            bool vpravo = rightmost_snizu[i] > r;
            bool vlevo = leftmost_snizu[i] < l;
            if (vpravo && vlevo) {
                continue;
            }
            watch(i);
            watch(vpravo);
            watch(vlevo);
            watch(best_used);
            ll VPRAVO = 0;
            vpll my;
            for (ll j = 0; j < i; j += 1) {
                my.push_back(pll(leftmost_sverhu[j], rightmost_sverhu[j]));
                VPRAVO += rightmost_sverhu[j]-leftmost_sverhu[j]+1;
            }
            my.push_back(pll(l,r));
            VPRAVO += r-l+1;
            ll curr_r_1 = r;
            for (ll j = i+1; j < n; j += 1) {
                ll curr_l_1 = leftmost_snizu[j];
                if (!points[j].empty()) curr_r_1 = max(curr_r_1, points[j].back());
                curr_r_1 = min(curr_r_1, rightmost_snizu[j]);
                my.push_back(pll(curr_l_1, curr_r_1));
                watch(curr_r_1);
                VPRAVO += curr_r_1-curr_l_1+1;
            }
            if (VPRAVO < best_used) shit = my, best_used=VPRAVO;
//            for (const auto &[left,right] : my) {
//                cout << left << " " << right << endl;
//            }
            ll VLEVO = 0;
            my.clear();
            for (ll j = 0; j < i; j += 1) {
                my.push_back(pll(leftmost_sverhu[j], rightmost_sverhu[j]));
                VLEVO += rightmost_sverhu[j]-leftmost_sverhu[j]+1;
            }
            my.push_back(pll(l,r));
            VLEVO += r-l+1;
            ll curr_l_2 = l;
            for (ll j = i+1; j < n; j += 1) {
                ll curr_r_2 = rightmost_snizu[j];
                if (!points[j].empty()) curr_l_2 = min(curr_l_2, points[j].front());
                curr_l_2 = max(curr_l_2, leftmost_snizu[j]);
                my.push_back(pll(curr_l_2, curr_r_2));
                VPRAVO += curr_r_2-curr_l_2+1;
            }
            if (VLEVO < best_used) shit = my, best_used=VLEVO;
        }
    }
    vector<string> ans(n);
    for (ll i = 0; i < n; i += 1) {
        ans[i].assign(m, '.');
    }
    if (!shit.empty()) {
        for (ll i = 0; i < n; i += 1) {
            ans[i].assign(m, '.');
            cout << shit[i].first << " " << shit[i].second << endl;
            for (ll j = shit[i].first; j <= shit[i].second; j += 1) {
                ans[i][j] = '*';
            }
        }
    }
    for (const auto &x : ans) {
        cout << x << endl;
    }
}

int32_t main(int32_t argc, char* argv[]) {
//    ifstream cin("distance.in");
//    ofstream cout("distance.out");
    cout << fixed << setprecision(2);
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