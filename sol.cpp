#include <bits/stdc++.h>
using namespace std;

int main() {
    const int INF = 1e9;
    int n, m, types_of_doors;
    while (cin >> n >> m >> types_of_doors) {
        struct Door {
            int to_x;
            int to_y;
            int type;
        };
        vector<int> ks[51][51];
        vector<Door> drs[51][51];
        int total_gates_and_walls;
        cin >> total_gates_and_walls;
        for (int i = 0; i < total_gates_and_walls; i += 1) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int type;
            cin >> type;
            drs[x1][y1].push_back({x2, y2, type});
            drs[x2][y2].push_back({x1, y1, type});
        }
        int keys;
        cin >> keys;
        for (int i = 0; i < keys; i += 1) {
            int x, y, type;
            cin >> x >> y >> type;
            ks[x][y].push_back(type);
        }
        struct Node {
            int x;
            int y;
            vector<bool> got_keys;
            Node(int x_, int y_) {
                x = x_;
                y = y_;
                got_keys.resize(11);
            }
            Node(int x, int y, vector<bool> got_keys) : x(x), y(y), got_keys(got_keys){};
            auto operator<(const Node& o) const {
                return tie(x, y, got_keys) < tie(o.x, o.y, o.got_keys);
            };
        };
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        queue<Node> q;
        map<Node, int> d;
        q.push(Node(1, 1));
        d[Node(1, 1)] = 0;
        bool found = false;
        while (!q.empty()) {
            auto [x, y, got] = q.front();
            int dist = d[{x, y, got}];
            if (x == n && y == m) {
                cout << dist << "\n";
                found = true;
                break;
            }
            q.pop();
            for (const auto &tp : ks[x][y]) {
                got[tp] = true;
            }
            set<pair<int, int>> special;
            for (const auto &[to_x, to_y, type] : drs[x][y]) {
                special.insert({to_x, to_y});
                if (to_x > n || to_x < 1 || to_y > m || to_y < 1) {
                    continue;
                }
                if (got[type] && !d.count({to_x, to_y, got})) {
                    d[{to_x, to_y, got}] = dist + 1;
                    q.push({to_x, to_y, got});
                }
            }
            for (int i = 0; i < 4; i += 1) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx > n || nx < 1 || ny > m || ny < 1) {
                    continue;
                }
                if (!special.count({nx, ny})) {
                    if (!d.count({nx, ny, got})) {
                        d[{nx, ny, got}] = dist + 1;
                        q.push({nx, ny, got});
                    }
                }
            }
        }
        if (!found) {
            cout << -1 << "\n";
        }
    }
}