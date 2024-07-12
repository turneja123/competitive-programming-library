//https://www.spoj.com/problems/BANSTAND/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

typedef pair<int, int> pii;
typedef complex<double> C;

const int N = 5e5 + 5;
const long long M = 1000000007;

long long a[N];
long long fact[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

long long modDivide(long long a, long long b) {
    a = a % M;
    long long inv = modPow(b, M - 2);
    return (inv * a) % M;
}

long long binomial(long long n, long long k) {
    long long num = fact[n];
    long long denom = (fact[k] * fact[n - k]) % M;
    return modDivide(num, denom);
}

void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
    vector<complex<long double>> R(2, 1);
    vector<C> rt(2, 1);

	for (int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (int i = k; i < 2 * k; i++) {
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
		}
	}

	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	}
	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
	}

	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
		}
    }
}

template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
	vector<ll> res(a.size() + b.size() - 1);
	int B = 32 - __builtin_clz(res.size());
	int n = 1 << B;
	int cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);


	for (int i = 0; i < a.size(); i++) {
        L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	}
	for (int i = 0; i < b.size(); i++) {
        R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	}

	fft(L), fft(R);
	for (int i = 0; i < n; i++) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}

	fft(outl), fft(outs);
	for (int i = 0; i < res.size(); i++) {
		ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
		ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

int main() {
	IOS;
	long long f = 1;
    fact[0] = 1;
    for (long long i = 1; i < N; i++) {
        f *= i;
        f %= M;
        fact[i] = f;
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long n, m;
        cin >> n >> m;
        vector<ll> A(m + 1); vector<ll> B(m + 1);
        for (int i = 0; i <= m; i++) {
            A[i] = (modPow(fact[i], M - 2) * ((i % 2 == 1) ? -1 : 1) + M) % M;
        }
        for (int i = 0; i <= m; i++) {
            B[i] = modPow(i, m) * modPow(fact[i], M - 2) % M;
        }
        auto ret = convMod<M>(A, B);
        for (int i = 1; i <= min(n, m); i++) {
            a[i] = binomial(n, i) * ret[i] % M * fact[i] % M;
        }

        long long prod = 0, tot = modPow(n, m);
        for (int i = 1; i <= min(n, m); i++) {
            prod = (prod + a[i] * i) % M;
        }
        cout << "Case " << tt << ": " << modDivide(prod, tot) << endl;
    }

	return 0;
}
