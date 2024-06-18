//https://cses.fi/problemset/task/1734/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int a[N];
int freq[N];
int sz;
tuple<int, int, int, int64_t> queries[N];
int ans[N];
gp_hash_table<int, int, custom_hash> pos;

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
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = pos[a[i]];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i, hilbert(l, r, 21, 0));
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            freq[a[r]]++;
            if (freq[a[r]] == 1) {
                ct++;
            }
        }
        while (r > rq) {
            freq[a[r]]--;
            if (freq[a[r]] == 0) {
                ct--;
            }
            r--;
        }
        while (l < lq) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) {
                ct--;
            }
            l++;
        }
        while (l > lq) {
            l--;
            freq[a[l]]++;
            if (freq[a[l]] == 1) {
                ct++;
            }
        }
        ans[cur] = ct;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
