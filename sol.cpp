#include <bits/stdc++.h>
using namespace std;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cin.ignore();
    map<string, vector<int>> what_could_it_be;
    map<string, int> no_change;
    no_change["     |  |"] = 1;
    no_change[" _  _||_ "] = 2;
    no_change[" _  _| _|"] = 3;
    no_change["   |_|  |"] = 4;
    no_change[" _ |_  _|"] = 5;
    no_change[" _ |_ |_|"] = 6;
    no_change[" _   |  |"] = 7;
    no_change[" _ |_||_|"] = 8;
    no_change[" _ |_| _|"] = 9;
    no_change[" _ | ||_|"] = 0;
    vector<int> code(10);
    for (const auto &[s, val] : no_change) {
        for (int i = 0; i < 9; i += 1) {
            if (s[i] != ' ') {
                code[val] += 1 << i;
            }
        }
    }
    auto scan = [&] (string &s1, string &s2, string &s3) -> void {
        vector<int> definite(9, -1);
        vector<vector<int>> possible(9);
        for (int f = 0; f < 27; f += 3) {
            string s;
            s += s1.substr(f, 3);
            s += s2.substr(f, 3);
            s += s3.substr(f, 3);
            int cd = 0;
            for (int i = 0; i < 9; i += 1) {
                if (s[i] != ' ') {
                    cd += 1 << i;
                }
            }
            for (int i = 0; i < 10; i += 1) {
                if (code[i] == cd) {
                    definite[f/3] = i;
                }
            }
            for (int i = 0; i < 10; i += 1) {
                int same = code[i]&cd;
                int diff = code[i]-cd;
                if (diff > 0 && (code[i]&diff)==diff) {
                    possible[f/3].push_back(i);
                }
            }
        }
//        for (const auto &x : definite) {
//            clog << x << " ";
//        }
//        clog << "\n";
//        for (int i = 0; i < 9; i += 1) {
//            if (!possible[i].empty()) {
//                cout << i << ":";
//                for (const auto &x : possible[i]) {
//                    cout << x << "!";
//                }
//                cout << "\n";
//            }
//        }
        vector<int> bad;
        for (int i = 0; i < 9; i += 1) {
            if (definite[i] == -1) {
                bad.push_back(i);
            }
        }
        if (bad.size() > 1) {
            cout << "failure\n";
            return;
        }
        if (bad.size() == 1) {
            int bd = bad[0];
            int su = 0;
            for (int i = 0; i < 9; i += 1) {
                if (i != bd) {
                    assert(definite[i] != -1);
                    su += definite[i]*(9-i);
                    su %= 11;
                }
            }
            vector<int> good_bd;
            for (const auto &x : possible[bd]) {
                if ((su+x*(9-bd))%11==0) {
                    good_bd.push_back(x);
                }
            }
            if (good_bd.empty()) {
                cout << "failure\n";
                return;
            }
            if (good_bd.size() > 1) {
                cout << "ambiguous\n";
                return;
            }
            for (int i = 0; i < 9; i += 1) {
                if (i != bd) {
                    cout << definite[i];
                } else {
                    cout << good_bd[0];
                }
            }
            cout << "\n";
            return;
        }
        vector<int> nice;
        int su = 0;
        for (int i = 0; i < 9; i += 1) {
            su += definite[i]*(9-i);
            su %= 11;
        }
        if (su == 0) {
            nice = definite;
        }
        for (int change = 0; change < 9; change += 1) {
            int tsu = 0;
            for (int i = 0; i < 9; i += 1) {
                if (i != change) {
                    tsu += definite[i]*(9-i);
                    tsu %= 11;
                }
            }
            for (const auto &x : possible[change]) {
                int ntsu = tsu + x*(9-change);
                ntsu %= 11;
                if (ntsu == 0) {
                    if (!nice.empty()) {
                        cout << "ambiguous\n";
                        return;
                    }
                    for (int i = 0; i < 9; i += 1) {
                        if (i != change) {
                            nice.push_back(definite[i]);
                        } else {
                            nice.push_back(x);
                        }
                    }
                }
            }
        }
        if (nice.empty()) {
            cout << "failure\n";
            return;
        }
        for (const auto &x : nice) {
            cout << x;
        }
        cout << "\n";
    };
    for (int i = 0; i < n; i += 1) {
        string s1, s2, s3;
        getline(cin, s1);
        getline(cin, s2);
        getline(cin, s3);
        scan(s1, s2, s3);
    }
    return 0;
}