#include <bits/stdc++.h>
using namespace std;
int main() {
    string A;
    string B;
    cin >> A >> B;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    while (A.size() < B.size()) {
        A.push_back('0');
    }
    while (B.size() < A.size()) {
        B.push_back('0');
    }
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    auto sub = [&] (string a, string b) -> string {
        bool carry = false;
        string result(a.size(), 'x');
        for (int i = a.size(); i >= 0; i -= 1) {
            int ai = a[i] - '0';
            int bi = b[i] - '0';
            ai -= carry;
            if (ai < bi) {
                ai += 10;
                carry = true;
            } else {
                carry = false;
            }
            result[i] = '0' + (ai - bi);
        }
        return result;
    };
    auto calc = [&] (string x, string y) -> string {
        string result = x;
        for (int i = 0; i < x.size(); i += 1) {
            int su = (x[i] - '0') + (y[i] - '0');
            if (su >= 10) {
                for (int j = i; j < x.size(); j += 1) {
                    result[j] = '0';
                }
                if (i == 0) {
                    result.insert(result.begin(), '1');
                } else {
                    result[i-1] += 1;
                }
                bool carry = false;
                for (int j = result.size(); j >= 0; j -= 1) {
                    result[j] += carry;
                    if (result[j] >= '0'+10) {
                        result[j] -= 10;
                        carry = true;
                    } else {
                        carry = false;
                    }
                }
                if (carry) {
                    result.insert(result.begin(), '1');
                }
                int su10idx = -1;
                while (y.size() < result.size()) {
                    y.insert(y.begin(), '0');
                }
                for (int j = 0; j < result.size(); j += 1) {
                    if ((result[j]-'0')+(y[j]-'0') == 10) {
                        su10idx = j;
                    }
                }
                if (su10idx != -1) {
                    result[su10idx] = '0';
                    int not9 = su10idx-1;
                    for (; not9 >= 0; not9 -= 1) {
                        if ((result[not9]-'0')+(y[not9]-'0') == 9) {
                            result[not9] = '0';
                        } else {
                            break;
                        }
                    }
                    if (not9 == -1) {
                        result.insert(result.begin(), '1');
                    } else {
                        result[not9] += 1;
                    }
                }
                carry = false;
                for (int j = result.size(); j >= 0; j -= 1) {
                    result[j] += carry;
                    if (result[j] >= '0'+10) {
                        result[j] -= 10;
                        carry = true;
                    } else {
                        carry = false;
                    }
                }
                if (carry) {
                    result.insert(result.begin(), '1');
                }
                while (result.size() > x.size()) {
                    x.insert(x.begin(), '0');
                }
                return sub(result, x);
            }
        }
        return sub(result, x);
    };
    string add_to_A = calc(A, B);
    string add_to_B = calc(B, A);
    reverse(add_to_A.begin(), add_to_A.end());
    reverse(add_to_B.begin(), add_to_B.end());
    while (add_to_A.size() < add_to_B.size()) add_to_A.push_back('0');
    while (add_to_A.size() > add_to_B.size()) add_to_B.push_back('0');
    reverse(add_to_A.begin(), add_to_A.end());
    reverse(add_to_B.begin(), add_to_B.end());
    auto ans = min(add_to_A, add_to_B);
    reverse(ans.begin(), ans.end());
    while (ans.size() > 1 && ans.back() == '0') {
        ans.pop_back();
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}