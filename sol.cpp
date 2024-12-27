#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    map<int, vector<pair<int, int>>> inc;
    map<int, vector<pair<int, int>>> dec;
    set<int> key_x;
    for (int i = 0; i < n; i += 1) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 200'000;
        y1 += 200'000;
        x2 += 200'000;
        y2 += 200'000;
        key_x.insert(x1);
        key_x.insert(x2);
        inc[x1].push_back({y1, y2});
        dec[x2].push_back({y1, y2});
    }
    int maxi = -1;
    const int N = 400'005;
    pair<int, int> maxi_point = {-1, -1};
    struct Node {
        int lazy = 0;
        int maxi = 0;
        int maxi_idx = 0;
    };
    vector<Node> tree(4*N+10);
    auto build = [&] (auto f, int v, int tl, int tr) -> void {
        tree[v].maxi_idx = tl;
        if (tl == tr) {
            return;
        }
        int tm = (tl + tr) >> 1;
        f(f, 2*v+1, tl, tm);
        f(f, 2*v+2, tm+1, tr);
    };
    build(build, 0, 0, N);
    auto push = [&] (int v) -> void {
        tree[2*v+1].maxi += tree[v].lazy;
        tree[2*v+1].lazy += tree[v].lazy;
        tree[2*v+2].maxi += tree[v].lazy;
        tree[2*v+2].lazy += tree[v].lazy;
        tree[v].lazy = 0;
    };
    auto add_segment = [&] (auto f, int v, int tl, int tr, int l, int r, int inc) -> void {
        if (tl == l && tr == r) {
            tree[v].maxi += inc;
            tree[v].lazy += inc;
            return;
        }
        int tm = (tl + tr) >> 1;
        push(v);
        if (l <= tm) {
            f(f, 2*v+1, tl, tm, l, min(r, tm), inc);
        }
        if (r >= tm + 1) {
            f(f, 2*v+2, tm+1, tr, max(l, tm+1), r, inc);
        }
        tree[v].maxi = tree[2*v+1].maxi;
        tree[v].maxi_idx = tree[2*v+1].maxi_idx;
        if (tree[v].maxi < tree[2*v+2].maxi) {
            tree[v].maxi = tree[2*v+2].maxi;
            tree[v].maxi_idx = tree[2*v+2].maxi_idx;
        }
    };
    for (const auto &x : key_x) {
        for (const auto &[l, r] : inc[x]) {
            add_segment(add_segment, 0, 0, N, l, r, 1);
        }
        if (maxi < tree[0].maxi) {
            maxi = tree[0].maxi;
            maxi_point.first = x - 200'000;
            maxi_point.second = tree[0].maxi_idx - 200'000;
        }
        for (const auto &[l, r] : dec[x]) {
            add_segment(add_segment, 0, 0, N, l, r, -1);
        }
    }
    cout << maxi << endl;
    cout << maxi_point.first << " " << maxi_point.second << endl;
    return 0;
}