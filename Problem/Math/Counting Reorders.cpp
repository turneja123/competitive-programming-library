//https://cses.fi/problemset/task/2421
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;
const ll M = 1e9 + 7;

vector<ll> polys[26];

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}


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

vector<long long> calc(int l, int r) {
    if (l == r) {
        return polys[l];
    }
    int mid = (l + r) / 2;
    vector<long long> a = calc(l, mid), b = calc(mid + 1, r);
    vector<long long> ans = convMod(a, b);
    return ans;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    string s;
    cin >> s;
    int n = s.size();
    vector<int> f(26, 0);
    for (int i = 0; i < n; i++) {
        f[s[i] - 'a']++;
    }
    int m = 0;
    for (int j = 0; j < 26; j++) {
        if (f[j]) {
            vector<ll> v;
            for (int i = 0; i < f[j]; i++) {
                ll cur = binomial(f[j] - 1, i) * factinv[f[j] - i] % M;
                if (i % 2) {
                    cur = M - cur;
                }
                v.push_back(cur);
            }
            polys[m++] = v;
        }
    }
    vector<ll> v = calc(0, m - 1);
    ll ans = 0;
    for (int i = 0; i <= n - m; i++) {
        ans = (ans + v[i] * fact[n - i]) % M;
    }
    cout << ans;


    return 0;
}
