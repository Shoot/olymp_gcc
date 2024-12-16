#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
using ll = long long;
const ll INF = 1e18;
mt19937 mt(time(0));
struct Node {
    ll val;
    ll y;
    Node* l;
    Node* r;
    ll mn;
    ll sz;
    Node (ll val) : val(val), y(mt()), mn(val), sz(1), l(0), r(0){};
};
void solve() {
    auto getsz = [&] (Node* v) -> ll {
        if (!v) return 0;
        return v->sz;
    };
    auto getmn = [&] (Node* v) -> ll {
        if (!v) return INF;
        return v->mn;
    };
    auto recalc = [&] (Node* v) -> void {
        if (!v) return;
        v->sz = 1+getsz(v->l)+getsz(v->r);
        v->mn = min({v->val, getmn(v->l), getmn(v->r)});
    };
    auto merge = [&] (auto f, Node* l, Node* r) -> Node* {
        assert(l || r);
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        assert(l->y != r->y);
        if (l->y > r->y) {
            l->r = f(f, l->r, r);
            recalc(l);
            return l;
        } else {
            r->l = f(f, l, r->l);
            recalc(r);
            return r;
        }
    };
    /*auto split = [&] (auto f, Node* v, ll key) -> pair<Node*, Node*> {
        if (!v) {
            return {};
        }
        assert(v->x != key);
        if (v->x < key) { // pravoe rezhem
            pair<Node*, Node*> xxx = f(f, v->r, key);
            v->r = xxx.first;
            recalc(*v);
            return {v, xxx.second};
        } else { // levoe rezhem
            pair<Node*, Node*> xxx = f(f, v->l, key);
            v->l = xxx.second;
            recalc(*v);
            return {xxx.first, v};
        }
    };*/
    auto splitsz = [&] (auto f, Node* v, ll sz) -> pair<Node*, Node*> {
        if (!v) {
            return {};
        }
        if (getsz(v->l) >= sz) { // levoe rezhem
            pair<Node*, Node*> xxx = f(f, v->l, sz);
            v->l = xxx.second;
            recalc(v);
            return {xxx.first, v};
        } else { // pravoe rezhem
            pair<Node*, Node*> xxx = f(f, v->r, sz-getsz(v->l)-1/*Ð¼Ð¸Ð½ÑƒÑ ÐºÐ¾Ñ€ÐµÐ½ÑŒ Ð¸ Ð»ÐµÐ²Ð¾Ðµ Ð¿Ð¾Ð´Ð´ÐµÑ€ÐµÐ²Ð¾*/);
            v->r = xxx.first;
            recalc(v);
            return {v, xxx.second};
        }
    };
    auto print_subtree = [&] (auto f, Node* v, bool r) -> void {
        if (!v) return;
        f(f, v->l, false);
        f(f, v->r, false);
    };
    ll q; cin >> q;
    Node* t = nullptr;
    for (ll i = 0; i < q; i += 1) {
        char tp; cin >> tp;
        if (tp == '+') {
            ll idx, val; cin >> idx >> val;
            auto [t1, t2] = splitsz(splitsz, t, idx);
            assert(getsz(t1) == idx);
            t1 = merge(merge, t1, new Node(val));
            t = merge(merge, t1, t2);
        } else {
            ll l, r; cin >> l >> r;
            auto [t0, t1] = splitsz(splitsz, t, l-1);
            assert(getsz(t0) == l-1);
            auto [t1t, t2] = splitsz(splitsz, t1, r-l+1);
            t1 = t1t;
            assert(getsz(t1) == r-l+1);
            cout << t1->mn << "\n";
            t = merge(merge, t0, t1);
            t = merge(merge, t, t2);
        }
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    ll tt = 1;
    while (tt--)
        solve();
    return 0;
}