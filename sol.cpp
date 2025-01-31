#include <bits/stdc++.h>
using namespace std;
signed main() {
    string s, t;
    cin >> s >> t;
    string ans;
    for (int i = 0; i < s.size(); i += 1) {
        ans.push_back(s[i]);
        if (equal(ans.end() - t.size(), ans.end(), t.begin())) {
            ans.resize(ans.size() - t.size());
        }
    }
    cout << ans << "\n";
}