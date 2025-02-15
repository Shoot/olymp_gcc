#include <bits/stdc++.h>
using namespace std;
signed main() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    long long tot = 0;
    // cyclic substrings of size > k, cycle is of size exactly k
    for (int i = 0, j = 0; i < s.size(); i += 1) {
        for (j = max(i+k, j); j < s.size() && s[j] == s[j-k]; j += 1) {

        }
        tot += j - i - k;
    }
    cout << tot << "\n";
}