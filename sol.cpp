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
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> distrib(1ll, 200000ll);
constexpr ll MOD7 = 1e9 + 7;
constexpr ll N = 1e6;
constexpr ll maxi_init = 1e9;
/*
void copy_this () {
    ll n; cin >> n;
    ll n, k; cin >> n >> k;
    ll n, q; cin >> n >> q;
    ll a[n]; fo(i, 0, n) cin >> a[i];
    vector<ll> a(n); fo(i, 0, n) cin >> a[i];
}
*/
struct shit {
    ll chet, nechet;
};
struct answer {
    ll less_or_eq_any, less_or_eq_less, less_less_or_eq;
};
ll __query__ (ll index, vector<ll> & tree)  {
    ll sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

ll get(ll left, ll right, vector<ll> & tree) {
    return __query__(right+5, tree) - __query__(left+5 - 1, tree);
}

void add(ll index, ll inc, vector<ll> & tree) {
    index += 5;
    while (index < tree.size()) {
        tree[index] += inc;
        index += index & -index;
    }
}
void solve() {
    ll k; cin >> k;
    ll max_length = 0;
    vector<pair<vector<shit>, vector<shit>>> G (k);
    bool graph_with_no_odd_cycle_exists = false;
    vector<ll> t_nak_nech(N, 0);
    vector<ll> t_nak_chet(N, 0);
    unordered_set<ll> st_nak_chet;
    unordered_set<ll> st_nak_nech;
    fo(ii, 0, k) {
        ll n, m; cin >> n >> m;
        G[ii].first.resize(n);
        G[ii].second.resize(n);
        vector<pair<ll, ll>> a (n+1);
        forr(i, 0, n) {
            a[i].first = maxi_init;
            a[i].second = maxi_init;
        }
        vector<vector<ll>> sm(n+1);
        fo(i, 0, m) {
            ll u, v; cin >> u >> v;
            sm[u].push_back(v);
            sm[v].push_back(u);
        }
        queue<pair<ll, ll>> q;
        q.push(make_pair(1, 0));
        while(!q.empty()) {
            auto tp = q.front();
            q.pop();
            if (tp.second % 2 == 0 && a[tp.first].first == maxi_init) {
                a[tp.first].first = tp.second;
            } else if (tp.second % 2 == 1 && a[tp.first].second == maxi_init) {
                a[tp.first].second = tp.second;
            } else {
                continue;
            }
            for (ll nxt: sm[tp.first]) {
                q.push(make_pair(nxt, tp.second+1));
            }
        }
        vector<ll> t_new_chet(N, 0);
        vector<ll> t_new_nech(N, 0);
        unordered_set<ll> st_new_chet;
        unordered_set<ll> st_new_nech;
        forr(i, 1, n) {
            G[ii].first[i-1] = shit(a[i].first, a[i].second);
            G[ii].second[i-1] = shit(a[i].first, a[i].second);
            max_length = max({max_length, a[i].first, a[i].second});
            //clog << a[i].first << " " << a[i].second << endl;
            if (a[i].first == maxi_init || a[i].second == maxi_init) {
                graph_with_no_odd_cycle_exists = true;
            }
            if (a[i].first != maxi_init) {
                st_new_chet.insert(a[i].first);
                add(a[i].first, 1, t_new_chet);
            }
            if (a[i].second != maxi_init) {
                st_new_nech.insert(a[i].second);
                add(a[i].second, 1, t_new_nech);
            }
        }
        //clog << endl;
        if (ii == 0) {
            swap(t_nak_chet, t_new_chet);
            swap(t_nak_nech, t_new_nech);
            swap(st_nak_chet, st_new_chet);
            swap(st_nak_nech, st_new_nech);
            continue;
        }
        vector<ll> t_nak_deriv_chet(N, 0);
        vector<ll> t_nak_deriv_nech(N, 0);
        unordered_set<ll> st_nak_deriv_chet;
        unordered_set<ll> st_nak_deriv_nech;
        // Из накапл в новый
        for (ll chet_koord: st_nak_chet) {
            st_nak_deriv_chet.insert(chet_koord);
            add(chet_koord,
                get(chet_koord, chet_koord, t_nak_chet)*get(0, chet_koord, t_new_chet),
                t_nak_deriv_chet);
        }
        for (ll nech_koord: st_nak_nech) {
            st_nak_deriv_nech.insert(nech_koord);
            add(nech_koord,
                get(nech_koord, nech_koord, t_nak_nech)*get(0, nech_koord, t_new_nech),
                t_nak_deriv_nech);
        }
        // Из ноого в накапл
        for (ll chet_koord: st_new_chet) {
            st_nak_deriv_chet.insert(chet_koord);
            add(chet_koord,
                get(chet_koord, chet_koord, t_new_chet)*get(0, chet_koord-1, t_nak_chet),
                t_nak_deriv_chet);
        }
        for (ll nech_koord: st_new_nech) {
            st_nak_deriv_nech.insert(nech_koord);
            add(nech_koord,
                get(nech_koord, nech_koord, t_new_nech)*get(0, nech_koord-1, t_nak_nech),
                t_nak_deriv_nech);
        }
        swap(t_nak_deriv_chet, t_nak_chet);
        swap(t_nak_deriv_nech, t_nak_nech);
        st_nak_chet.merge(st_nak_deriv_chet);
        st_nak_nech.merge(st_nak_deriv_nech);
    }
    if (graph_with_no_odd_cycle_exists) {
        //clog << "ez" << endl;
        ll ans = 0;
        for(ll jjjj: st_nak_chet) {
            ans += jjjj*get(jjjj, jjjj, t_nak_chet);
        }
        for(ll jjjj: st_nak_nech) {
            ans += jjjj*get(jjjj, jjjj, t_nak_nech);
        }
        cout << ans%MOD7 << endl;
        return;
    }
    vector<vector<answer>> answ (k, vector<answer> (max_length+1));
    fo(ii, 0, k) {
        vector<ll> first_tree (N, 0);
        vector<ll> second_tree (N, 0);
        sort(all(G[ii].first), [](shit a, shit b) {
            return a.chet < b.chet;
        });
        sort(all(G[ii].second), [](shit a, shit b) {
            return a.nechet < b.nechet;
        });
        ll curr_ans=0;
        ll adding_first = 0;
        ll adding_second = 0;
        while (curr_ans <= max_length) {
//            //clog << "curr_ans=" << curr_ans << endl;
            if (curr_ans%2 == 0) {
                answ[ii][curr_ans].less_less_or_eq = get(0, curr_ans, first_tree);
                while (adding_first < G[ii].first.size() && G[ii].first[adding_first].chet <= curr_ans) {
                    add(G[ii].first[adding_first].nechet, 1, first_tree);
                    adding_first += 1;
                }
                answ[ii][curr_ans].less_or_eq_any = get(0, N-100, first_tree);
//                //clog << "answ[" << ii << "][curr_ans].less_or_eq_any=" << answ[ii][curr_ans].less_or_eq_any << endl;
                answ[ii][curr_ans].less_or_eq_less = get(0, curr_ans-1, first_tree);
//                //clog << "answ[" << ii << "][curr_ans].less_or_eq_less=" << answ[ii][curr_ans].less_or_eq_less << endl;
            } else {
                answ[ii][curr_ans].less_less_or_eq = get(0, curr_ans, second_tree);
                while (adding_second < G[ii].second.size() && G[ii].second[adding_second].nechet <= curr_ans) {
                    add(G[ii].second[adding_second].chet, 1, second_tree);
                    //clog << "+1" << G[ii].second[adding_second].chet << endl;
                    adding_second += 1;
                }
                answ[ii][curr_ans].less_or_eq_any = get(0, N-100, second_tree);
//                //clog << "answ[" << ii << "][curr_ans].less_or_eq_any=" << answ[ii][curr_ans].less_or_eq_any << endl;
                answ[ii][curr_ans].less_or_eq_less = get(0, curr_ans-1, second_tree);
//                //clog << "answ[" << ii << "][curr_ans].less_or_eq_less=" << answ[ii][curr_ans].less_or_eq_less << endl;
            }
            curr_ans += 1;
        }
    }
    ll myans = 0;
    forr(length, 1, max_length) {
        //clog << "--------------------------length=" << length << endl;
        //clog << "--------------------------length=" << length << endl;
        //clog << "--------------------------length=" << length << endl;
        ll ALL = 1;
        ll FIRST_COND_NOT_MET = 1;
        ll SECOND_COND_NOT_MET = 1;
        ll BOTH_CONDs_NOT_MET = 1;
        fo(ii, 0, k) {
            ALL *= answ[ii][length].less_or_eq_any;
            //clog << "all*=" << answ[ii][length].less_or_eq_any << endl;
            FIRST_COND_NOT_MET *= answ[ii][length-2].less_or_eq_any;
            //clog << "first*=" << answ[ii][length-2].less_or_eq_any << endl;
            SECOND_COND_NOT_MET *= answ[ii][length].less_or_eq_less;
            //clog << "second*=" << answ[ii][length].less_or_eq_less << endl;
            BOTH_CONDs_NOT_MET *= answ[ii][length].less_less_or_eq;
            //clog << "both*=" << answ[ii][length].less_less_or_eq << endl;
        }
        //clog << "ALL: " << ALL << endl;
        //clog << "FIRST_COND_NOT_MET: " << FIRST_COND_NOT_MET << endl;
        //clog << "SECOND_COND_NOT_MET: " << SECOND_COND_NOT_MET << endl;
        //clog << "BOTH_CONDs_NOT_MET: " << BOTH_CONDs_NOT_MET << endl;
        myans += length*(ALL - FIRST_COND_NOT_MET - SECOND_COND_NOT_MET + BOTH_CONDs_NOT_MET);
    }
    cout << myans%MOD7 << endl;
}
int32_t main (int32_t argc, char* argv[]) {
    bool use_fast_io = true;
    for (int32_t i = 1; i < argc; ++i)
        if (string(argv[i]) == "-local-no-fast-io") {
            use_fast_io = false;
//            cout << "No fastIO" << endl;
            break;
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
    while (tt--) solve();
    return 0;
}