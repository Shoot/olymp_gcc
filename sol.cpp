//#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
//#define double long double
#define YES(x) cout << (x?"YES\n":"NO\n")
#define ALICE(x) cout << (x?"Alice\n":"Bob\n")
#define BOB(x) cout << (x?"Bob\n":"Alice\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
constexpr int INF = 1e18;
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
//    int T;
//    cin >> T;
//    for (int tt = 0; tt < T; tt += 1) {
//    }
    int n;
    cin >> n;
    vector<int> _2(n+1, 1);
    for (int i = 1; i <= n; i += 1) {
        _2[i] = _2[i-1]*2%MOD;
    }
    struct Node {
        int val=0;
        int subtree_sum=0;
        int dp=0;
        vector<int> ch;
        Node() {
            ch.assign(2, -1);
        }
    };
    vector<Node> nds;
    nds.push_back({});
    auto mknode = [&] () -> int {
        nds.push_back({});
        return nds.size()-1;
    };
    auto gtsz = [&] (int u) -> int {
        return u == -1 ? 0 : nds[u].subtree_sum;
    };
    auto updsz = [&] (int u) -> void {
        nds[u].subtree_sum = nds[u].val;
        for (const auto &x : nds[u].ch) {
            nds[u].subtree_sum += gtsz(x);
        }
    };
    auto upd_dp = [&] (int u) -> void { // returns колво способов выбрать подмножество строк
        // из поддерева в боре чтобы все ок было для всех infinity строк которые имеют u как префикс
        int ret = 1;
        for (const auto &x : nds[u].ch) { // в каждом из сыновей
            (ret *= (x==-1?0:nds[x].dp)) %= MOD;
        }
//        ret += (1ll << (nds[u].subtree_sum-nds[u].val)) * ((1ll << nds[u].val)-1/*отняли тк пустое не подходит*/); // что-то в родителе
        (ret += _2[nds[u].subtree_sum-nds[u].val] * (_2[nds[u].val]-1) % MOD) %= MOD;
        nds[u].dp = ret;
    };
    for (int i = 0; i < n; i += 1) {
        // dp[u] = П_{(v in ch[u])}dp[v]  +   (u != 0)*(2^(subtree_sz[u]-1))
        string s;
        cin >> s;
        auto dfs = [&] (auto f, int u, int j) -> void {
            if (j == s.size()) {
                nds[u].val += 1;
                updsz(u);
                upd_dp(u);
                return;
            }
            int& to = nds[u].ch[s[j]-'A'];
            if (to == -1) {
                to = mknode();
            }
            f(f, to, j+1);
            updsz(u);
            upd_dp(u);
        };
        dfs(dfs, 0, 0);
        cout << nds[0].dp << "\n";
    }
}