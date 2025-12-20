//https://codeforces.com/contest/2129/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int SQ = 500;

int lo[N], hi[N];
int val[N];
int inside[N];
int ans[N];

int freq[N];
int freq_sq[N];

vector<pair<int, int>> adj[N];
vector<tuple<int, int, int>> events;

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


void add_value(int v, int x, int add) {
    if (!inside[v]) {
        return;
    }
    freq[x] += add;
    freq_sq[x / SQ] += add;
}

void add(int i) {
    auto [u, v, e] = events[i];
    if (u == -1) {
        inside[v] = 1;
        add_value(v, val[v], 1);
        return;
    }
    add_value(u, val[u], -1);
    add_value(v, val[v], -1);

    val[v] ^= u;

    add_value(u, val[u], 1);
    add_value(v, val[v], 1);
}

void rem(int i) {
    auto [u, v, e] = events[i];
    if (u == -1) {
        add_value(v, val[v], -1);
        inside[v] = 0;
        return;
    }
    add_value(u, val[u], -1);
    add_value(v, val[v], -1);

    val[v] ^= u;

    add_value(u, val[u], 1);
    add_value(v, val[v], 1);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
        for (int i = 1; i <= n; i++) {
            lo[i] = events.size();
            events.push_back(make_tuple(-1, i, i));
            for (auto [j, e] : adj[i]) {
                events.push_back(make_tuple(i, j, e));
            }
            hi[i] = events.size() - 1;
        }
        vector<tuple<int, int, int, int, int64_t>> queries;
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            l = lo[l], r = hi[r];
            queries.push_back(make_tuple(l, r, k, i, hilbert(l, r, 21, 0)));
        }
        sort(queries.begin(), queries.end(), comp);
        int l = 0, r = -1;
        for (auto [lq, rq, k, j, _] : queries) {
            while (l > lq) {
                l--;
                add(l);
            }
            while (r < rq) {
                r++;
                add(r);
            }
            while (l < lq) {
                rem(l);
                l++;
            }
            while (r > rq) {
                rem(r);
                r--;
            }
            int i = 0;
            for (; i < N; i++) {
                if (k - freq_sq[i] <= 0) {
                    break;
                }
                k -= freq_sq[i];
            }
            i *= SQ;
            for (; i < N; i++) {
                k -= freq[i];
                if (k <= 0) {
                    ans[j] = i;
                    break;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
        }
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            freq[val[i]] = 0;
            freq_sq[val[i] / SQ] = 0;
            inside[i] = 0;
            val[i] = 0;
        }
        events.clear();

    }
    return 0;
}
