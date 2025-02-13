#include <bits/stdc++.h>
using namespace std;
signed main() {
    int T;
    cin >> T;
    char x[2] = {'R', 'L'};
    char y[2] = {'U', 'D'};
    for (int tt = 0; tt < T; tt += 1) {
        string s;
        cin >> s;
        int n = int(s.size());
        int mini = 1e9;
        for (const auto &one : x) {
            for (const auto &another : y) {
                for (const auto &third : x) {
                    if (third != one) {
                        for (const auto &fourth : y) {
                            if (fourth != another) {
                                int one_cnt = 0;
                                int another_cnt = 0;
                                for (int i = 0; i < n / 2; i += 1) {
                                    one_cnt += s[i] == one;
                                    another_cnt += s[i] == another;
                                }
                                int third_cnt = 0;
                                int fourth_cnt = 0;
                                for (int i = n / 2; i < n; i += 1) {
                                    third_cnt += s[i] == third;
                                    fourth_cnt += s[i] == fourth;
                                }
                                int free_left = n / 2 - (one_cnt + another_cnt);
                                int free_right = n / 2 - (third_cnt + fourth_cnt);
                                int val = max(free_left+free_right, (abs(one_cnt-third_cnt)+abs(another_cnt-fourth_cnt))/2+(abs(one_cnt-third_cnt)+abs(another_cnt-fourth_cnt))%2);
                                cout << one << another << ", " << third << fourth << " : " << val << "\n";
                                mini = min(mini, val);
                            }
                        }
                    }
                }
            }
        }
        cout << mini << "\n";
    }
}