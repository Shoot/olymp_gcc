#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a (n, vector<int>(m, 0));
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < m; j += 1) {
            cin >> a[i][j];
        }
    }
    int q;cin>>q;
    while(q--) {
        int c;
        cin >> c;
        stack<int> stck;
        vector<int> up(m, -1), left(m), right(m);
        int ans = -1e9;
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < m; j+=1) {
                if (a[i][j] != c) {
                    up[j] = i;
                }
            }
            while (!stck.empty()) stck.pop();
            for (int j = 0; j < m; j += 1) {
                while (!stck.empty() && up[stck.top()] <= up[j]) stck.pop();
                if (stck.empty()) left[j] = -1;
                else left[j] = stck.top();
                stck.push(j);
            }
            while (!stck.empty()) stck.pop();
            for (int j = m - 1; j >= 0; j -= 1) {
                while (!stck.empty() && up[stck.top()] <= up[j]) stck.pop();
                if (stck.empty()) right[j] = m;
                else right[j] = stck.top();
                stck.push(j);
            }
            for(int j = 0; j < m; j++) ans = max(ans, (i - up[j]) * (right[j] - left[j] - 1));
        }
        cout << ans << endl;
    }
}
