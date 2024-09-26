//https://codeforces.com/contest/446/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long M = 1e9 + 9;

long long phi[2];
long long phi_pow[2][N];
long long pref[3][N];

long long a[N];
long long lazy[2][4 * N];
long long segtree[2][4 * N];

long long modPow(long long x, long long y, long long M) {
    if (x == 0 && y == 0) {
        return 1;
    }
    long long res = 1;
    x = x % M;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % M;
        }
        y >>= 1;
        x = (x * x) % M;
    }
    return res;
}

long long tonelli_shanks(long long a, long long p) {
    if (a == 0) {
        return 0;
    }
    if (modPow(a, (p - 1) / 2, p) != 1) {
        return -1;
    }
    if (p % 4 == 3) {
        return modPow(a, (p + 1) / 4, p);
    }
    long long s = p - 1, n = 2, r = 0;
    while (s % 2 == 0) {
        r++;
        s /= 2;
    }
    while (modPow(n, (p - 1) / 2, p) != p - 1) {
        n++;
    }
    long long x = modPow(a, (s + 1) / 2, p), b = modPow(a, s, p), g = modPow(n, s, p), m = 1;
    while (m) {
        long long t = b;
        m = 0;
        for (; m < r && t != 1; m++) {
            t = (t * t) % p;
        }
        if (m == 0) {
            return x;
        }
        long long gs = modPow(g, 1 << (r - m - 1), p);
        g = (gs * gs) % p;
        x = (x * gs) % p;
        b = (b * g) % p;
        r = m;
    }
    return 0;
}

void apply(int l, int r, int node) {
    segtree[0][node] = (segtree[0][node] + lazy[0][node] * (pref[0][r] - ((l == 0) ? 0 : pref[0][l - 1]) + M)) % M;
    segtree[1][node] = (segtree[1][node] + lazy[1][node] * (pref[1][r] - ((l == 0) ? 0 : pref[1][l - 1]) + M)) % M;
    if (l != r) {
        lazy[0][2 * node + 1] = (lazy[0][2 * node + 1] + lazy[0][node]) % M;
        lazy[1][2 * node + 1] = (lazy[1][2 * node + 1] + lazy[1][node]) % M;

        lazy[0][2 * node + 2] = (lazy[0][2 * node + 2] + lazy[0][node]) % M;
        lazy[1][2 * node + 2] = (lazy[1][2 * node + 2] + lazy[1][node]) % M;
    }
    lazy[0][node] = 0;
    lazy[1][node] = 0;
}

void incUpdate(int l, int r, int node, int lq, int rq, vector<long long> &add) {
    if (l > rq || r < lq) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[0][node] = (lazy[0][node] + add[0]) % M;
        lazy[1][node] = (lazy[1][node] + add[1]) % M;
        return;
    }
    apply(l, r, node);
    int mid = (l + r) / 2;
    incUpdate(l, mid, 2 * node + 1, lq, rq, add);
    incUpdate(mid + 1, r, 2 * node + 2, lq, rq,add);
    apply(l, mid, 2 * node + 1);
    apply(mid + 1, r, 2 * node + 2);
    segtree[0][node] = (segtree[0][2 * node + 1] + segtree[0][2 * node + 2]) % M;
    segtree[1][node] = (segtree[1][2 * node + 1] + segtree[1][2 * node + 2]) % M;
}

pair<long long, long long> query(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq) {
        return make_pair(0, 0);
    }
    apply(l, r, node);
    if (l >= lq && r <= rq) {
        return make_pair(segtree[0][node], segtree[1][node]);
    }
    int mid = (l + r) / 2;
    pair<long long, long long> lf = query(l, mid, 2 * node + 1, lq, rq);
    pair<long long, long long> rt = query(mid + 1, r, 2 * node + 2, lq, rq);
    return make_pair((lf.first + rt.first) % M, (lf.second + rt.second) % M);
}

int main() {
	IOS;
    long long sq = tonelli_shanks(5, M);
    phi[0] = (1 + sq) * modPow(2, M - 2, M) % M;
    phi[1] = (1 - sq + M) * modPow(2, M - 2, M) % M;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        phi_pow[0][i] = ((i == 0) ? phi[0] : phi_pow[0][i - 1] * phi[0] % M);
        phi_pow[1][i] = ((i == 0) ? phi[1] : phi_pow[1][i - 1] * phi[1] % M);
        pref[0][i] = ((i == 0) ? phi[0] : (pref[0][i - 1] + phi_pow[0][i]) % M);
        pref[1][i] = ((i == 0) ? phi[1] : (pref[1][i - 1] + phi_pow[1][i]) % M);
        pref[2][i] = ((i == 0) ? a[i] : (pref[2][i - 1] + a[i]) % M);
    }
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            vector<long long> add(2);
            add[0] = ((l == 0) ? 1 : modPow(phi_pow[0][l - 1], M - 2, M));
            add[1] = ((l == 0) ? 1 : modPow(phi_pow[1][l - 1], M - 2, M));
            incUpdate(0, n - 1, 0, l, r, add);
        } else {
            pair<long long, long long> q = query(0, n - 1, 0, l, r);
            long long ans = (pref[2][r] - ((l == 0) ? 0 : pref[2][l - 1]) + modPow(sq, M - 2, M) * (q.first - q.second + M)) % M;
            cout << ans << endl;
        }
    }

    return 0;
}
