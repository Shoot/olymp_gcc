#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <cstring>

using namespace std;

struct Order {
    int departure_time; // Departure time in minutes from 00:00
    pair<int, int> start; // Starting coordinates
    pair<int, int> end;   // Destination coordinates
    int travel_time;      // Travel time from start to end
};

// Convert time from hh:mm to total minutes
int timeToMinutes(const string& time) {
    int h, m;
    sscanf(time.c_str(), "%d:%d", &h, &m);
    return h * 60 + m;
}

// Check if order1 can be followed by order2
bool canChain(const Order& o1, const Order& o2) {
    int end_time1 = o1.departure_time + o1.travel_time;
    int travel_to_next = abs(o1.end.first - o2.start.first) + abs(o1.end.second - o2.start.second);
    return end_time1 + travel_to_next + 1 <= o2.departure_time;
}

// Depth-First Search for finding an augmenting path in bipartite graph
bool bpm(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& match) {
    for (int v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || bpm(match[v], graph, visited, match)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int minTaxis(vector<Order>& orders) {
    int n = orders.size();
    vector<vector<int>> graph(n);

    // Build the graph based on chaining constraints
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (canChain(orders[i], orders[j])) {
                graph[i].push_back(j);
            }
        }
    }

    // Maximum Bipartite Matching using DFS
    vector<int> match(n, -1);
    int result = 0;
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n, false);
        if (bpm(i, graph, visited, match)) {
            ++result;
        }
    }

    // Minimum number of taxis required
    return n - result;
}

int main() {
    int M;
    cin >> M;
    vector<Order> orders;

    for (int i = 0; i < M; ++i) {
        string time;
        int a, b, c, d;
        cin >> time >> a >> b >> c >> d;
        int departure_time = timeToMinutes(time);
        int travel_time = abs(a - c) + abs(b - d);
        orders.push_back({departure_time, {a, b}, {c, d}, travel_time});
    }

    cout << minTaxis(orders) << endl;
    return 0;
}
