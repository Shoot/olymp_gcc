#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using comp = complex<double>;
const double PI = acos(-1);
void solve() {
    auto FFT = [&] (auto f, vector<comp> P, comp x) -> vector<comp> {
        ll n = ll(P.size());
        if (n == 1) {
            return P;
        }
        vector<comp> A(n);
        vector<comp> P0;
        vector<comp> P1;
        for (ll i = 0; i < n; i += 2) {
            P0.push_back(P[i]);
        }
        for (ll i = 1; i < n; i += 2) {
            P1.push_back(P[i]);
        }
        auto A0 = f(f, P0, x * x);
        auto A1 = f(f, P1, x * x);
        comp c(1);
        for (ll i = 0; i < n/2; i += 1) {
            A[i] = A0[i] + c * A1[i];
            A[i + n/2] = A0[i] + -c * A1[i];
            c *= x;
        }

        return A;
    };
    auto multiply = [&] (vector<ll> &A, vector<ll> &B) -> vector<ll> {
        vector<comp> one(A.begin(), A.end()), another(B.begin(), B.end());
        ll multsz = 1;
        while (multsz < ll(A.size()+B.size())) multsz <<= 1;
        one.resize(multsz);
        another.resize(multsz);
        auto dir = comp(cos(PI * 2. / multsz), sin(PI * 2. / multsz));
        auto rev = comp(cos(PI * 2. / multsz), -sin(PI * 2. / multsz));
        auto FFT_direct_one = FFT(FFT, one, dir);
        auto FFT_direct_another = FFT(FFT, another, dir);

        vector<comp> values_mult(multsz);
        for (ll i = 0; i < multsz; i += 1) {
            values_mult[i] = FFT_direct_one[i] * FFT_direct_another[i];
        }
        auto coeff_mult = FFT(FFT, values_mult, rev);

        vector<ll> coeff_ll(multsz);
        for (ll i = 0; i < multsz; i += 1) {
            coeff_ll[i] = round(coeff_mult[i].real() / multsz);
        }
        return coeff_ll;
    };
    auto normalize10 = [&] (vector<ll> &P, ll MAX_RAZRYAD) -> void {
        for (ll i = 0; i < ll(P.size()); i += 1) {
            if (P[i] >= MAX_RAZRYAD) {
                assert(i+1 < ll(P.size()));
                P[i + 1] += P[i] / MAX_RAZRYAD;
                P[i] %= MAX_RAZRYAD;
            }
            assert(P[i] >= 0);
            assert(P[i] < MAX_RAZRYAD);
        }
        while (!P.empty() && P.back() == 0) {
            P.pop_back();
        }
    };
    string x, y; cin >> x >> y;
    bool x_neg = false;
    bool y_neg = false;
    if (x.front() == '-') {
        x_neg = true;
        x.erase(0, 1);
    }
    if (y.front() == '-') {
        y_neg = true;
        y.erase(0, 1);
    }
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    const ll base_pow = 2;
    const ll MAX_RAZRYAD = 1'00;
    while (x.size()%base_pow != 0) x.push_back('0');
    while (y.size()%base_pow != 0) y.push_back('0');
    vector<ll> a;
    vector<ll> b;
    for (ll i = 0; i < ll(x.size()); i += base_pow) {
        ll curr = 0;
        for (ll j = base_pow-1; j >= 0; j -= 1) {
            curr *= 10;
            curr += x[i+j]-'0';
        }
        a.push_back(curr);
    }
    for (ll i = 0; i < ll(y.size()); i += base_pow) {
        ll curr = 0;
        for (ll j = base_pow-1; j >= 0; j -= 1) {
            curr *= 10;
            curr += y[i+j]-'0';
        }
        b.push_back(curr);
    }
    auto c = multiply(a, b);
    normalize10(c, MAX_RAZRYAD);
    if (c.empty()) {
        cout << 0 << endl;
        return;
    }
    if (x_neg ^ y_neg) {
        cout << "-";
    }
    for (ll i = c.size()-1; i >= 0; i -= 1) {
        if (i != ll(c.size()) - 1)
            cout << setw(base_pow) << setfill('0');
        cout << c[i];
    }cout << endl;
    // 1 2 3 4 -> (10,0) (-2,-2) (-2,0) (-2,2)
    // 1 2 3 4 5 6 7 8 -> (36,0) (-4,-9.65685) (-4,-4) (-4,-1.65685) (-4,0) (-4,1.65685) (-4,4) (-4,9.65685)
//    for (const auto &x : FFT_direct_one) {
//        cout << x << ' ';
//    }cout << endl;
}
int main() {
    cout << fixed; cout << setprecision(5);
    ll t = 1;
    //cin >> t;
    for (ll I = 0; I < t; I += 1)
        solve();
    return 0;
}
