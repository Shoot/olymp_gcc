#include <iostream>
#include <map>
using namespace std;
signed main() {
    long long n;
    cin >> n;
    n *= 2;
    string s;
    cin >> s;
    long long balance = 0;
    long long more_than = 0;
    map<pair<long long,long long>, long long> mem;
    auto number_by_balance_and_len = [&] (auto f, long long bal, long long len) -> long long {
        if (mem.count({bal, len})) {
            return mem[{bal, len}];
        }
        if (abs(bal) > len) {
            return mem[{bal, len}] = 0;
        }
        if (bal == 0) {
            if (len == 0) {
                return mem[{bal, len}] = 1;
            }
            return mem[{bal, len}] = f(f, bal+1, len-1);
        }
        return mem[{bal, len}] = f(f, bal-1, len-1) + f(f, bal+1, len-1);
    };
    for (long long i = 0; i < n; i += 1) {
        if (s[i] == ')') {
            balance -= 1;
            long long rest = n - i - 1;
            more_than += number_by_balance_and_len(number_by_balance_and_len, -(balance+2), rest);
        } else {
            balance += 1;
        }
    }
    cout << more_than << "\n";
}