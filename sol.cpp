#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b) {
    if (a%b==0) {
        return b;
    }
    return gcd(b,a%b);
}
long long x, z, k;
long long a;
long long m;
long long b;
string find_sol() {
    a %= m;
    b %= m;
    if (b == 1 || m == 1) {
        return "0";
    }
    long long g = gcd(a, m);
    if (g > 1) {
        long long pow_addone = 0;
        long long ko = 1;
        while (g > 1) {
            if (b == ko) {
                return to_string(pow_addone);
            }
            if (b % g != 0) {
                return "No Solution";
            }
            pow_addone += 1;
            long long a0 = a / g;
            b /= g;
            m /= g;
            ko = (ko * a0) % m;
            g = gcd(a, m);
        }
        long long C = sqrt(m)+1;
        long long a_pow_sqrt = 1;
        for (long long i = 0; i < C; i += 1) {
            a_pow_sqrt = (a_pow_sqrt * a) % m;
        }
        unordered_map<long long, set<long long>> mp;
        long long curr = ko;
        for (long long i = 0; i <= C; i += 1) {
            mp[curr].insert(C * i);
            curr = (curr * a_pow_sqrt) % m;
        }
        curr = b;
        const long long INF = 1e18;
        long long mini = INF;
        for (long long j = 0; j < C; j += 1) {
            if (mp.count(curr)) {
                auto it = mp[curr].lower_bound(j);
                if (it != mp[curr].end()) {
                    mini = min(mini, *it - j);
                }
            }
            curr = (curr * a) % m;
        }
        if (mini == INF) {
            return "No Solution";
        }
        return to_string(mini+pow_addone);
    } else {
        long long C = sqrt(m)+1;
        long long a_pow_sqrt = 1;
        for (long long i = 0; i < C; i += 1) {
            a_pow_sqrt = (a_pow_sqrt * a) % m;
        }
        unordered_map<long long, set<long long>> mp;
        long long curr = 1;
        for (long long i = 0; i <= C; i += 1) {
            mp[curr].insert(C*i);
            curr = (curr * a_pow_sqrt) % m;
        }
        curr = b;
        const long long INF = 1e18;
        long long mini = INF;
        for (long long j = 0; j < C; j += 1) {
            if (mp.count(curr)) {
                auto it = mp[curr].lower_bound(j);
                if (it != mp[curr].end()) {
                    mini = min(mini, *it-j);
                }
            }
            curr = (curr * a) % m;
        }
        if (mini == INF) {
            return "No Solution";
        }
        return to_string(mini);
    }
}
string solve() {
    x %= z, k %= z;
    long long O = 1, add = 0, g;
    while ((g = gcd(x, z)) > 1) {
        if (k == O) {
            return to_string(add);
        }
        if (k % g) {
            return "No Solution";
        }
        k /= g;
        z /= g;
        add += 1;
        O = (O * x / g) % z;
    }

    long long sqrt_z = sqrt(z) + 1;
    long long x_pow_sqrt = 1;
    for (long long i = 0; i < sqrt_z; i += 1) {
        x_pow_sqrt = (x_pow_sqrt * x) % z;
    }

    unordered_map<long long, long long> k_mult_by_x_pow;
    for (long long q = 0, cur = k; q <= sqrt_z; q += 1) {
        k_mult_by_x_pow[cur] = q;
        cur = (cur * x) % z;
    }

    for (long long p = 1, cur = O; p <= sqrt_z; p += 1) {
        cur = (cur * x_pow_sqrt) % z;
        if (k_mult_by_x_pow.count(cur)) {
            long long ans = sqrt_z * p - k_mult_by_x_pow[cur] + add;
            return to_string(ans);
        }
    }
    return "No Solution";
}
int main() {
    mt19937 mt(time(0));
    while (true) {
        x = mt() % 50 + 1;
        z = mt() % 50 + 1;
        k = mt() % 50 + 1;
//        cout << x << " (" << z << ") equals to" << k << endl;
        cin >> x >> z >> k;
        a = x;
        m = z;
        b = k;
        if (x == 0 && z == 0 && k == 0) {
            break;
        }
        cout << find_sol() << "\n";
    }
    return 0;
}