#include <bits/stdc++.h>
using namespace std;
signed main() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    vector<int> cnt(100);
    int need_cells = 0;
    int l = 0;
    int tot = 0;
    // unique = k
    // size > k
    // answer = cnt_of_subarrays_with_such_qualities
    for (int i = 0; i < s.size(); i += 1) {
        need_cells += !cnt[s[i]-'a'];
        cnt[s[i]-'a'] += 1;
        while (need_cells > k) {
            cnt[s[l]-'a'] -= 1;
            need_cells -= !cnt[s[l]-'a'];
            l += 1;
        }
        int sz = i - l + 1;
        if (sz > k) {
            tot += sz - k;
        }
    }
    cout << tot << "\n";
}