#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    mt19937 mt(time(0));
    for (int i = 1; i <= 10; i += 1) {
        ofstream cout("output"+to_string(i)+".txt");
        ifstream cin("input"+to_string(i)+".txt");
        string s;
        cin >> s;
        std::cout << s << ":D\n";
        int base, m;
        cin >> base >> m;
        auto powm = [&] (int a, int b) -> int {
            int res = 1;
            while (b) {
                if (b&1) {
                    res = (__int128(res) * a) % m;
                }
                a = (__int128(a) * a) % m;
                b >>= 1;
            }
            return res;
        };
        int n = s.size();
        auto nw = s;
        auto h = [&] () -> int {
            int res = 0;
            for (const auto &x : nw) {
                res = (__int128(res) * base + (x-'a'+1)) % m;
            }
            return res;
        };
        auto target = h();
        int tries = 0;
        vector<map<int,string>> mp(100);
        auto dfs = [&] (auto f, int idx) -> bool {
            if (idx == n) {
//                if (h() == target) {
//                    std::cout << nw << "!\n";
//                    std::cout << "!!!\n";
//                    return true;
//                }
                mp[n][h()]=nw;
                return false;
            }
            vector<char> go(26);
            iota(go.begin(), go.end(), 'a');
            shuffle(go.begin(), go.end(), mt);
            for (const auto &x : go) {
                if (tries > 1e8) {
                    return false;
                }
                nw[idx] = x;
                tries += 1;
                if (f(f, idx+1)) {
                    return true;
                }
            }
            return false;
        };
        std::cout << target << "xD\n";
        for (int sz = 1; ; sz += 1) {
            n = sz;
            nw.resize(sz);
            tries = 0;
            if (dfs(dfs, 0)) {
                cout << nw << "\n";
                break;
            }
            bool done = false;
            for (const auto &[h1, s1] : mp[sz]) {
//                std::cout << "have " << h1 << "\n";
                for (int appendsz = 1; appendsz <= sz; appendsz += 1) {
                    int nwhash = (__int128(h1) * powm(base, appendsz))%m;
                    int need = ((target - nwhash) + m) % m;
//                    std::cout << "need " << need << "\n";
                    if (mp[appendsz].count(need)) {
                        cout << s1 << mp[appendsz][need] << "\n";
                        std::cout << "HOOO\n";
                        done = true;
                        break;
                    }
                }
                if (done) {
                    break;
                }
            }
            if (done) {
                break;
            }
            std::cout << "bruh " << sz << "\n";
            std::cout << "tr " << tries << "\n";
        }
        dfs(dfs, 0);
    }
}