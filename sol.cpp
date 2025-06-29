//#include "testlib.h"
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int long long
#define YES(x) cout << (x?"YES\n":"NO\n")
#define NO(x) cout << (x?"NO\n":"YES\n")
#ifdef LO
#pragma GCC optimize("trapv")
#endif
#ifndef LO
#pragma GCC optimize("Ofast,unroll-loops")
#endif
//constexpr int MOD = (119<<23)+1;
//constexpr int MOD = 967276608647009887ll;
//constexpr int MOD = 1e9+7;
//constexpr int INF = 1e18;
mt19937 mt(time(0));
signed main() {
#ifndef LO
    clog << "FIO" << endl;
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LO
    cout << unitbuf;
#endif
    ifstream fin("nice.txt");
    vector<int> dp(2);
    vector<pair<int,int>> ch(2);
    vector<int> palka(2);
    for (int i = 2; ; i += 1) {
        string s;
        if (!getline(fin, s)) {
            break;
        }
        dp.push_back({});
        ch.push_back({});
        palka.push_back({});
        stringstream ss(s);
        getline(ss, s, '(');
        getline(ss, s, ',');
        assert(stoi(s) == i);
        getline(ss, s, ' ');
        getline(ss, s, ' ');
        dp[i] = stoi(s);
        getline(ss, s, '|');
        ch[i].first = stoi(s);
        getline(ss, s, ' ');
        getline(ss, s, '|');
        ch[i].second = stoi(s);
        getline(ss, s, ' ');
        getline(ss, s);
        palka[i] = stoi(s);
//        cout << i << " " << dp[i] << " " << palka[i] << " " << ch[i].first << " " << ch[i].second << "\n";
        assert(ss.eof());
    }
    cout << "MAX n: " << dp.size()-1 << "\n";
    int curr = 1;
    int n = 467146;
    vector<vector<int>> adj(n+1);
    vector<pair<int,int>> edges;
    auto print = [&] (auto f, const int x) -> int {
        if (!x) {
            return -1;
        }
        int U = curr++;
        int u = U;
        for (int i = 0; i < palka[x]-1; i += 1) {
            int v = curr++;
            edges.push_back({u, v});
            adj[u].push_back(v);
            adj[v].push_back(u);
            u = v;
        }
        int v1 = f(f, ch[x].first), v2 = f(f, ch[x].second);
        if (v1 != -1) {
            adj[v1].push_back(u);
            adj[u].push_back(v1);
            edges.push_back({u, v1});
        }
        if (v2 != -1) {
            adj[v2].push_back(u);
            adj[u].push_back(v2);
            edges.push_back({u, v2});
        }
        return U;
    };
    ofstream testout("001.dat");
    print(print, n);
    uniform_int_distribution<int> V(1, n);
    vector<int> leaves;
    auto dfs = [&] (auto f, int u, int p) -> void {
        bool leaf = true;
        for (const auto &x : adj[u]) {
            if (x != p) {
                f(f, x, u);
                leaf = false;
            }
        }
        if (leaf) {
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(u);
            leaves.push_back(-V(mt));
        }
    };
    dfs(dfs, 1, -1);
    shuffle(leaves.begin(), leaves.end(), mt);
    while (leaves.size()%100 || leaves.size() > 5e5) {
        leaves.pop_back();
    }
    int q = leaves.size();
    testout << n << " " << q << "\n";
    for (const auto &[u, v] : edges) {
        testout << u << " " << v << "\n";
    }
    for (const auto &x : leaves) {
        if (x < 0) {
            testout << 2 << " " << -x << "\n";
        } else {
            testout << 1 << " " << x << "\n";
        }
    }
}