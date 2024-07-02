//https://codeforces.com/contest/840/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int SQ = 550;
const int K = 80;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

int a[N];
int freq[N];
int freq_light[N];

int ans[N];

int ans_q;

vector<tuple<int, int, int, int64_t, int>> queries;

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

bool comp(tuple<int, int, int, int64_t, int> a, tuple<int, int, int, int64_t, int> b) {
    int64_t h1 = get<3>(a);
    int64_t h2 = get<3>(b);
    return h1 < h2;
}

void light(int l, int r, int lim, int n) {
    for (int i = l; i <= r; i++) {
        freq_light[a[i]]++;
        if (freq_light[a[i]] > lim) {
            ans_q = min(ans_q, a[i]);
        }
    }
    for (int i = l; i <= r; i++) {
        freq_light[a[i]]--;
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        if (r - l < SQ) {
            ans_q = N;
            light(l, r, (r - l + 1) / k, n);
            ans[i] = ans_q;
        } else {
            queries.push_back(make_tuple(l, r, i, hilbert(l, r, 21, 0), k));
        }
    }
    sort(queries.begin(), queries.end(), comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < queries.size(); i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int k = get<4>(queries[i]), lim = (rq - lq + 1) / k;
        while (r < rq) {
            r++;
            freq[a[r]]++;
        }
        while (r > rq) {
            freq[a[r]]--;
            r--;
        }
        while (l < lq) {
            freq[a[l]]--;
            l++;
        }
        while (l > lq) {
            l--;
            freq[a[l]]++;
        }
        ans[cur] = N;
        for (int j = 0; j < min(n, K); j++) {
            int ind = l + generator() % (r - l + 1);
            if (freq[a[ind]] > lim) {
                ans[cur] = min(ans[cur], a[ind]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        if (ans[i] == N) {
            cout << -1 << endl;
        } else {
            cout << ans[i] + 1 << endl;
        }
    }
    return 0;
}
