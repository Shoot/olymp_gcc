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
uniform_int_distribution<ll> distrib(0ll, 10ll);
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 1e9+7;
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
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; for (ll i=0; i < n; i+=1) cin >> a[i];
    vector<ll> a(n); for (ll i=0; i < n; i+=1) cin >> a[i];
}
*/
ll dp[11][2][2];
string S, L, R;
ll do_dp (ll i, ll xl, ll xr) { // xl — S гарантированно больше L, xr — S меньше R
    if (i == S.size()) return xl==1;
    if (dp[i][xl][xr] != -1) {
        return dp[i][xl][xr];
    }
    vector<ll> possible_digits;
    if (S[i] == '?') {
//        if (i != 0 || S.size() == 1)
            possible_digits.push_back(0);
        for (ll j = 1; j <= 9; j += 1) {
            possible_digits.push_back(j);
        }
    } else {
        possible_digits.push_back(S[i]-'0');
    }
    ll this_digit_inL = L[i]-'0';
    ll this_digit_inR = R[i]-'0';
    ll su = 0;
    for (const auto &possible_digit : possible_digits) {
        if (possible_digit < this_digit_inL && !xl) continue;
        if (possible_digit > this_digit_inR && !xr) continue;
        bool nxl = xl || possible_digit > this_digit_inL;
        bool nxr = xr || possible_digit < this_digit_inR;
        su += do_dp(i+1, nxl, nxr);
    }
    return su;
}
void solve() {
    auto a_less_than_b = [] (string a, string b) {
        if (a.size() != b.size()) {
            return a.size()<b.size();
        }
        return a<b;
    };
    ll n, q; cin >> n >> q;
    vector<string> a(n);
    for (auto &x : a) {
        cin >> x;
        reverse(all(x));
        while (x.size() != 10) x.push_back('0');
        reverse(all(x));
    }
    sort(all(a), a_less_than_b);
    vll first_by_number_of_digits(11, 1e9);
    vll last_by_number_of_digits(11, -1);
    for (ll i = 0; i < n; i += 1) {
        first_by_number_of_digits[a[i].size()] = min(first_by_number_of_digits[a[i].size()], i);
        last_by_number_of_digits[a[i].size()] = max(last_by_number_of_digits[a[i].size()], i);
    }
//    print(a);
    ll ans = 0;
    auto ask = [&] (string s) {
        reverse(all(s));
        assert(!s.empty());
        assert(s.size() < last_by_number_of_digits.size());
//        cout << "asked " << s << ", prevans below" << endl;
//        cout << ans << endl;
        S = s;
        ll first = first_by_number_of_digits[s.size()];
        ll last = last_by_number_of_digits[s.size()];
        if (last == -1) {
            ll nxt = 1'000'000;
            for (ll j = s.size(); j < 11; j += 1) {
                if (last_by_number_of_digits[j] != -1) {
                    nxt = first_by_number_of_digits[j];
                    break;
                }
            }
            if (nxt == 1'000'000) return ;
            ll mnozh = n-nxt;
            ll kol = 1;
//            if (S[0] == '?' && S.size() != 1) kol *= 9;
//            if (S[0] == '?' && S.size() == 1) kol *= 10;
            for (ll i = 0; i < S.size(); i += 1) {
                if (S[i] == '?') kol *= 10;
            }
            ans += kol*mnozh;
            return;
        }
        ll mnozh = n-first;
        memset(dp, -1, sizeof(dp));
        L = string(S.size(), '\0');
        R = a[first];
        ans += mnozh*do_dp(0, 0, 0);
        for (ll r = first+1; r <= last; r += 1) {
            memset(dp, -1, sizeof(dp));
            mnozh -= 1;
            L = a[r-1];
            R = a[r];
            ans += mnozh*do_dp(0, 0, 0);
        }
        mnozh -= 1;
        if (mnozh != 0) {
            memset(dp, -1, sizeof(dp));
            assert(mnozh > 0);
            L = a[last];
            R = string(S.size(), '9');
            ans += mnozh*do_dp(0, 0, 0);
        }
//        cout << "currans = " << ans << endl;
    };
    for (ll i = 0; i < q; i += 1) {
        string s; cin >> s;
        reverse(all(s));
        while (s.size() != 10) s.push_back('0');
        ans = 0;
        ask(s);
//        while (!s.empty() && s.back() == '?') {
//            s.pop_back();
//            if (!s.empty()) ask(s);
//        }
        cout << ans << endl;
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
