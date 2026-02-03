//https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

void ntt(vector<ll> &a, int typ) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	}
	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
	}
	int g = modPow(3, (M - 1) / n);
	vector<ll> wn(n), w(n);
	wn[0] = 1;
	for (int i = 1; i < n; i++) {
        wn[i] = wn[i - 1] * g % M;
	}
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0, t = n / (2 * k); i < k; i++) {
            w[i] = wn[i * t];
        }
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll x = a[i + j], y = a[i + j + k] * w[j] % M;
                a[i + j] = x + y - (x + y >= M ? M : 0);
                a[i + j + k] = x - y + (x - y < 0 ? M : 0);
            }
        }
    }
    if (!typ) {
        reverse(a.begin() + 1, a.end());
        ll inv_n = modPow(n, M - 2);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * inv_n % M;
        }
    }
}

vector<ll> convMod(vector<ll> a, vector<ll> b) {
    int m = a.size() + b.size() - 1;
    if (m == 1) {
        return {a[0] * b[0] % M};
    }
	int B = 32 - __builtin_clz(m - 1);
	int n = 1 << B;

    a.resize(n), b.resize(n);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * b[i] % M;
    }
    ntt(a, 0);
    a.resize(m);
    return a;
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<ll> c = convMod(a, b);
    for (ll x : c) {
        cout << x << " ";
    }

    return 0;
}
