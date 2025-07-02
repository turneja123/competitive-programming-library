//https://ocpc2025s.eolymp.space/en/compete/m9rs3cu3vp6lv7kjgk9aaqsa1s/problem/11
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int K = 20;
const long long M = 998244353;

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

int ans[2][K][N];

void dfs(int l, int r, int k, int d, int f) {
    if (d == 0) {
        cout << f;
        return;
    }
    int mid = (l + r) / 2;
    for (int p = 0; p <= 1; p++) {
        int q = f ^ p;
        for (int nl = 0; nl <= k; nl++) {
            int nr = k - f - nl;
            if (nr < 0 || !ans[p][d - 1][nl] || !ans[q][d - 1][nr]) {
                continue;
            }
            dfs(l, mid, nl, d - 1, p);
            dfs(mid + 1, r, nr, d - 1, q);
            return;
        }
    }

}


int main() {
    IOS;
    ans[0][0][0] = 1;
    ans[1][0][1] = 1;
    vector<long long> dpo{0, 1}, dpz{1};
    for (int i = 1; i < K; i++) {
        vector<long long> a = convMod<M>(dpo, dpz);
        vector<long long> b = convMod<M>(dpo, dpo);
        vector<long long> c = convMod<M>(dpz, dpz);
        int na = a.size(), nb = b.size(), nc = c.size();
        vector<long long> no(na + 1), nz(max(nb, nc));
        for (int j = 0; j < na; j++) {
            no[j + 1] = a[j] * 2 % M;
            ans[1][i][j + 1] = (ans[1][i][j + 1] + no[j + 1]) % M;
        }
        for (int j = 0; j < nb; j++) {
            nz[j] = b[j] % M;
            ans[0][i][j] = (ans[0][i][j] + b[j]) % M;
        }
        for (int j = 0; j < nc; j++) {
            nz[j] = (nz[j] + c[j]) % M;
            ans[0][i][j] = (ans[0][i][j] + c[j]) % M;
        }
        dpo = no;
        dpz = nz;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        long long s = (ans[0][n][k] + ans[1][n][k]) % M;
        if (s == 0) {
            cout << -1 << endl;
            continue;
        }
        cout << s << endl;
        if (ans[0][n][k]) {
            dfs(0, 1 << n, k, n, 0);
        } else {
            dfs(0, 1 << n, k, n, 1);
        }
        cout << endl;
    }
    return 0;
}
