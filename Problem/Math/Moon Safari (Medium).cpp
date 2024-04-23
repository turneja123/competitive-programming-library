//https://www.spoj.com/problems/MOON1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 7;
int N = 1003;

typedef pair<int, int> pii;
typedef complex<double> C;

vector<C> rt;
vector<int> rev;

void init(int n) {
    int B = 32 - __builtin_clz(n), L;
    n = 1 << B, L = 31 - __builtin_clz(n);
    vector<complex<long double>> R(2, 1);
    rt = {1, 1};
    rev.resize(n);
    for (int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (int i = k; i < 2 * k; i++) {
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
		}
	}

	rev.resize(n);
	for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	}
}

void fft(vector<C>& a) {
	int n = a.size();

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
    init(s.size() + q.size() - 1);

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
        long long coef = (d_next * modPow(d, M - 2)) % M;
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
    int t;
    cin >> t;
    for (int p = 1; p <= t; p++) {
        long long n, a, k;
        cin >> n >> a >> k;
        vector<long long> s(N);
        s[0] = a;
        for (int i = 1; i < N; i++) {
            s[i] = (s[i - 1] + modPow(a, i + 1) * modPow(i + 1, k)) % M;
        }
        vector<long long> c = berlekamp_massey(s);
        s.resize(c.size());
        cout << solve(c, s, n - 1) << endl;
    }


    return 0;
}
