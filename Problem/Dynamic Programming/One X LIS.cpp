//https://www.spoj.com/problems/ONEXLIS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

int a[N];
int segtree[2][4 * N];
int dp[N][2];


int rmq(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1, n),
               rmq(mid + 1, r, lq, rq, 2 * node + 2, n));
}

void update(int l, int r, int ind, long long val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = max(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
}
void build(int l, int r, int node, int n) {
    if (l == r) {
        segtree[n][node] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = 0;
}

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n;
        cin >> n;
        set<int> st;
        map<int, int> pos;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            st.insert(a[i]);
            dp[i][0] = 0, dp[i][1] = 0;
        }
        int j = 0;
        for (int x : st) {
            pos[x] = j++;
        }
        int m = st.size();
        build(0, m - 1, 0, 0);
        build(0, m - 1, 0, 1);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int ind = pos[a[i]];
            int l = rmq(0, m - 1, 0, ind, 0, 0);
            if (l != 0) {
                dp[ind][0] = l + 1;
            } else {
                dp[ind][0] = 1;
            }
            update(0, m - 1, ind, dp[ind][0], 0, 0);

            l = rmq(0, m - 1, 0, ind, 0, 1);
            if (l != 0) {
                dp[ind][1] = max(dp[ind][1], l + 1);
            }
            if (ind != m - 1) {
                int r = rmq(0, m - 1, ind + 1, m - 1, 0, 0);
                if (r != 0) {
                    dp[ind][1] = max(dp[ind][1], r + 1);
                }
            }
            update(0, m - 1, ind, dp[ind][1], 0, 1);
            ans = max(ans, dp[ind][1]);
        }
        cout << ans << endl;
	}

	return 0;
}
