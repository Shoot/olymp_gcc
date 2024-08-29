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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib_1(0, 1);
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
ordered_set<ll> su_st_ch;
ordered_set<ll> su_st_nech;
ordered_set<ll> razn_pol_st_ch;
ordered_set<ll> razn_pol_st_nech;
ordered_set<ll> razn_otr_st_ch;
ordered_set<ll> razn_otr_st_nech;
void su_shit_ch (ll l, ll r) {
    tot -= (ll)su_st_ch.order_of_key(r+1);
    clog << "Доб su до " << r+1 << endl;
    tot += (ll)su_st_ch.order_of_key(l);
    clog << "Отн su до " << l << endl;
}
void su_shit_nech (ll l, ll r) {
    tot -= (ll)su_st_nech.order_of_key(r+1);
    clog << "Доб su до " << r+1 << endl;
    tot += (ll)su_st_nech.order_of_key(l);
    clog << "Отн su до " << l << endl;
}
void solve () {
    ll n, m;
    cin >> n >> m;
//    bool slow[n][m];
//    fo(i, 0, n) {
//        fo(j, 0, m) {
//            slow[i][j] = false;
//        }
//    }
    ll q;
    cin >> q;
    unordered_set<ll> was_sum;
    unordered_set<ll> was_raz;
    fo(iii, 0, q) {
        ll _tot = tot;
        char type;
        cin >> type;
        ll su_add;
        ll razn_add;
        if (type == '+') {
            cin >> su_add;
            clog << "su: " << su_add << endl;
            if (was_sum.contains(su_add)) {
                clog << "skip" << endl;
                continue;
            }
            was_sum.insert(su_add);
            ll dlina;
            if (su_add > max(n, m)) {
                dlina = min(n, m) - (su_add - max(m, n)) + 1;
            } else {
                dlina = min(su_add-1, min(n, m));
            }
            clog << "dlina: " << dlina << endl;
            tot += dlina;
            if (su_add % 2 == 0) {
                clog << "THIS IS CH" << endl;
                su_st_ch.insert(su_add);
                if (n <= m) {
                    if (su_add <= min(n, m) + 1) {
                        tot -= (ll) razn_otr_st_ch.order_of_key(su_add - 2 + 1);
                        clog << "(1)Отр до " << su_add - 2 + 1 << endl;
                        tot -= (ll) razn_pol_st_ch.order_of_key(su_add - 2 + 1);
                        clog << "(1)Пол до " << su_add - 2 + 1 << endl;
                    } else {
                        ll l, r;
                        if (su_add <= max(n, m) + 1) {
                            ll d = su_add - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base - d;
                            r = base - d;
                        } else {
                            // отталкиваемся от su_add == (max(n, m) + 1)
                            ll d = max(n, m) + 1 - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base - d;
                            r = base - d;
                            l += su_add - (max(n, m) + 1);
                            r -= su_add - (max(n, m) + 1);
                        }
                        if (l <= 0) {
                            ll x = (ll)razn_otr_st_ch.order_of_key(-l + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "97. Добавляем отр чт до " << -l+1 << ": " << x << endl;
                        } else {
                            ll x = (ll)razn_pol_st_ch.order_of_key(l);
                            assert(x >= 0);
                            tot += x;
                            clog << "98. Отнимаем пол чт до " << l << ": " << x << endl;
                        }
                        if (r >= 0) {
                            ll x = (ll) razn_pol_st_ch.order_of_key(r + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "99. Добавляем пол чт до " << r+1 << ": " << x << endl;
                        } else {
                            ll x = (ll) razn_otr_st_ch.order_of_key(-r);
                            assert(x >= 0);
                            tot += x;
                            clog << "100. Отнимаем отр чт до " << -r << ": " << x << endl;
                        }
                    }
                } else {
                    if (su_add <= min(n, m) + 1) {
                        tot -= (ll) razn_otr_st_ch.order_of_key(su_add - 2 + 1);
                        clog << "(1)Отр до " << su_add - 2 + 1 << endl;
                        tot -= (ll) razn_pol_st_ch.order_of_key(su_add - 2 + 1);
                        clog << "(1)Пол до " << su_add - 2 + 1 << endl;
                    } else {
                        ll l, r;
                        if (su_add <= max(n, m) + 1) {
                            ll d = su_add - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base + d;
                            r = base + d;
                        } else {
                            // отталкиваемся от su_add == (max(n, m) + 1)
                            ll d = max(n, m) + 1 - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base + d;
                            r = base + d;
                            l += su_add - (max(n, m) + 1);
                            r -= su_add - (max(n, m) + 1);
                        }
                        if (l <= 0) {
                            ll x = (ll)razn_otr_st_ch.order_of_key(-l + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "245. Добавляем отр чт до " << -l+1 << ": " << x << endl;
                        } else {
                            ll x = (ll)razn_pol_st_ch.order_of_key(l);
                            assert(x >= 0);
                            tot += x;
                            clog << "250. Отнимаем пол чт до " << l << ": " << x << endl;
                        }
                        if (r >= 0) {
                            ll x = (ll) razn_pol_st_ch.order_of_key(r + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "256. Добавляем пол чт до " << r+1 << ": " << x << endl;
                        } else {
                            ll x = (ll) razn_otr_st_ch.order_of_key(-l);
                            assert(x >= 0);
                            tot += x;
                            clog << "261. Отнимаем отр чт до " << -r << ": " << x << endl;
                        }
                    }
                }
            } else {
                clog << "THIS IS NECH" << endl;
                su_st_nech.insert(su_add);
                if (n <= m) {
                    if (su_add <= min(n, m) + 1) {
                        tot -= (ll) razn_otr_st_nech.order_of_key(su_add - 2 + 1);
                        clog << "(1)Отр до " << su_add - 2 + 1 << endl;
                        tot -= (ll) razn_pol_st_nech.order_of_key(su_add - 2 + 1);
                        clog << "(1)Пол до " << su_add - 2 + 1 << endl;
                    } else {
                        ll l, r;
                        if (su_add <= max(n, m) + 1) {
                            ll d = su_add - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base - d;
                            r = base - d;
                        } else {
                            // отталкиваемся от su_add == (max(n, m) + 1)
                            ll d = max(n, m) + 1 - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base - d;
                            r = base - d;
                            l += su_add - (max(n, m) + 1);
                            r -= su_add - (max(n, m) + 1);
                        }
                        if (l <= 0) {
                            ll x = (ll)razn_otr_st_nech.order_of_key(-l + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "207. Добавляем отр нч до " << -l+1 << ": " << x << endl;
                        } else {
                            ll x = (ll)razn_pol_st_nech.order_of_key(l);
                            assert(x >= 0);
                            tot += x;
                            clog << "212. Отнимаем пол нч до " << l << ": " << x << endl;
                        }
                        if (r >= 0) {
                            ll x = (ll) razn_pol_st_nech.order_of_key(r + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "218. Добавляем пол нч до " << r+1 << ": " << x << endl;
                        } else {
                            ll x = (ll) razn_otr_st_nech.order_of_key(-r);
                            assert(x >= 0);
                            tot += x;
                            clog << "223. Отнимаем отр нч до " << -r << ": " << x << endl;
                        }
                    }
                } else {
                    if (su_add <= min(n, m) + 1) {
                        tot -= (ll) razn_otr_st_nech.order_of_key(su_add - 2 + 1);
                        clog << "(1)Отр до " << su_add - 2 + 1 << endl;
                        tot -= (ll) razn_pol_st_nech.order_of_key(su_add - 2 + 1);
                        clog << "(1)Пол до " << su_add - 2 + 1 << endl;
                    } else {
                        ll l, r;
                        if (su_add <= max(n, m) + 1) {
                            ll d = su_add - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base + d;
                            r = base + d;
                            // xz!!!!
                        } else {
                            // отталкиваемся от su_add == (max(n, m) + 1)
                            ll d = max(n, m) + 1 - (min(n, m) + 1);
                            ll base = min(n, m) + 1 - 2;
                            l = -base + d;
                            r = base + d;
                            // xz!!!!!
                            l += su_add - (max(n, m) + 1);
                            r -= su_add - (max(n, m) + 1);
                        }

                        if (l <= 0) {
                            ll x = (ll)razn_otr_st_nech.order_of_key(-l + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "245. Добавляем отр нч до " << -l+1 << ": " << x << endl;
                        } else {
                            ll x = (ll)razn_pol_st_nech.order_of_key(l);
                            assert(x >= 0);
                            tot += x;
                            clog << "250. Отнимаем пол нч до " << l << ": " << x << endl;
                        }
                        if (r >= 0) {
                            ll x = (ll) razn_pol_st_nech.order_of_key(r + 1);
                            assert(x >= 0);
                            tot -= x;
                            clog << "256. Добавляем пол нч до " << r+1 << ": " << x << endl;
                        } else {
                            ll x = (ll) razn_otr_st_nech.order_of_key(-r);
                            assert(x >= 0);
                            tot += x;
                            clog << "261. Отнимаем отр нч до " << -r << ": " << x << endl;
                        }
                    }
                }
            }
        } else {
            cin >> razn_add;
            clog << "raz: " << razn_add << endl;
            if(was_raz.contains(razn_add)) {
                clog << "skip" << endl;
                continue;
            }
            was_raz.insert(razn_add);
            ll dlina;
            if (razn_add < 0) {
                dlina = min(m-(-razn_add), n);
            } else {
                dlina = min(n-razn_add, m);
            }
            clog << "dlina: " << dlina << endl;
            tot += dlina;
            if (abs(razn_add) % 2 == 0) {
                if (razn_add < 0) {
                    razn_otr_st_ch.insert(-razn_add);
                    clog << ".280 " << -razn_add << endl;
                    clog << ".280 " << razn_otr_st_ch.order_of_key(-razn_add+1) << endl;
                } else {
                    razn_pol_st_ch.insert(razn_add);
                    clog << ".283 " << razn_add << endl;
                    clog << ".283 " << razn_pol_st_ch.order_of_key(razn_add+1) << endl;
                }
                if (n <= m) {
                    if (razn_add >= 0) {
                        su_shit_ch(2+razn_add, 2*min(n, m)-razn_add);
                    } else if (razn_add < 0 && razn_add >= -(max(n, m)-min(n, m))) {
                        su_shit_ch(2-razn_add, 2*min(n, m)-razn_add);
                    } else {
                        ll d = -(max(n, m)-min(n, m)) - razn_add;
                        assert(d > 0);
                        su_shit_ch(2+max(n, m)-min(n, m)+d, 2*min(n, m)+max(n, m)-min(n, m)-d);
                    }
                } else {
                    if (razn_add < 0) {
                        su_shit_ch(2-razn_add, 2*min(n, m)+razn_add);
                    } else if (razn_add <= max(n, m)-min(n, m)) {
                        su_shit_ch(2+razn_add, 2*min(n, m)+razn_add);
                    } else {
                        ll d = razn_add-(max(n, m)-min(n, m));
                        su_shit_ch(2+max(n, m)-min(n, m)+d, 2*min(n, m)+max(n, m)-min(n, m)-d);
                    }
                }
            } else {
                if (razn_add < 0) {
                    razn_otr_st_nech.insert(-razn_add);
                    clog << ".10101 " << -razn_add << endl;
                    clog << ".11111 " << razn_otr_st_nech.order_of_key(-razn_add+1) << endl;
                } else {
                    razn_pol_st_nech.insert(razn_add);
                    clog << ".1111110 " << razn_add << endl;
                    clog << ".1111111 " << razn_pol_st_nech.order_of_key(razn_add+1) << endl;
                }
                if (n <= m) {
                    if (razn_add >= 0) {
                        su_shit_nech(2+razn_add, 2*min(n, m)-razn_add);
                    } else if (razn_add < 0 && razn_add >= -(max(n, m)-min(n, m))) {
                        su_shit_nech(2-razn_add, 2*min(n, m)-razn_add);
                    } else {
                        ll d = -(max(n, m)-min(n, m)) - razn_add;
                        assert(d > 0);
                        su_shit_nech(2+max(n, m)-min(n, m)+d, 2*min(n, m)+max(n, m)-min(n, m)-d);
                    }
                } else {
                    if (razn_add < 0) {
                        su_shit_nech(2-razn_add, 2*min(n, m)+razn_add);
                    } else if (razn_add <= max(n, m)-min(n, m)) {
                        su_shit_nech(2+razn_add, 2*min(n, m)+razn_add);
                    } else {
                        ll d = razn_add-(max(n, m)-min(n, m));
                        su_shit_nech(2+max(n, m)-min(n, m)+d, 2*min(n, m)+max(n, m)-min(n, m)-d);
                    }
                }
            }
        }
        clog << "dtot: " << tot-_tot << endl;
    }
    assert(tot > 0 || q == 0);
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