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
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math,trapv")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,no-stack-protector,fast-math")
#endif
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<__int128> distrib(1ll, 200000ll);
constexpr __int128 MOD7 = 1e9 + 7;
constexpr __int128 N = 2e5+40;
constexpr __int128 maxi_init = 1e9;
/*
void copy_this () {
    __int128 n; cin >> n;
    __int128 n, k; cin >> n >> k;
    __int128 n, q; cin >> n >> q;
    __int128 a[n]; fo(i, 0, n) cin >> a[i];
    vector<__int128> a(n); fo(i, 0, n) cin >> a[i];
}
*/
struct shit {
    ll chet, nechet;
};
struct answer {
    ll less_or_eq__any, less__any, less_or_eq__less, less__less_or_eq;
};

ll OP_SHIT = 0;

__int128 __query__ (ll index, vector<__int128> & tree)  {
    __int128 sum = 0;
    while (index > 0) {
        OP_SHIT += 1;
        assert(OP_SHIT < 5e7);
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

ll __queryll__ (ll index, vector<ll> & tree)  {
    ll sum = 0;
    while (index > 0) {
        OP_SHIT += 1;
        assert(OP_SHIT < 5e7);
        sum += tree[index];
        index -= index & -index;
    }
    return sum;
}

__int128 get(ll left, ll right, vector<__int128> & tree) {
    return __query__(right+5, tree) - __query__(left+5 - 1, tree);
}

ll getll(ll left, ll right, vector<ll> & tree) {
    return __queryll__(right+5, tree) - __queryll__(left+5 - 1, tree);
}


void add(ll index, __int128 inc, vector<__int128> & tree) {
    index += 5;
    while (index < tree.size()) {
        OP_SHIT += 1;
        assert(OP_SHIT < 5e7);
        tree[index] += inc;
        index += index & -index;
    }
}

void addll(ll index, ll inc, vector<ll> & tree) {
    index += 5;
    while (index < tree.size()) {
        OP_SHIT += 1;
        assert(OP_SHIT < 5e7);
        tree[index] += inc;
        index += index & -index;
    }
}

void solve() {
    auto start = chrono::high_resolution_clock::now();
    ll k=2;
    cin >> k;
    vector<pair<vector<shit>, vector<shit>>> G (k);
    bool graph_with_no_odd_cycle_exists = false;
    vector<ll> max_length (k, 0);
    ll absolute_max_length = 0;
    vector<ll> nn(k);
    fo(ii, 0, k) {
        ll n=10, m=15;
        cin >> n >> m;
        nn[ii] = n;
        G[ii].first.resize(n);
        G[ii].second.resize(n);
        vector<pair<ll, ll>> a (n+1);
        forr(i, 0, n) {
            a[i].first = maxi_init;
            a[i].second = maxi_init;
        }
        vector<vector<ll>> sm(n+1);
        fo(i, 0, m) {
            ll u=1, v=1;
            cin >> u >> v;
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
        forr(i, 1, n) {
            G[ii].first[i-1] = shit(a[i].first, a[i].second);
            G[ii].second[i-1] = shit(a[i].first, a[i].second);
            max_length[ii] = max({max_length[ii], a[i].first, a[i].second});
//            clog << a[i].first << " " << a[i].second << endl;
            if (a[i].first == maxi_init || a[i].second == maxi_init) {
                graph_with_no_odd_cycle_exists = true;
            }
            max_length[ii] += 1;
        }
        absolute_max_length = max(absolute_max_length, max_length[ii]);
    }
    if (graph_with_no_odd_cycle_exists) {
        vector<__int128> t_nak_nech(N, 0);
        vector<__int128> t_nak_chet(N, 0);
        unordered_set<ll> st_nak_chet;
        unordered_set<ll> st_nak_nech;
        fo(ii, 0, k) {
            vector<__int128> t_new_chet(N, 0);
            vector<__int128> t_new_nech(N, 0);
            unordered_set<ll> st_new_chet;
            unordered_set<ll> st_new_nech;
            forr(i, 1, nn[ii]) {
                if (G[ii].first[i-1].chet != maxi_init) {
                    st_new_chet.insert(G[ii].first[i-1].chet);
                    add(G[ii].first[i-1].chet, 1, t_new_chet);
                }
                if (G[ii].first[i-1].nechet != maxi_init) {
                    st_new_nech.insert(G[ii].first[i-1].nechet);
                    add(G[ii].first[i-1].nechet, 1, t_new_nech);
                }
            }
            if (ii == 0) {
                swap(t_nak_chet, t_new_chet);
                swap(t_nak_nech, t_new_nech);
                swap(st_nak_chet, st_new_chet);
                swap(st_nak_nech, st_new_nech);
                continue;
            }
            vector<__int128> t_nak_deriv_chet(N, 0);
            vector<__int128> t_nak_deriv_nech(N, 0);
            unordered_set<ll> st_nak_deriv_chet = st_nak_chet;
            unordered_set<ll> st_nak_deriv_nech = st_nak_nech;
            // Из накапл в новый
            for (ll chet_koord: st_nak_chet) {
                add(chet_koord,
                    (get(chet_koord, chet_koord, t_nak_chet)*get(0, chet_koord, t_new_chet))%MOD7,
                    t_nak_deriv_chet);
            }
            for (ll nech_koord: st_nak_nech) {
                add(nech_koord,
                    (get(nech_koord, nech_koord, t_nak_nech)*get(0, nech_koord, t_new_nech))%MOD7,
                    t_nak_deriv_nech);
            }
            // Из ноого в накапл
            for (ll chet_koord: st_new_chet) {
                st_nak_deriv_chet.insert(chet_koord);
                add(chet_koord,
                    (get(chet_koord, chet_koord, t_new_chet)*get(0, chet_koord-1, t_nak_chet))%MOD7,
                    t_nak_deriv_chet);
            }
            for (ll nech_koord: st_new_nech) {
                st_nak_deriv_nech.insert(nech_koord);
                add(nech_koord,
                    (get(nech_koord, nech_koord, t_new_nech)*get(0, nech_koord-1, t_nak_nech))%MOD7,
                    t_nak_deriv_nech);
            }
            swap(t_nak_deriv_chet, t_nak_chet);
            swap(t_nak_deriv_nech, t_nak_nech);
            st_nak_chet.merge(st_nak_deriv_chet);
            st_nak_nech.merge(st_nak_deriv_nech);
        }
        clog << "ez" << endl;
        __int128 ans = 0;
        for(ll jjjj: st_nak_chet) {
            ans = (ans+(jjjj*get(jjjj, jjjj, t_nak_chet))%MOD7)%MOD7;
        }
        for(ll jjjj: st_nak_nech) {
            ans = (ans+(jjjj*get(jjjj, jjjj, t_nak_nech))%MOD7)%MOD7;
        }
        cout << (ll)ans << endl;
        return;
    }
    vector<vector<answer>> answ (k);
    fo(ii, 0, k) {
//        auto stop = chrono::high_resolution_clock::now();
//        auto duration_all = duration_cast<chrono::microseconds>(stop - start);
//        if (duration_all.count() > 2e5) {
//            assert(false);
//        }
        answ[ii].resize(max_length[ii]+1);
        vector<ll> first_tree (max_length[ii]+20, 0);
        vector<ll> second_tree (max_length[ii]+20, 0);
        sort(all(G[ii].first), [](shit a, shit b) {
            return a.chet < b.chet;
        });
        sort(all(G[ii].second), [](shit a, shit b) {
            return a.nechet < b.nechet;
        });
        ll curr_ans=0;
        ll adding_first = 0;
        ll adding_second = 0;
        while (curr_ans <= max_length[ii]) {
            if (curr_ans%2 == 0) {
                answ[ii][curr_ans].less__any = getll(0, max_length[ii]+2, first_tree);
                answ[ii][curr_ans].less__less_or_eq = getll(0, curr_ans, first_tree);
                while (adding_first < G[ii].first.size() && G[ii].first[adding_first].chet <= curr_ans) {
                    addll(G[ii].first[adding_first].nechet, 1, first_tree);
                    adding_first += 1;
                }
                answ[ii][curr_ans].less_or_eq__any = getll(0, max_length[ii]+2, first_tree);
                answ[ii][curr_ans].less_or_eq__less = getll(0, curr_ans-1, first_tree);
            } else {
                answ[ii][curr_ans].less__any = getll(0, max_length[ii]+2, second_tree);
                answ[ii][curr_ans].less__less_or_eq = getll(0, curr_ans, second_tree);
                while (adding_second < G[ii].second.size() && G[ii].second[adding_second].nechet <= curr_ans) {
                    addll(G[ii].second[adding_second].chet, 1, second_tree);
                    adding_second += 1;
                }
                answ[ii][curr_ans].less_or_eq__any = getll(0, max_length[ii]+2, second_tree);
                answ[ii][curr_ans].less_or_eq__less = getll(0, curr_ans-1, second_tree);
            }
            curr_ans += 1;
        }
    }
    __int128 myans = 0;
    unordered_set<ll> relevant_ii;
    fo(ii, 0, k) {
        relevant_ii.insert(ii);
    }
    __int128 base_ALL = 1;
    __int128 base_FIRST_COND_NOT_MET = 1;
    __int128 base_SECOND_COND_NOT_MET = 1;
    __int128 base_BOTH_CONDs_NOT_MET = 1;
    __int128 BASIC_OP_COUNTER = 0;
    for(ll length=1; length<=absolute_max_length; length+=1) {
//        clog << "--------------------------length=" << length << endl;
//        clog << "--------------------------length=" << length << endl;
//        clog << "--------------------------length=" << length << endl;
        __int128 ALL = base_ALL;
        __int128 FIRST_COND_NOT_MET = base_FIRST_COND_NOT_MET;
        __int128 SECOND_COND_NOT_MET = base_SECOND_COND_NOT_MET;
        __int128 BOTH_CONDs_NOT_MET = base_BOTH_CONDs_NOT_MET;
        for(auto ii: relevant_ii) {
            BASIC_OP_COUNTER += 1;
            ALL = (ALL*answ[ii][min(length, max_length[ii])].less_or_eq__any)%MOD7;
//            clog << "all*=" << answ[ii][length].less_or_eq__any << endl;
            FIRST_COND_NOT_MET = (FIRST_COND_NOT_MET*answ[ii][min(length, max_length[ii])].less__any)%MOD7;
//            clog << "first*=" << answ[ii][length].less__any << endl;
            SECOND_COND_NOT_MET = (SECOND_COND_NOT_MET*answ[ii][min(length, max_length[ii])].less_or_eq__less)%MOD7;
//            clog << "second*=" << answ[ii][length].less_or_eq__less << endl;
            BOTH_CONDs_NOT_MET = (BOTH_CONDs_NOT_MET*answ[ii][min(length, max_length[ii])].less__less_or_eq)%MOD7;
//            clog << "both*=" << answ[ii][length].less__less_or_eq << endl;
        }
        if (length < 5 || length < 100 && length % 5 == 0 || length % 100 == 0) {
            vector<ll> erases;
            for(auto ii: relevant_ii) {
                if (length > max_length[ii]) {
                    erases.push_back(ii);
                }
            }
            for (auto erasee: erases) {
                relevant_ii.erase(erasee);
                base_ALL = (base_ALL*answ[erasee][max_length[erasee]].less_or_eq__any)%MOD7;
                base_FIRST_COND_NOT_MET = (base_FIRST_COND_NOT_MET*answ[erasee][max_length[erasee]].less__any)%MOD7;
                base_SECOND_COND_NOT_MET = (base_SECOND_COND_NOT_MET*answ[erasee][max_length[erasee]].less_or_eq__less)%MOD7;
                base_BOTH_CONDs_NOT_MET = (base_BOTH_CONDs_NOT_MET*answ[erasee][max_length[erasee]].less__less_or_eq)%MOD7;
            }
        }
//        clog << "ALL: " << ALL << endl;
//        clog << "FIRST_COND_NOT_MET: " << FIRST_COND_NOT_MET << endl;
//        clog << "SECOND_COND_NOT_MET: " << SECOND_COND_NOT_MET << endl;
//        clog << "BOTH_CONDs_NOT_MET: " << BOTH_CONDs_NOT_MET << endl;
        myans = (myans+length*(ALL - FIRST_COND_NOT_MET - SECOND_COND_NOT_MET + BOTH_CONDs_NOT_MET + 10*MOD7))%MOD7;
    }
    cout << (ll)myans << endl;
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
    __int128 tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}