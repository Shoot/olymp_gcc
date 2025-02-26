#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    vector<vector<int>> vals(n);
    int period = 1;
    for (int i = 0; i < n; i += 1) {
        int sz;
        cin >> sz;
        vals[i].resize(sz);
        for (auto &x : vals[i]) {
            cin >> x;
        }
        period = lcm(period, sz);
    }
    vals.insert(vals.begin(), {0});
    n = vals.size();
//    cout << "P = " << period << "\n";
    // [vertice][time%LCM] = min
    struct Node {
        int cell;
        int time;
        auto operator<(const Node &other) const {
            return make_tuple(cell, time) < make_tuple(other.cell, other.time);
        }
    };
    map<Node, int> damage_by_state;
    set<Node> dijkstra_decided;
    damage_by_state[{0, 0}] = 0;
    set<pair<int,Node>> dijkstra_set;
    dijkstra_set.insert({0, {0, 0}});
    while (!dijkstra_set.empty()) {
        auto [d, tp] = *dijkstra_set.begin();
//        cout << d << "()\n";
//        cout << tp.cell << " " << tp.time << "!!\n";
//        int tmp;
//        cin >> tmp;
        dijkstra_set.erase(dijkstra_set.begin());
        if (dijkstra_decided.count(tp)) {
            continue;
        }
        dijkstra_decided.insert(tp);
        int nxt_time = (tp.time + 1) % period;
//        cout << nxt_time << "!\n";

        int from = damage_by_state[tp];
        for (int k = -1; k <= 1; k += 1) if (tp.cell+k >= 0 && tp.cell+k < n) {
            auto to = Node{tp.cell+k, nxt_time};
            if (!damage_by_state.count(to) || damage_by_state[to] >
            from + vals[to.cell][nxt_time%vals[to.cell].size()]) {
                damage_by_state[to] = from + vals[to.cell][nxt_time%vals[to.cell].size()];
                dijkstra_set.insert({damage_by_state[to], to});
            }
        }
    }
    int mini = 1e9;
    for (const auto &[state, cost] : damage_by_state) {
        if (state.cell == n-1) {
            mini = min(mini, cost);
        }
    }
    cout << mini << "\n";
}