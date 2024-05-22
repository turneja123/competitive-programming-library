//https://www.spoj.com/problems/PIBO2/
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e4 + 5;
unsigned long long M = 1111111111;
const unsigned long long CM = 1111111111;
const unsigned int MP[] = {11, 41, 271, 9091};

long long a[N];

long long extendedEuclidean(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedEuclidean(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

long long modInverse(long long b, long long m) {
    long long x, y;
    long long g = extendedEuclidean(b, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

long long crt(vector<pair<long long, long long>> &v) {
    long long M = 1;
    for (int i = 0; i < v.size(); i++) {
        M *= v[i].second;
    }
    __int128 ans = 0;
    for (int i = 0; i < v.size(); i++) {
        long long m = M / v[i].second;
        long long n = modInverse(m, v[i].second);
        ans = (ans + (__int128)v[i].first * m % M * n) % M;
    }
    return (long long)ans;
}

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

vector<int> convMod(const vector<int> &a, const vector<int> &b, int mp) {
	vector<int> res(a.size() + b.size() - 1);
	int B = 32 - __builtin_clz(res.size());
	int n = 1 << B;
	int cut = int(sqrt(MP[mp]));
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
		res[i] = ((av % MP[mp] * cut + bv) % MP[mp] * cut + cv) % MP[mp];
	}
	return res;
}

int solve(vector<int> &c, vector<int> &s, long long k, int mp) {
    if (c.empty()) {
        return 0;
    }
    if (k < c.size()){
        return s[k];
    }
    auto q = c;
    for (auto &x: q) {
        x = MP[mp] - x;
    }
    q.insert(q.begin(), 1);
    init(s.size() + q.size() - 1);
    auto p = convMod(s, q, mp);
    p.resize(c.size());
    while (k) {
        auto qm = q;
        for (int i = 1; i < qm.size(); i += 2) {
            qm[i] = MP[mp] - qm[i];
        }
        auto s = convMod(p, qm, mp);
        auto t = convMod(q, qm, mp);
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

int ct = 0;

long long modPow(long long a, long long y, int mp) {
    long long res = 1;
    ct++;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % MP[mp];
        }
        y /= 2;
        a = (a * a) % MP[mp];
    }
    return res;
}

vector<int> berlekamp_massey(vector<int> s, int mp) {
    int n = s.size(), l = 0, m = 0;
    vector<int> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    int d = 1, add = MP[mp] * MP[mp];
    for (int i = 0; i < n; i++) {
        m++;
        long long d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next += c[j] * s[i - j];
        }
        d_next %= MP[mp];
        if (d_next == 0) {
            continue;
        }
        t = c;
        int coef = (d_next * modPow(d, MP[mp] - 2, mp)) % MP[mp];
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) + add) % MP[mp];
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
        c[i] = (c[i] + MP[mp]) % MP[mp];
    }
    return c;
}

long long poly(long long n, int d) {
    long long ans = 0, ct = 1;
    for (int i = 0; i <= d; i++) {
        ans = (ans + a[i] * ct) % CM;

        ct = (ct * n) % CM;
    }
    return ans;
}


int main() {
    IOS;
    int n, d;
    cin >> n >> d;
    for (int i = 0; i <= d; i++) {
        cin >> a[i];
    }
    vector<int> s[4];
    for (int j = 0; j < 4; j++) {
        s[j].push_back(1);
        s[j].push_back(1);
    }
    for (int i = 2; i <= 2 * d + 10; i++) {
        int p = poly(i, d);
        for (int j = 0; j < 4; j++) {
            s[j].push_back((s[j][i - 1] + s[j][i - 2] + p % MP[j]) % MP[j]);
        }
    }
    vector<int> c[4];
    for (int j = 0; j < 4; j++) {
        c[j] = berlekamp_massey(s[j], j);
    }

    vector<pair<long long, long long>> v;
    for (int j = 0; j < 4; j++) {
        s[j].resize(c[j].size());
        long long ans = solve(c[j], s[j], n, j);
        v.push_back(make_pair(ans, MP[j]));
    }
    cout << crt(v) << endl;

    return 0;
}
