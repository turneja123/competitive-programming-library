//https://www.spoj.com/problems/EST/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int K = 26;

int dp[N][K];
int a[N];
int id[N];

int segtree[4 * N];
int sum[4 * N];

int S = 0, C = 0;

int walk(int l, int r, int k, int node) {
    if (l == r) {
        S += sum[node];
        C += segtree[node];
        return l;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] >= k) {
        return walk(l, mid, k, 2 * node + 1);
    } else {
        S += sum[2 * node + 1];
        C += segtree[2 * node + 1];
        return walk(mid + 1, r, k - segtree[2 * node + 1], 2 * node + 2);
    }
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += 1;
        sum[node] += val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
}


void build(int l, int r, int node) {
    segtree[node] = 0;
    sum[node] = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);

}

int main() {
    IOS;
    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0) {
            break;
        }
        vector<int> compr(n);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            compr[i - 1] = a[i];
        }
        sort(compr.begin(), compr.end());
        compr.erase(unique(compr.begin(), compr.end()), compr.end());
        for (int i = 1; i <= n; i++) {
            id[i] = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
        }
        int c = compr.size();

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            build(0, c - 1, 0);
            int s = 0;
            for (int j = i; j >= 1; j--) {
                s += a[j];
                update(0, c - 1, id[j], a[j], 0);
                int sz = i - j + 1;
                S = 0, C = 0;
                int med = compr[walk(0, c - 1, (sz + 1) / 2, 0)];
                int add = C * med - S + (s - S) - (sz - C) * med;

                for (int k = 1; k <= m; k++) {
                    dp[i][k] = min(dp[i][k], dp[j - 1][k - 1] + add);
                }
            }
        }
        cout << dp[n][m] << endl;

    }
    return 0;
}
