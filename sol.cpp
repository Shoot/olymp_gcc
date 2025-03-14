#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("popcnt")
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    vector<set<int>> adjSET(n+1);
    vector<vector<int>> iadj(n+1);
    for (int i = 1; i <= n; i += 1) {
        for (int j = i+1; j <= n; j += 1) {
            bool exists;
            cin >> exists;
            if (exists) {
                adj[i].push_back(j);
                adjSET[i].insert(j);
                iadj[j].push_back(i);
            } else {
                adj[j].push_back(i);
                adjSET[j].insert(i);
                iadj[i].push_back(j);
            }
        }
    }
    bitset<2'001> seen;
    vector<int> topo;
    auto dfs = [&] (auto f, int u) -> void {
        seen[u] = true;
        for (const auto &x : adj[u]) {
            if (!seen[x]) {
                f(f, x);
            }
        }
        topo.push_back(u);
    };
    vector<int> curr;
    curr.reserve(2'001);
    vector<int> comp(n+1, 1e9);
    auto idfs = [&] (auto f, int u) -> void {
        seen[u] = true;
        for (const auto &x : iadj[u]) {
            if (!seen[x]) {
                comp[x] = comp[u];
                f(f, x);
            }
        }
        curr.push_back(u);
    };
    for (int i = 1; i <= n; i += 1) {
        if (!seen[i]) {
            dfs(dfs, i);
        }
    }
    reverse(topo.begin(), topo.end());
    int C = 0;
    vector<vector<int>> comps;
    vector<vector<int>> COMPadj(n+1);
    auto dfsshit = [&] (auto f, int u, vector<int>& p, bitset<2'001>& s) -> void {
        s[u] = true;
        for (const auto &x : COMPadj[u]) {
            if (!s[x]) {
                f(f, x, p, s);
            }
        }
        p.push_back(u);
    };
    bitset<2'001> insbitset;
    seen.reset();
    for (const auto &x : topo) {
        if (!seen[x]) {
            curr.clear();
            insbitset.reset();
            comp[x] = C++;
            idfs(idfs, x);
            for (const auto &y : curr) {
                for (const auto &z : adj[y]) {
                    if (comp[z] == comp[y]) {
                        COMPadj[y].push_back(z);
                    }
                }
            }
            vector<int> instopo;
            dfsshit(dfsshit, curr[0], instopo, insbitset);
            reverse(instopo.begin(), instopo.end());
            comps.push_back(instopo);
        }
    }
    vector<int> ans;
    ans.reserve(2'001);
    vector<vector<int>> shit(n+1);
    for (int i = 1; i <= n; i += 1) {
        if (shit[comp[i]].empty()) {
            insbitset.reset();
            ans.clear();
            dfsshit(dfsshit, i, ans, insbitset);
            reverse(ans.begin(), ans.end());
            if (ans.size() == 1 || adjSET[ans.back()].contains(ans.front())) {
                shit[comp[i]] = ans;
            }
        }
    }
    for (int i = 1; i <= n; i += 1) {
        int st = -1;
        int dop = 0;
        for (int j = comp[i]; j < C; j += 1) {
            dop += comps[j].size();
        }
        cout << dop << " ";
        for (int j = 0; j < shit[comp[i]].size(); j += 1) {
            if (shit[comp[i]][j] == i) {
                st = j;
            }
            if (st != -1) {
                cout << shit[comp[i]][j] << " ";
            }
        }
        for (int j = 0; j < st; j += 1) {
            cout << shit[comp[i]][j] << " ";
        }
        for (int j = comp[i]+1; j < C; j += 1) {
            for (const auto &x : comps[j]) {
                cout << x << " ";
            }
        }cout << "\n";
    }
}