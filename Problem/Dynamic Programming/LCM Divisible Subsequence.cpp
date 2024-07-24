//https://toph.co/p/lcm-divisible-subsequence
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

typedef pair<int, int> pii;
typedef complex<double> C;

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

const int K = 1 << 8;
const long long M = 998244353;
const int N = 1005;

int ct[K];
long long dp[K][N];
long long dp_next[K][N];
vector<long long> factors;

const int B = 1e6 + 5;

long long fact[B];

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
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
    long long inv = modInverse(b);
    return (inv * a) % M;
}

long long binomial(long long n, long long k) {
    long long num = fact[n];
    long long denom = (fact[k] * fact[n - k]) % M;
    return modDivide(num, denom);
}

int main() {
    IOS;
    long long f = 1;
    fact[0] = 1;
    for (long long i = 1; i < B; i++) {
        f *= i;
        f %= M;
        fact[i] = f;
    }
    int c;
    cin >> c;
    while (c--) {
        int n, k; long long m;
        cin >> n >> k >> m;
        long long t = m;
        for (long long i = 2; i <= sqrt(m); i++) {
            if (t % i == 0) {
                long long prod = 1;
                while (t % i == 0) {
                    t /= i;
                    prod *= i;
                }
                factors.push_back(prod);
            }
        }
        if (t > 1) {
            factors.push_back(t);
        }
        int x = factors.size(), bits = 1 << x;
        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
            int mask = 0;
            for (int j = 0; j < x; j++) {
                if (a % factors[j] == 0) {
                    mask += 1 << j;
                }
            }
            ct[mask]++;
        }


        for (int i = 0; i < bits; i++) {
            if (ct[i] == 0) {
                continue;
            }
            for (int j = 0; j < bits; j++) {
                /*for (int s = 0; s <= k; s++) {
                    for (int add = 1; add + s <= k && add <= ct[i]; add++) {
                        dp_next[i | j][s + add] = (dp_next[i | j][s + add] + binomial(ct[i], add) * dp[j][s]) % M;
                    }
                }*/
                vector<long long> a(k + 1);
                for (int s = 0; s <= k; s++) {
                    a[s] = dp[j][s];
                }
                vector<long long> b(min(k, ct[i]) + 1);
                for (int add = 0; add <= min(k, ct[i]); add++) {
                    b[add] = binomial(ct[i], add);
                }
                b[0] = 0;
                auto add = convMod<M>(a, b);
                for (int s = 0; s <= k; s++) {
                    dp_next[i | j][s] = (dp_next[i | j][s] + add[s]) % M;
                }
            }

            for (int add = 1; add <= min(k, ct[i]); add++) {
                dp_next[i][add] = (dp_next[i][add] + binomial(ct[i], add)) % M;
            }
            for (int j = 0; j < bits; j++) {
                for (int s = 0; s <= k; s++) {
                    dp[j][s] = (dp[j][s] + dp_next[j][s]) % M;
                    dp_next[j][s] = 0;
                }
            }
        }
        cout << dp[bits - 1][k] << endl;
        for (int j = 0; j < bits; j++) {
            for (int s = 0; s <= k; s++) {
                dp[j][s] = 0;
            }
            ct[j] = 0;
        }
        factors.clear();
    }

    return 0;
}
