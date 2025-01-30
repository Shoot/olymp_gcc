#include <bits/stdc++.h>
using namespace std;
signed main() {
    int M;
    cin >> M;
    struct Measure {
        int fromi;
        int fromj;
        int dist;
    };
    map<int,vector<Measure>> mp;
    for (int i = 0; i < M; i += 1) {
        string s;
        cin >> s;
        auto stre = stringstream(s);
        string num;
        getline(stre, num, ',');
        int x = stoi(num);
        getline(stre, num, ':');
        int y = stoi(num);
        while (getline(stre, num, '-')) {
            int id = stoi(num);
            getline(stre, num, ',');
            int r = stoi(num);
            mp[id].push_back({x, y, r});
        }
    }
    vector<map<int,map<int,int>>> f(30001);
    vector<int> cnt(30001);
    for (const auto &[id, ms] : mp) {
        cnt[id] = ms.size();
        vector<vector<int>> possible(201, vector<int>(201));
        for (const auto &[x, y, r] : ms) {
            set<pair<int,int>> done;
            int i1 = x - r;
            if (i1 >= 1) {
                for (int j1 = 1; j1 <= 200; j1 += 1) {
                    int di = abs(i1 - x);
                    int dj = abs(j1 - y);
                    if (max(di, dj) == r && !done.count({i1, j1})) {
                        done.insert({i1,j1});
                        f[id][i1][j1] += 1;
                    }
                }
            }
            i1 = x + r;
            if (i1 <= 200) {
                for (int j1 = 1; j1 <= 200; j1 += 1) {
                    int di = abs(i1 - x);
                    int dj = abs(j1 - y);
                    if (max(di, dj) == r && !done.count({i1, j1})) {
                        done.insert({i1,j1});
                        f[id][i1][j1] += 1;
                    }
                }
            }
            int j2 = y - r;
            if (j2 >= 1) {
                for (int i2 = 1; i2 <= 200; i2 += 1) {
                    int di = abs(i2 - x);
                    int dj = abs(j2 - y);
                    if (max(di, dj) == r && !done.count({i2, j2})) {
                        done.insert({i2,j2});
                        f[id][i2][j2] += 1;
                    }
                }
            }
            j2 = y + r;
            if (j2 <= 200) {
                for (int i2 = 1; i2 <= 200; i2 += 1) {
                    int di = abs(i2 - x);
                    int dj = abs(j2 - y);
                    if (max(di, dj) == r && !done.count({i2, j2})) {
                        done.insert({i2,j2});
                        f[id][i2][j2] += 1;
                    }
                }
            }
        }
    }
}