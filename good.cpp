#include <bits/stdc++.h>
using namespace std;
const int SQRT_MAXN = 100000; // корень из максимального значения N
const int S = 10000;
bool nprime[SQRT_MAXN], bl[S];
int primes[SQRT_MAXN], cnt;

int main() {

    int n;
    cin >> n;
    int nsqrt = (int) sqrt (n + .0);
    for (int i=2; i<=nsqrt; ++i)
        if (!nprime[i]) {
            primes[cnt++] = i;
            if (i * 1ll * i <= nsqrt)
                for (int j=i*i; j<=nsqrt; j+=i)
                    nprime[j] = true;
        }

    int result = 0;
    for (int k=0, maxk=n/S; k<=maxk; ++k) {
        memset (bl, 0, sizeof bl);
        int start = k * S;
        for (int i=0; i<cnt; ++i) {
            int start_idx = max(2, (start + primes[i] - 1) / primes[i]);
            cout << primes[i] << ": start = " << start_idx*primes[i] << " ( start_of_block = " << start << endl;
            int mystart = max(primes[i]*primes[i], start+(primes[i]-start%primes[i])%primes[i]);
            cout << "mystart:" << mystart << endl;
//            assert(start_idx*primes[i] == mystart);
            int j = mystart - start;
            for (; j<S; j+=primes[i])
                bl[j] = true;
        }
        if (k == 0)
            bl[0] = bl[1] = true;
        for (int i=0; i<S && start+i<=n; ++i)
            if (!bl[i]) {
                result += 1;
                cout << start + i << endl;
            }
    }
    cout << result;
}