#include <bits/stdc++.h>
using namespace std;
int main () {
//    ios::sync_with_stdio(false);
//    cin.tie(0);
    int n; cin >> n;
    map<int, string> mp;
    map<string, int> invmp;
    for (int i = 1; i <= n; i += 1) {
        string filename; cin >> filename;
        mp[i] = filename;
        invmp[filename] = i;
    }
    vector<vector<int>> sm(n+1);
    for (int i = 1; i <= n; i += 1) {
        string filename; cin >> filename;
        assert(filename == mp[i]);
        int sz; cin >> sz;
        cin.ignore();
        for (int j = 0; j < sz; j += 1) {
            string imports;
            getline(cin, imports);
            int start_of_next_item = 1;
            for (int k = 0; k <= imports.size(); k += 1) {
                if (k == imports.size() || imports[k] == ',') {
                    sm[i].push_back(invmp[imports.substr(start_of_next_item, k-start_of_next_item)]);
                } else if (imports[k] == ' ') {
                    start_of_next_item = k + 1;
                }
            }
        }
    }
    int min_cycle = 1e9;
    int min_cycle_vertice = -1;
    bitset<501> seen;
    vector<int> par(501);
    auto bfs = [&] (int u) -> void {
        queue<pair<int,int>> q;
        q.push({0, u});
        seen.reset();
        seen[u] = true;
        while (!q.empty()) {
            auto [d, tp] = q.front();
            q.pop();
            for (const auto &x : sm[tp]) {
                if (x == u) {
                    par[x] = tp;
                    if (d + 1 < min_cycle) {
                        min_cycle = d + 1;
                        min_cycle_vertice = u;
                    }
                    return;
                }
                if (!seen[x]) {
                    par[x] = tp;
                    seen[x] = true;
                    q.push({d + 1, x});
                }
            }
        }
    };
    for (int i = 1; i <= n; i += 1) {
        bfs(i);
    }
    if (min_cycle_vertice == -1) {
        cout << "SHIP IT" << "\n";
        return 0;
    }
    bfs(min_cycle_vertice);
    int curr = min_cycle_vertice;
    vector<string> res;
    while (par[curr] != min_cycle_vertice) {
        curr = par[curr];
        res.push_back(mp[curr]);
    }
    reverse(res.begin(), res.end());
    cout << mp[min_cycle_vertice] << " ";
    for (const auto &x : res) {
        cout << x << " ";
    }
    cout << "\n";
}
