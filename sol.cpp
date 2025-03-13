#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }
    vector<int> min_edge(n, 1e17);
    min_edge[0] = 0;
    double su = 0;
    for (int it = 0; it < n; it += 1) {
        int min_edge_idx = -1;
        int min_edge_weight = 1e18;
        for (int i = 0; i < n; i += 1) {
            if (min_edge[i] < min_edge_weight) {
                min_edge_weight = min_edge[i];
                min_edge_idx = i;
            }
        }
        su += sqrt(min_edge[min_edge_idx]);
        min_edge[min_edge_idx] = 1e18;
        for (int relax = 0; relax < n; relax += 1) if (min_edge[relax] != 1e18) {
                int dx = a[min_edge_idx].first - a[relax].first;
                int dy = a[min_edge_idx].second - a[relax].second;
                min_edge[relax] = min(min_edge[relax], dx*dx+dy*dy);
            }
    }
    cout << fixed << setprecision(10) << su << "\n";
}