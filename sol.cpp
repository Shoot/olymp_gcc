#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    vector<vector<char>> F(10, vector<char>(10));
    struct Vertice {
        int i;
        int j;
    };
    auto can_move_to = [&] (Vertice v) -> bool {
        if (v.i >= 10 || v.j >= 10 || v.i < 0 || v.j < 0 || F[v.i][v.j] != '#') {
            return false;
        }
        return true;
    };
    auto is_black = [&] (Vertice v) -> bool {
        if (v.i >= 10 || v.j >= 10 || v.i < 0 || v.j < 0 || F[v.i][v.j] != 'B') {
            return false;
        }
        return true;
    };
    int maxi;
    const int di[] = {-2, -2, 2, 2};
    const int dj[] = {-2, 2, -2, 2};
    auto dfs = [&] (auto f, int i, int j, int sz) -> void {
        assert(F[i][j] == 'W');
        maxi = max(maxi, sz);
        for (int k = 0; k < 4; k += 1) {
            if (can_move_to({i+di[k], j+dj[k]}) && is_black({i+di[k]/2, j+dj[k]/2})) {
                F[i+di[k]/2][j+dj[k]/2] = '#';
                F[i][j] = '#';
                F[i+di[k]][j+dj[k]] = 'W';
                f(f, i+di[k], j+dj[k], sz+1);
                F[i+di[k]/2][j+dj[k]/2] = 'B';
                F[i][j] = 'W';
                F[i+di[k]][j+dj[k]] = '#';
            }
        }
    };
    for (int tc = 0; tc < T; tc += 1) {
        maxi = 0;
        for (auto &x : F) {
            for (auto &y : x) {
                cin >> y;
            }
        }
        for (int i = 0; i < 10; i += 1) {
            for (int j = 0; j < 10; j += 1) {
                if (F[i][j] == 'W') {
                    dfs(dfs, i, j, 0);
                }
            }
        }
        cout << maxi << "\n";
    }
    return 0;
}
