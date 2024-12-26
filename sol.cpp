#include <bits/stdc++.h>
using namespace std;
int main () {
    int n;
    cin >> n;
    struct Order {
        int when;
        int from_x;
        int from_y;
        int to_x;
        int to_y;
        int dist () {
            return abs(from_x - to_x) + abs(from_y - to_y);
        }
        int arrive_to_next (int nxt_x, int nxt_y) {
            return when + dist() + abs(nxt_x - to_x) + abs(nxt_y - to_y);
        }
    };
    vector<Order> orders(n);
    for (int i = 0; i < n; i += 1) {
        int h, m, x1, y1, x2, y2;
        scanf("%d:%d %d %d %d %d", &h, &m, &x1, &y1, &x2, &y2);
        int when = h * 60 + m;
        orders[i] = {when, x1, y1, x2, y2};
    }
    vector<vector<int>> adj(n);
    vector<int> match(n, -1);
    auto matching = [&] (auto f, int u, vector<bool>& visited, vector<int>& match) -> bool {
        for (int v: adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                if (match[v] == -1 || f(f, match[v], visited, match)) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    for (int i = 0; i < n; i += 1) {
        for (int j = i + 1; j < n; j += 1) {
            if (orders[i].arrive_to_next(orders[j].from_x, orders[j].from_y) + 1 <= orders[j].when) {
                adj[i].push_back(j);
            }
        }
    }
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n);
        sz += matching(matching, i, visited, match);
    }
    cout << n - sz << "\n";
    return 0;
}