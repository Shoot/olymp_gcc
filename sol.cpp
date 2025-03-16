#include <bits/stdc++.h>
using namespace std;
signed main() {
    int nvm, T;
    cin >> nvm >> T;
    for (int tt = 0; tt < T; tt += 1) {
        int n, k, m;
        cin >> n >> k >> m;
        map<char, set<char>> swappable;
        for (int i = 0; i < m; i += 1) {
            char a, b;
            cin >> a >> b;
            swappable[a].insert(b);
            swappable[b].insert(a);
        }
        string source;
        string target;
        cin >> source >> target;
        bool ok = true;
        for (char one = 'a'; one <= 'a' + k - 1; one += 1) {
            for (char another = one; another <= 'a' + k - 1; another += 1) {
                if (swappable[one].count(another)) {
                    continue;
                }
                string s, t;
                for (const auto &x: source) {
                    if (x == one || x == another) {
                        s.push_back(x);
                    }
                }
                for (const auto &x: target) {
                    if (x == one || x == another) {
                        t.push_back(x);
                    }
                }
                ok &= s == t;
            }
        }
        cout << (ok?"YES":"NO") << "\n";
    }
}