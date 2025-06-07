//https://atcoder.jp/contests/abc409/tasks/abc409_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

using ll = long long;

typedef pair<int, int> pii;
typedef complex<double> C;

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

long long fact[N], factinv[N], inv[N];
long long h[N], ih[N];
long long Q[N], R[N];
long long ans[N];

int main() {
    IOS;
    int n, p;
    cin >> n >> p;
    if (p == 0) {
        cout << n << endl;
        for (int i = 1; i < n; i++) {
            cout << 0 << endl;
        }
        return 0;
    }
    if (p == 100) {
        for (int i = 0; i < n; i++) {
            cout << 1 << endl;
        }
        return 0;
    }
    p = p * modPow(100, M - 2) % M; ll q = (1 - p + M) % M;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    h[0] = 1;
    for (int i = 1; i < n; i++) {
        h[i] = h[i - 1] * (q + i) % M;
    }
    ih[n - 1] = modPow(h[n - 1], M - 2);
    for (int i = n - 1; i > 0; i--) {
        ih[i - 1] = ih[i] * (q + i) % M;
    }
    long long k = h[n - 1] * factinv[n - 1] % M;
    Q[0] = 1;
    for (int i = 1; i <= n; i++) {
        Q[i] = Q[i - 1] * q % M;
    }
    vector<long long> a(n - 1);
    for (int i = 0; i < n - 1; i++) {
        a[i] = Q[i + 1] * k % M * fact[i + 1] % M * ih[i + 1] % M;
    }
    vector<long long> c = a, d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        c[i] = c[i] * fact[i] % M;
        d[i] = factinv[i];
    }
    reverse(c.begin(), c.end());
    auto f = convMod<M>(c, d);
    R[0] = 1;
    for (int i = 1; i < n; i++) {
        R[i] = R[i - 1] * p % M * modPow(q, M - 2) % M;
    }
    ans[0] = k * ih[0] % M;
    for (int i = 2; i <= n; i++) {
        ans[i - 1] = R[i - 1] * f[n - i] % M * factinv[i - 2] % M;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
