#include <bits/stdc++.h>
using namespace std;
signed main() {
    atomic<int> right_total = 0;
    int total = 0;
    vector<thread> threads;
    struct Node {
        int p;
        bool iam;
        array<atomic<bool>, 2> want;
        int l = -1e9;
        int r = -1e9;
        atomic<bool> victim;
        Node() {};
    };
    struct P_Mutex {
        int N;
        array<Node, 1000> tree;
        vector<pair<int, bool>> get_v;
        mutex perfect;
        atomic<int> curr = 0;
        void build(int l, int r, int p, bool iam) {
            if (l == r) {
                get_v[l] = {p, iam};
                return;
            }
            tree[curr].iam = iam;
            tree[curr].p = p;
            int m = (l + r) >> 1;
            int v = curr;
            curr += 1;
            tree[v].l = curr;
            build(l, m, v, 0);
            tree[v].r = curr;
            build(m+1, r, v, 1);
        }
        P_Mutex(int cnt) {
            N = cnt;
            get_v.resize(N);
            build(0, N-1, -1, 0);
        }
        void lock(int index) {
//            perfect.lock();
            int curr_v = get_v[index].first;
            int side = get_v[index].second;
            while (curr_v != -1) {
                tree[curr_v].want[side].store(true);
                tree[curr_v].victim.store(side);
                while (tree[curr_v].want[1-side].load() && tree[curr_v].victim.load() == side) {

                }
                side = tree[curr_v].iam;
                curr_v = tree[curr_v].p;
            }
        }
        void unlock(int index) {
//            perfect.unlock();
            int curr_v = 0;
            int l = 0, r = N-1;
            while (l != r) {
//                cout << "hi " << l << " " << r << "\n";
                int m = (l+r) >> 1;
                if (index <= m) {
                    r = m;
                    tree[curr_v].want[0].store(false);
                    curr_v = tree[curr_v].l;
                } else {
                    l = m+1;
                    tree[curr_v].want[1].store(false);
                    curr_v = tree[curr_v].r;
                }
            }
        }
    };
    int TOT = 2;
    volatile int each_liveness[TOT];
    for (int i = 0; i < TOT; i += 1) {
        each_liveness[i] = 0;
    }
    P_Mutex M(TOT+1);
    auto f = [&] (int index) -> void {
        cout << index << "!\n";
        while (true) {
            M.lock(index);
            each_liveness[index] += 1;
            right_total += 1;
            total += 1;
            M.unlock(index);
        }
    };
    for (int i = 0; i < TOT; i += 1) {
        threads.push_back(thread(f, i));
        threads.back().detach();
    }
    while (true) {
        this_thread::sleep_for(100ms);
        M.lock(TOT);
        cout << "1. " << right_total << " " << total << "   ";
        int su = 0;
        for (int i = 0; i < TOT; i += 1) {
            su += each_liveness[i];
        }
        cout << su << "( ";
        for (int i = 0; i < TOT; i += 1) {
            cout << each_liveness[i] << " ";
        }cout << ")\n";



        this_thread::sleep_for(100ms);
        cout << "2. " << right_total << " " << total << "   ";
        su = 0;
        for (int i = 0; i < TOT; i += 1) {
            su += each_liveness[i];
        }
        cout << su << "( ";
        for (int i = 0; i < TOT; i += 1) {
            cout << each_liveness[i] << " ";
        }cout << ")\n";


        this_thread::sleep_for(100ms);
        cout << "3. " << right_total << " " << total << "   ";
        su = 0;
        for (int i = 0; i < TOT; i += 1) {
            su += each_liveness[i];
        }
        cout << su << "(";
        for (int i = 0; i < TOT; i += 1) {
            cout << each_liveness[i] << " ";
        }cout << ")\n";

        M.unlock(TOT);
    }
}