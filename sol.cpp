#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    bitset<1'000'000> seen;
    for (int tt = 0; tt <= 11; tt += 1) {
        seen.reset();
        ofstream cout("output"+string(1, char('0'+tt/10))+string(1, '0'+tt%10)+".txt");
        ifstream cin("input"+string(1, char('0'+tt/10))+string(1, '0'+tt%10)+".txt");
        string s;
        vector<string> strings;
        while (getline(cin, s)) {
            strings.push_back(s);
        }
        int n = strings.size();
        int NVM = 0;
        string curr;
        auto dfs = [&] (auto f, int u) -> void {
            seen[u] = true;
            for (int j = 0; j < n; j += 1) if (!seen[j]) {
                // i ----> j
                for (int k = 0; k < 30; k += 1) {
                    if (equal(strings[u].begin()+k, strings[u].end(), strings[j].begin())) {
                        for (int d = 0; d < 50-k; d += 1) {
                            curr.pop_back();
                        }
                        curr += strings[j];
//                        std::cout << ++NVM << "\n";
                        f(f, j);
//                        std::cout << tt << "::::" << u << " ->> " << j << "(" << k << ")\n";
                        return;
                    }
                }
            }
        };
        vector<string> ans;
        for (int i = 0; i < n; i += 1) {
            if (!seen[i]) {
                curr = strings[i];
                dfs(dfs, i);
                std::cout << curr.size() << ":)\n";
                ans.push_back(curr);
                curr = "";
            }
        }
        vector<string> final;
        for (const auto &x : ans) {
            for (int i = 0; i+500 <= x.size(); i += 500) {
                final.push_back(x.substr(i, 500));
            }
        }
        final.resize(100);
        cout << final.size() << "\n";
        for (const auto &x : final) {
            cout << x << "\n";
        }
    }
}