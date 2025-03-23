#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifdef LO
#pragma GCC optimize("trapv")
#endif
signed main() {
#ifndef LO
    clog << "FIO\n";
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    mt19937 mt(time(0));
    atomic<int> a;
    atomic<int> b;
    int x;
    atomic<bool> free;
    mutex mu;
    auto go = [&] () -> void {
        while (true) {
            mu.lock();
            a += 1;
            b += 1;
            x += 1;
            mu.unlock();
        }
    };
    vector<thread> ts;
    for (int i = 0; i < 100; i += 1) {
        ts.push_back(thread(go));
        ts.back().detach();
    }
    for (;;) {
        mu.lock();
        cout << a << " " << b << " " << x << "\n";
        mu.unlock();
    }
}
