#include <bits/stdc++.h>
using namespace std;
signed main() {
    int q;
    cin >> q;
    for (int ii = 0; ii < q; ii += 1) {
        string s;
        cin >> s;
        int n = int(s.size());
        int atarg, btarg, abrest, barest;
        cin >> atarg >> btarg >> abrest >> barest;
        int _abtarg = abrest;
        int _batarg = barest;
        vector<int> chetABs, chetBAs;
        vector<int> nechet;
        vector<string> temp;
        for (int i = 0; i < n; i += 1) {
            if (!i || s[i] == s[i-1]) {
                temp.push_back(string(1, s[i]));
            } else {
                temp.back().push_back(s[i]);
            }
        }
        for (const auto &x : temp) {
            if (x.size() % 2 == 0) {
                if (x.front() == 'A') {
                    chetABs.push_back(x.size());
                } else {
                    chetBAs.push_back(x.size());
                }
            } else {
                nechet.push_back(x.size());
            }
        }
        sort(chetABs.rbegin(), chetABs.rend());
        for (; chetABs.size(); ) {
            while (abrest) {
                chetABs.back() -= 2;
                abrest -= 1;
                if (!chetABs.back()) {
                    break;
                }
            }
            if (chetABs.back() == 0) {
                chetABs.pop_back();
            } else {
                break;
            }
        }
        sort(chetBAs.rbegin(), chetBAs.rend());
        for (; chetBAs.size(); ) {
            while (barest) {
                chetBAs.back() -= 2;
                barest -= 1;
                if (!chetBAs.back()) {
                    break;
                }
            }
            if (chetBAs.back() == 0) {
                chetBAs.pop_back();
            } else {
                break;
            }
        }
        while (chetABs.size() && barest) {
            int maxi = min(chetABs.back()-2, barest*2);
            barest -= maxi/2;
            chetABs.back() -= maxi+2;
            if (chetABs.back() == 0) {
                chetABs.pop_back();
            }
        }
        while (chetBAs.size() && abrest) {
            int maxi = min(chetBAs.back()-2, abrest*2);
            abrest -= maxi/2;
            chetBAs.back() -= maxi+2;
            if (chetBAs.back() == 0) {
                chetBAs.pop_back();
            }
        }
        int max_undecided_basically_any_hell_yea = 0;
        for (const auto &x : nechet) {
            max_undecided_basically_any_hell_yea += x/2;
        }max_undecided_basically_any_hell_yea = min(max_undecided_basically_any_hell_yea, abrest+barest);
        int our_decided_ab_cnt = _abtarg-abrest;
        int our_decided_ba_cnt = _batarg-barest;
        int our_a_cnt = count(s.begin(), s.end(), 'A') - our_decided_ab_cnt - our_decided_ba_cnt - max_undecided_basically_any_hell_yea;
        int our_b_cnt = count(s.begin(), s.end(), 'B') - our_decided_ab_cnt - our_decided_ba_cnt - max_undecided_basically_any_hell_yea;
        if (our_a_cnt > atarg || our_b_cnt > btarg) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}