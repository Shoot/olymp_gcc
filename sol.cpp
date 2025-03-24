#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
mt19937 mt(time(0));
struct Node {
    int y;
    int l = -1;
    int r = -1;
    int subtree_sz = 1;
    int val;
    int mn;
    bool lz_r = 0;
    Node(int val_) {
        val = val_;
        mn = val_;
        y = mt();
    }
};
vector<Node> tree;
void reverse(int u) {
    tree[u].lz_r ^= 1;
}
int getsz(int u) {
    if (u == -1) {
        return 0;
    }
    return tree[u].subtree_sz;
}
int getmn(int u) {
    if (u == -1) {
        return 1e18;
    }
    return tree[u].mn;
}
void push(int u) {
    if (u == -1) {
        return;
    }
    if (tree[u].lz_r) {
//        cout << "rrr1: "; print_subtree(u); cout << "\n";
//        clog << "swap: " << tree[u].l << " " << tree[u].r << "\n";
        swap(tree[u].l, tree[u].r);
//        cout << "rrr2: "; print_subtree(u); cout << "\n";
        tree[u].lz_r = false;
        if (getsz(tree[u].l) > 1) {
            tree[tree[u].l].lz_r ^= 1;
        }
        if (getsz(tree[u].r) > 1) {
            tree[tree[u].r].lz_r ^= 1;
        }
    }
}
void print_subtree(int u) {
    push(u);
    if (u == -1) {
        return;
    }
    print_subtree(tree[u].l);
    cout << tree[u].val << " ";
    print_subtree(tree[u].r);
};
void recalc(int u) {
    tree[u].subtree_sz = getsz(tree[u].l)+getsz(tree[u].r)+1;
    tree[u].mn = min(tree[u].val, min(getmn(tree[u].l), getmn(tree[u].r)));
}
int merge(int l, int r) {
    push(l);
    push(r);
    if (l == -1) {
        return r;
    }
    if (r == -1) {
        return l;
    }
    if (tree[l].y < tree[r].y) {
        tree[r].l = merge(l, tree[r].l);
        recalc(r);
        return r;
    } else {
        tree[l].r = merge(tree[l].r, r);
        recalc(l);
        return l;
    }
}
pair<int,int> splitsz(int u, int sz) {
    push(u);
    if (u == -1) {
        return {-1, -1};
    }
    if (getsz(tree[u].l) >= sz) {
        auto [l, m] = splitsz(tree[u].l, sz);
        tree[u].l = m;
        recalc(u);
        return {l, u};
    } else {
        auto [l, r] = splitsz(tree[u].r, sz-getsz(tree[u].l)-1);
        tree[u].r = l;
        recalc(u);
        return {u, r};
    }
}
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int T = 1;
//    cin >> T;

    for (int tt = 0; tt < T; tt += 1) {
        tree.reserve(1'000'000);
        int n, q;
        cin >> n >> q;
        int rt = -1;
        for (int i = 0; i < n; i += 1) {
            int x;
            cin >> x;
            tree.push_back(Node(x));
            rt = merge(rt, tree.size()-1);
        }
        auto rev = [&] (int L, int R) -> void {
            auto [lm, r] = splitsz(rt, R+1);
//            cout << "lm: "; print_subtree(lm); cout << ":)\n";
            auto [l, m] = splitsz(lm, L);
//            cout << "m: "; print_subtree(m); cout << ":)\n";
            reverse(m);
//            cout << "lmn: "; print_subtree(lmn); cout << ":)\n";
//            cout << "r: "; print_subtree(r); cout << ":)\n";
            rt = merge(merge(l, m), r);
        };
        for (int ii = 0; ii < q; ii += 1) {
            int tp;
            cin >> tp;
            if (tp == 1) {
                int l, r;
                cin >> l >> r;
                l -= 1;
                r -= 1;
                rev(l, r);
            } else {
                int l, r;
                cin >> l >> r;
                l -= 1;
                r -= 1;
                auto [llmm, rr] = splitsz(rt, r+1);
                auto [ll, mm] = splitsz(llmm, l);
                cout << tree[mm].mn << "\n";
                rt = merge(ll, merge(mm, rr));
            }
//            print_subtree(rt); cout << "\n";
        }
    }
}