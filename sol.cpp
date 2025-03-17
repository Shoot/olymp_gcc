#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    vector<vector<int>> tp(n, vector<int>(m));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> a[i][j];
            if (a[i][j] == '/') {
                tp[i][j] = 1;
            } else {
                tp[i][j] = -1;
            }
        }
    }
    struct Node {
        int i;
        int j;
        int tp;
        auto operator<(const Node& other) const {
            return tie(i, j, tp) < tie(other.i, other.j, other.tp);
        }
    };
    set<pair<int,Node>> st;
    st.insert({tp[0][0] != -1, {0, 0, -1}});
    map<Node,int> dist;
    dist[{0, 0, -1}] = tp[0][0] != -1;
    struct Transition {
        int di;
        int dj;
        int nwtp;
    };
    map<int,vector<Transition>> go;
    go[1] = {{1,-1,1},{0,-1,-1},{1,0,-1},
             {-1,0,-1},{-1,1,1},{0,1,-1}};
    go[-1] = {{-1,-1,-1},{1,1,-1},{-1,0,1},
              {0,-1,1},{0,1,1},{1,0,1}};
    set<Node> seen;
    while (!st.empty()) {
        auto [nvm, u] = *st.begin();
        st.erase(st.begin());
        if (seen.count(u)) {
            continue;
        }
        seen.insert(u);
        for (const auto &[di,dj,nwtp] : go[u.tp]) {
            int ni = u.i + di;
            int nj = u.j + dj;
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) {
                continue;
            }
            int w = tp[ni][nj] != nwtp;
            if (!dist.count({ni,nj,nwtp})||dist[{ni,nj,nwtp}]>dist[u]+w) {
                dist[{ni,nj,nwtp}]=dist[u]+w;
                st.insert({dist[{ni,nj,nwtp}], {ni,nj,nwtp}});
            }
        }
    }
    int mini = 1e9;
    for (const auto &[u, d] : dist) {
        if (u.i == n-1 && u.j == m-1 && u.tp == -1) {
            mini = min(mini, d);
        }
    }
    if (mini==1e9) {
        cout << "NO SOLUTION\n";
        return 0;
    }
    cout << mini << "\n";
}