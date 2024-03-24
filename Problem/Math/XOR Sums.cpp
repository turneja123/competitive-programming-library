//https://www.codechef.com/problems/SUMXOR2
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;
const int N = 2e5 + 5;
const long long M = 998244353;

typedef pair<int, int> pii;
typedef complex<double> C;

int x[32];
long long f[N];
long long ans[N];

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

ll modInverse(ll a, ll m) {
    ll res = 1;
    ll y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

ll modDivide(ll a, ll b, ll m) {
    a = a % m;
    ll inv = modInverse(b, m);
    return (inv * a) % m;
}

long long binomial(long long n, long long k, long long m) {
    long long num = f[n];
    long long denom = (f[k] * f[n - k]) % m;
    return modDivide(num, denom, m);
}

int main() {
	IOS;
	int n;
	cin >> n;
	f[0] = 1;
	for (long long i = 1; i < N; i++) {
        f[i] = (f[i - 1] * i) % M;
	}
	for (int i = 0; i < n; i++) {
        long long val;
        cin >> val;
        for (long long j = 0; j < 32; j++) {
            long long pw = 1 << j;
            if (pw > val) {
                break;
            }
            long long c = val & pw;
            if (c > 0) {
                x[j]++;
            }
        }
	}
	for (int j = 0; j < 32; j++) {
        if (x[j] == 0) {
            continue;
        }/*
        for (int m = 1; m <= n; m++) {
            for (int k = 1; k <= min(m, x[j]); k += 2) {
                long long ways = (binomial(x[j], k, M) * binomial(n - x[j], m - k, M)) % M;
                ans[m] = (ans[m] + ways * (long long)(1 << j)) % M;
            }
        }*/
        vector<long long> A(x[j] + 1);
        vector<long long> B(n - x[j] + 1);
        for (int i = 0; i <= x[j]; i++) {
            if (i % 2 == 0) {
                A[i] = 0;
            } else {
                A[i] = binomial(x[j], i, M);
            }
        }
        for (int i = 0; i <= n - x[j]; i++) {
            B[i] = binomial(n - x[j], i, M);
        }
        auto conv = convMod<M>(A, B);
        for (int m = 1; m <= n; m++) {
            ans[m] = (ans[m] + conv[m] * (long long)(1 << j));
        }

	}
    for (int m = 1; m <= n; m++) {
        ans[m] = (ans[m] + ans[m - 1]) % M;
    }
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        cout << ans[t] << endl;
    }
	return 0;
}
