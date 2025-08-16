//https://www.spoj.com/problems/COUNTDIO/
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

vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
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

vector<ll> poly_inv(vector<ll> f) {
    int n = f.size();
    vector<ll> g{modPow(f[0], M - 2)};
    int m = 1;
    while (m < n) {
        int lim = min(2 * m, n);
        vector<ll> fcut(f.begin(), f.begin() + min((int)f.size(), lim));
        vector<ll> t = convMod(g, fcut);
        if (t.size() < lim) {
            t.resize(lim, 0);
        }
        while (t.size() > lim) {
            t.pop_back();
        }
        t[0] = (2 - t[0] + M) % M;
        for (int i = 1; i < lim; i++) {
            t[i] = (M - t[i]) % M;
        }
        g = convMod(g, t);
        while (g.size() > lim) {
            g.pop_back();
        }
        m *= 2;
    }
    return g;
}

int a[N];

vector<long long> calc(int l, int r) {
    if (l == r) {
        vector<long long> ans(a[l] + 1);
        ans[0] = 1;
        ans.back() = M - 1;
        return ans;
    }
    int mid = (l + r) / 2;
    vector<long long> a = calc(l, mid), b = calc(mid + 1, r);
    vector<long long> ans = convMod(a, b);
    return ans;
}

ll solve(vector<long long> &c, vector<long long> &s, long long k) {
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
    auto p = convMod(s, q);
    p.resize(c.size());
    while (k) {
        auto qm = q;
        for (int i = 1; i < qm.size(); i += 2) {
            qm[i] = M - qm[i];
        }
        auto s = convMod(p, qm);
        auto t = convMod(q, qm);
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


int main() {
    IOS;
    int n; ll m;
    cin >> n >> m;
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = __gcd(g, a[i]);
    }
    if (m % g != 0) {
        cout << 0 << endl;
        return 0;
    }
    m /= g;
    for (int i = 0; i < n; i++) {
        a[i] /= g;
    }
    vector<ll> q = calc(0, n - 1);
    vector<ll> r = poly_inv(q);
    int d = 0;
    for (int i = 0; i < n; i++) {
        d += a[i];
    }
    vector<ll> s(d, 0);
    for (int i = 0; i < d && i < r.size(); i++) {
        s[i] = r[i];
    }
    vector<ll> c(d, 0);
    for (int i = 0; i < d; i++) {
        ll x = (i + 1 < q.size() ? q[i + 1] : 0);
        c[i] = (M - x % M) % M;
    }
    cout << solve(c, s, m) % M << endl;
    return 0;
}
