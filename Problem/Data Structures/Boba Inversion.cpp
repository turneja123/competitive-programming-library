//https://www.spoj.com/problems/BOBAINV/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9 + 5;

int a[N];
int sz;
tuple<int, int, int, int64_t> queries[N];
long long ans[N];

int segtree[4 * N];
pair<int, int> compr[N];
int pos[N];

int query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) +
               query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
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

bool comp(tuple<int, int, int, int64_t> a, tuple<int, int, int, int64_t> b) {
    int64_t h1 = get<3>(a);
    int64_t h2 = get<3>(b);
    return h1 < h2;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        pos[compr[i].second] = m;
    }
    m++;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i, hilbert(l, r, 21, 0));
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    long long ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            int ind = pos[r];
            if (ind < m - 1) {
                ct += query(0, m - 1, ind + 1, m - 1, 0);
            }
            update(0, m - 1, ind, 1, 0);
        }
        while (r > rq) {
            int ind = pos[r];
            if (ind < m - 1) {
                ct -= query(0, m - 1, ind + 1, m - 1, 0);
            }
            update(0, m - 1, ind, -1, 0);
            r--;
        }
        while (l < lq) {
            int ind = pos[l];
            if (ind > 0) {
                ct -= query(0, m - 1, 0, ind - 1, 0);
            }
            update(0, m - 1, ind, -1, 0);
            l++;
        }
        while (l > lq) {
            l--;
            int ind = pos[l];
            if (ind > 0) {
                ct += query(0, m - 1, 0, ind - 1, 0);
            }
            update(0, m - 1, ind, 1, 0);
        }
        ans[cur] = ct;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
