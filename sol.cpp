#include <bits/stdc++.h>
using namespace std;

int main() {
    string nvm;
    int n, m;
    cin >> nvm;
    double S;
    int map_number = 0;
    while (cin >> n >> m) {
        map_number += 1;
        cout << "MAP " << map_number << "\n";
        map<string, int> mp;
        map<int, string> imp;
        vector<pair<double, double>> pts(n);
        vector<int> s(n);
        for (int i = 0; i < n; i += 1) {
            cin >> pts[i].first >> pts[i].second;
            cin >> s[i];
            string id;
            cin >> id;
            mp[id] = i;
            imp[i] = id;
            getline(cin, nvm);
        }
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i += 1) {
            string x, y;
            cin >> x >> y;
            int X = mp[x];
            int Y = mp[y];
            adj[X].push_back(Y);
            adj[Y].push_back(X);
        }
        vector<vector<double>> dist(n, vector<double>(n, 1e18));
        for (int i = 0; i < n; i += 1) {
            dist[i][i] = 0;
            for (const auto &x : adj[i]) {
                dist[i][x] = 15 * hypot(abs(pts[i].first-pts[x].first), abs(pts[i].second-pts[x].second));
            }
        }
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                for (int k = 0; k < n; k += 1) {
                    dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
            }
        }
        cin >> nvm;
        assert(nvm == "ARRIVALS");
        while (cin >> nvm) {
            string time_from, from;
            string time_to, to;
            if (nvm == "MAP") {
                cout << "B\n";
                break;
            }cout << "C\n";
            time_from = nvm;
            cin >> from >> time_to >> to >> S;
            int start = mp[from];
            int finish = mp[to];
            int time = 0;
            time += (time_to[0]-time_from[0])*10*60;
            time += (time_to[1]-time_from[1])*60;
            time += (time_to[3]-time_from[3])*10;
            time += (time_to[4]-time_from[4]);
            if (time < 0) {
                time += 24*60;
            }
            struct Node {
                int u;
                double time;
                double s;
                unsigned long long seen;
                vector<string> ans;
            };
            auto comp = [&] (const Node& one, const Node& another) -> bool {
                double this_path = abs(S - (one.s - dist[one.u][finish]));
                double another_path = abs(S - (another.s - dist[another.u][finish]));
                return this_path < another_path;
            };
            multiset<Node, decltype(comp)> st(comp);
            st.insert({start, 0, 0, 1ull << start, {"!"+imp[start]}});
            st.insert({start, 15, double(s[start]), 1ull << start, {imp[start]}});
            auto show = [&] (Node &x) {
                cout << "PATH FOUND: " << x.s << " ";
                for (const auto &y : x.ans) {
                    cout << y << " ";
                }
                cout << "\n";
            };
            bool done = false;
            while (!st.empty()) {
                if (done) {
                    break;
                }
                Node p = *st.begin();
                st.erase(st.begin());
                for (const auto &v : adj[p.u]) {
                }
            }
            if (!done) {
                cout << "Impossible!\n";
            }
        }
    }
}