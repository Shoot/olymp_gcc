#include <bits/stdc++.h>
using namespace std;
signed main() {
    vector<string> ss;
    ss.push_back("I");
    ss.push_back("II");
    ss.push_back("III");
    ss.push_back("V");
    ss.push_back("X");
    ss.push_back("XIX");
    ss.push_back("XX");
    ss.push_back("XXX");
    ss.push_back("C");
    ss.push_back("CC");
    ss.push_back("CCC");
    ss.push_back("D");
    ss.push_back("M");
    ss.push_back("MM");
    ss.push_back("MMM");
    sort(ss.begin(), ss.end(), [] (string a, string b) {return a.size() > b.size();});
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i += 1) {
        for (const auto &x : ss) {
            if (s.substr(i, x.size()) == x) {
                curr
                break;
            }
        }
    }
}