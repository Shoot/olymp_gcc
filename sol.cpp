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
    for (auto & x : a) cin >> x;
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
    ll ans = fj0dsq983gf8(right, tree);
    if (left-1 >= 0) {
        ans -= fj0dsq983gf8(left - 1, tree);
    }
    return ans;
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
ll N = 5e6+1;
vll fact(N);
vll ifact(N);
void solve() {
    ll n;
    cin>>n;
    vector<ll>cnt(n+1);
    for(ll i=0;i<n;i++)
    {
        ll x;
        cin>>x;
        cnt[x]++;
    }
    function<ll(ll, ll)> C = [&] (ll n, ll k) {
        if(k==0)return 1ll;
        if(n<0||n<k)return 0ll;
        return mul(mul(fact[n], ifact[n-k]), ifact[k]);
    };
    vector<ll>prev_dp_cnt(n+100),prev_dp_sum(n+100);
    prev_dp_cnt.back()=1;
    for(auto &x:cnt)
    {
        auto suf_cnt_prev_dp=prev_dp_cnt;
        auto suf_sum_prev_dp=prev_dp_sum;
        for(ll i=prev_dp_sum.size()-2;i>=0;i--){
            suf_cnt_prev_dp[i]=sum(suf_cnt_prev_dp[i],suf_cnt_prev_dp[i+1]);
            suf_sum_prev_dp[i]=sum(suf_sum_prev_dp[i],suf_sum_prev_dp[i+1]);
        }
        vector<ll>x_choose_more_or_eq_sum(x+1);
        for(ll i=0;i<=x;i++)x_choose_more_or_eq_sum[i]=C(x,i);
        for(ll i=x-1;i>=0;i--){
            x_choose_more_or_eq_sum[i]=sum(x_choose_more_or_eq_sum[i],x_choose_more_or_eq_sum[i+1]);
        }
        vector<ll>nw_dp_cnt(x+1),nw_dp_sum(x+1);
        for(ll new_minimum_val=0;new_minimum_val<=x;new_minimum_val++)
        {
            if(new_minimum_val+1<prev_dp_sum.size()){ // new_minimum_val+1 existsed, 
                // new_minimum_val+1 or more before
                // we choose EXACTLY new_minimum_val
                nw_dp_cnt[new_minimum_val]=sum(nw_dp_cnt[new_minimum_val],
                                  mul(suf_cnt_prev_dp[new_minimum_val+1],C(x,new_minimum_val)));
                nw_dp_sum[new_minimum_val]=sum(nw_dp_sum[new_minimum_val],
                                  mul(suf_sum_prev_dp[new_minimum_val+1],C(x,new_minimum_val)));
            }
            if(new_minimum_val<prev_dp_sum.size()){ // new_minimum_val existsed
                // exactly new_minimum_val before
                nw_dp_cnt[new_minimum_val]=sum(nw_dp_cnt[new_minimum_val],mul(prev_dp_cnt[new_minimum_val],
                       x_choose_more_or_eq_sum[new_minimum_val])); // min is alr good so we choose anything
                nw_dp_sum[new_minimum_val]=sum(nw_dp_sum[new_minimum_val],mul(prev_dp_sum[new_minimum_val],
                       x_choose_more_or_eq_sum[new_minimum_val])); // min is alr good so we choose anything
                
            }
            nw_dp_sum[new_minimum_val]=sum(nw_dp_sum[new_minimum_val],
                                        mul(nw_dp_cnt[new_minimum_val],new_minimum_val));
        }
        prev_dp_cnt=nw_dp_cnt;
        prev_dp_sum=nw_dp_sum;
    }
    ll ans=0;
    for(auto &x:prev_dp_sum)ans=sum(ans,x);
    cout<<ans<<endl;
}
int32_t main(int32_t argc, char* argv[]) {
    fact[0] = 1;
    ifact[0] = 1;
    for (ll i = 1; i < N; i += 1) {
        fact[i] = mul(fact[i-1], i);
    }
    ifact[N-1] = powm(fact[N-1], MOD-2);
    for (ll i = N-2; i >= 1; i -= 1) {
        ifact[i] = mul(ifact[i+1], i+1);
    }
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