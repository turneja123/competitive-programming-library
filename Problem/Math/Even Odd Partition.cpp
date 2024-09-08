//https://www.codechef.com/problems/PARTN01?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 6500;
const int K = 1e6 + 5;
const long long M = 998244353;

long long dp[N][2];
long long precalc[K];

vector<long long> s[N];
vector<long long> c[N];

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

int solve(vector<long long> &c, vector<long long> &s, long long k) {
    if (c.empty()) {
        return 0;
    }
    if (k < c.size()){
        return s[k];
    }
    auto q = c;
    for (auto &x: q) {
        x = M - x;
    }
    q.insert(q.begin(), 1);
    auto p = convMod<M>(s, q);
    p.resize(c.size());
    while (k) {
        auto qm = q;
        for (int i = 1; i < qm.size(); i += 2) {
            qm[i] = M - qm[i];
        }
        auto s = convMod<M>(p, qm);
        auto t = convMod<M>(q, qm);
        for (int i = 0; i < t.size() ; i += 2) {
            q[i >> 1] = t[i];
        }
        if (k & 1) {
            for (int i = 1; i < s.size() ; i += 2) {
                p[i >> 1] = s[i];
            }

        } else {
            for (int i = 0; i < s.size(); i += 2) {
                p[i >> 1] = s[i];
            }
        }
        k >>= 1;
    }
    return p[0];
}

long long modInverse(long long a, long long m) {
    long long res = 1;
    long long y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

vector<long long> berlekamp_massey(vector<long long> s) {
    int n = s.size(), l = 0, m = 0;
    vector<long long> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    long long d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        long long d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        long long coef = (d_next * modInverse(d, M)) % M;
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) % M + M) % M;
        }
        if (2 * l > i) {
            continue;
        }
        l = i + 1 - l, b = t, d = d_next, m = 0;
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int i = 0; i < l; i++) {
        c[i] *= -1;
        c[i] = (c[i] + M) % M;
    }
    return c;
}

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i - 1; j >= 0; j--) {
            long long m = ((long long)i * (i + 1) / 2 - (long long)j * (j + 1) / 2) % 2;
            if (j == 0) {
                dp[i][m]++;
            } else {
                dp[i][m] += dp[j][(m + 1) % 2];
            }
        }
        dp[i][0] %= M, dp[i][1] %= M;
        s[0].push_back((dp[i][0] + dp[i][1]) % M);
    }
    for (int i = 1; i < N; i++) {
        long long sum = 0;
        for (int j = 0; j < s[i - 1].size(); j++) {
            sum = (sum + s[i - 1][j]) % M;
            s[i].push_back(sum);
        }
    }
    c[0] = berlekamp_massey(s[0]);
    for (int i = 0; i < 8; i++) {
        precalc[i] = s[0][i];
    }
    for (int i = 8; i < K; i++) {
        for (int j = 0; j < c[0].size(); j++) {
            precalc[i] = (precalc[i] + precalc[i - j - 1] * c[0][j]) % M;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long n; int k;
        cin >> n >> k;
        if (c[k].size() == 0) {
            c[k] = berlekamp_massey(s[k]);
        }
        if (k == 0 && n < N) {
            cout << precalc[n - 1] << endl;
        } else {
            cout << solve(c[k], s[k], n - 1) << endl;
        }
    }

    return 0;
}
