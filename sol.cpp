#include <bits/stdc++.h>
using namespace std;
int main () {
    int n, m, o1, o2;
    cin >> n >> m >> o1 >> o2;
    vector<string> a(n);
    int free = 0;
    for (auto &x : a) {
        cin >> x;
        for (auto &y : x) {
            free += y == '*';
        }
    }
    vector<vector<int>> adj(n*m+1);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            int v = i*m+j+1;
            if ((i+j)%2==0)
                if (a[i][j] == '*') {
                    for (int ii = 0; ii < n; ii += 1) {
                        for (int jj = 0; jj < m; jj += 1) {
                            if (abs(ii-i)+abs(jj-j) == 1) {
                                int vv = ii*m+jj + 1;
                                if (a[ii][jj] == '*') {
                                    adj[v].push_back(vv);
                                }
                            }
                        }
                    }
                }
        }
    }
    n = n * m + 1;
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
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n);
        sz += matching(matching, i, visited, match);
    }
    int rest = free - 2*sz;
    if (2*o2 > o1) {
        cout << sz*o1+rest*o2 << "\n";
    } else {
        cout << free*o2 << "\n";
    }
    return 0;
}