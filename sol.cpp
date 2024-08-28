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
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required
using namespace std;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(100, 900);
constexpr ll N = (ll)(2e5+1);
//constexpr ll MOD = 998244353;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, m; cin >> n >> m;
    ll q; cin >> q;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
ll tot = 0;
ordered_set<ll> su_st;
ordered_set<ll> razn_pol_st;
ordered_set<ll> razn_otr_st;
void su_shit (ll l, ll r) {
    tot -= (ll)su_st.order_of_key(r+1);
    clog << "Доб su до " << r+1 << endl;
    tot += (ll)su_st.order_of_key(l);
    clog << "Отн su до " << l << endl;
}
void solve () {
    ll n, m; cin >> n >> m;
    ll q; cin >> q;
//    vector<ll> razn_pol (m);
//    vector<ll> razn_otr (n);
//    vector<ll> su (m+n+1);
//    fo(r_p, 0, n) {
//        razn_pol[r_p] = min(n-r_p, m);
//        clog << "r_p: " << r_p << " = " << razn_pol[r_p] << endl;
//    }
//    fo(r_o, 1, m) {
//        razn_otr[r_o] = min(m-r_o, n);
//        clog << "r_o: " << r_o << " = " << razn_otr[r_o] << endl;
//    }
//    forr(s, 2, m+n) {
//        if (s > max(n, m)) {
//            su[s] = min(n, m) - (s - max(m, n)) + 1;
//        } else {
//            su[s] = min(s-1, min(n, m));
//        }
//        clog << "su: " << s << " = " << su[s] << endl;
//    }

    while (q--) {
        char type; cin >> type;
        if (type == '+') {
            ll su_add; cin >> su_add;
            clog << "su: " << su_add << endl;
            su_st.insert(su_add);
            if (su_add > max(n, m)) {
                tot += min(n, m) - (su_add - max(m, n)) + 1;
            } else {
                tot += min(su_add-1, min(n, m));
            }
            if (su_add <= min(n, m)+1) {
                tot -= (ll)razn_otr_st.order_of_key(su_add-2+1);
                clog << "Отр до " << su_add-2+1 << endl;
                tot -= (ll)razn_pol_st.order_of_key(su_add-2+1);
                clog << "Пол до " << su_add-2+1 << endl;
            } else if (su_add <= max(n, m)+1) {
                ll d = su_add-(min(n, m)+1);
                ll base = min(n, m)+1-2;
                tot -= (ll)razn_otr_st.order_of_key(base-d+1);
                clog << "Отр до " << base-d+1 << endl;
                tot -= (ll)razn_pol_st.order_of_key(base+d+1);
                clog << "Пол до " << base+d+1 << endl;
            } else {
                ll shit_d = max(n, m)+1-(min(n, m)+1);
                ll shit_base = min(n, m)+1-2;
                ll base_otr = -(shit_base-shit_d);
                ll base_pol = shit_base+shit_d;
                ll d = su_add-(max(n, m)+1);
                ll l = base_otr+d;
                ll r = base_pol-d;
                if (l < 0) {
                    tot -= (ll)razn_otr_st.order_of_key(-l+1);
                    clog << "Добавляем пересечения отр до " << -l+1 << endl;
                } else {
                    tot += (ll)razn_pol_st.order_of_key(l);
                    clog << "Отнимаем пересечения пол до " << l << endl;
                }
                if (r > 0) {
                    tot -= (ll)razn_pol_st.order_of_key(r+1);
                    clog << "Добавляем пересечения пол до " << r+1 << endl;
                } else {
                    tot += (ll)razn_otr_st.order_of_key(-l);
                    clog << "Отнимаем пересечения отр до " << -l << endl;
                }
            }
        } else {
            ll razn_add; cin >> razn_add;
            clog << "raz: " << razn_add << endl;
            if (razn_add < 0) {
                tot += min(m-(-razn_add), n);
                razn_otr_st.insert(-razn_add);
            } else {
                tot += min(n-razn_add, m);
                razn_pol_st.insert(razn_add);
            }
            if (n <= m) {
                if (razn_add >= 0) {
                    su_shit(2+razn_add, 2*min(n, m)-razn_add);
                } else if (razn_add < 0 && razn_add >= -(max(n, m)-min(n, m))) {
                    su_shit(2-razn_add, 2*min(n, m)-razn_add);
                } else {
                    ll d = -(max(n, m)-min(n, m)) - razn_add;
                    assert(d > 0);
                    su_shit(2+max(n, m)-min(n, m)+d, 2*min(n, m)+max(n, m)-min(n, m)-d);
                }
            } else {
                if (razn_add < 0) {

                }
            }
        }
    }
    cout << tot << endl;
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            clog << "No fastIO" << endl;
            break;
        }
    if (use_fast_io) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        clog.tie(nullptr);
        cerr.tie(nullptr);
        clog.tie(nullptr);
    }
    ll tt = 1;
    while (tt--) solve();
    return 0;
}