//https://atcoder.jp/contests/abc405/tasks/abc405_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int B = 500;

const long long M = 998244353;


int a[N];
int ct[N];
int ct_b[N];
long long prod_b[N];
long long f[N], finv[N];

long long ans[N];
tuple<int, int, int, int, int64_t> queries[N];


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

inline int64_t hilbert(int x, int y, int pow, int rot) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rot) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rot + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbert(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

bool comp(tuple<int, int, int, int, int64_t> a, tuple<int, int, int, int, int64_t> b) {
    int64_t h1 = get<4>(a);
    int64_t h2 = get<4>(b);
    return h1 < h2;
}

int main() {
    IOS;
    f[0] = 1, finv[0] = 1, prod_b[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = f[i - 1] * i % M;
        finv[i] = modPow(f[i], M - 2);
        prod_b[i] = 1;
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--, x--;
        queries[i] = make_tuple(l, r, i, x, hilbert(l, r, 21, 0));
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, cur, x, h] = queries[i];
        while (r < rq) {
            r++;
            prod_b[a[r] / B] = prod_b[a[r] / B] * f[ct[a[r]]] % M;
            ct[a[r]]++;
            ct_b[a[r] / B]++;
            prod_b[a[r] / B] = prod_b[a[r] / B] * finv[ct[a[r]]] % M;
        }
        while (l > lq) {
            l--;
            prod_b[a[l] / B] = prod_b[a[l] / B] * f[ct[a[l]]] % M;
            ct[a[l]]++;
            ct_b[a[l] / B]++;
            prod_b[a[l] / B] = prod_b[a[l] / B] * finv[ct[a[l]]] % M;
        }
        while (r > rq) {
            prod_b[a[r] / B] = prod_b[a[r] / B] * f[ct[a[r]]] % M;
            ct[a[r]]--;
            ct_b[a[r] / B]--;
            prod_b[a[r] / B] = prod_b[a[r] / B] * finv[ct[a[r]]] % M;
            r--;
        }
        while (l < lq) {
            prod_b[a[l] / B] = prod_b[a[l] / B] * f[ct[a[l]]] % M;
            ct[a[l]]--;
            ct_b[a[l] / B]--;
            prod_b[a[l] / B] = prod_b[a[l] / B] * finv[ct[a[l]]] % M;
            l++;
        }

        ans[cur] = 1;
        int m = 0;
        int j = 0;
        for (j; (j + 1) * B - 1 <= x; j++) {
            m += ct_b[j];
            ans[cur] = ans[cur] * prod_b[j] % M;
        }
        for (int k = B * j; k <= x; k++) {
            m += ct[k];
            ans[cur] = ans[cur] * finv[ct[k]] % M;
        }
        ans[cur] = ans[cur] * f[m] % M;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

