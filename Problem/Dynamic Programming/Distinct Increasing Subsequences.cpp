//https://www.spoj.com/problems/INCDSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 55;

const long long M = 5000000;

long long segtree[K][4 * N];
long long dp[K][N];
int a[N];
pair<int, int> compr[N];

long long last[K][N];

long long query(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    return (query(l, mid, lq, rq, 2 * node + 1, n) + query(mid + 1, r, lq, rq, 2 * node + 2, n)) % M;
}

void update(int l, int r, int ind, int val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val % M;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = (segtree[n][2 * node + 1] + segtree[n][2 * node + 2]) % M;
}


int main() {
    IOS;
    int n, k;
    cin >> n >> k;
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
        a[compr[i].second] = m;
    }
    m++;
    dp[1][0] = 1;
    last[1][a[0]] = 1;
    update(0, m - 1, a[0], 1, 0, 1);
    for (int i = 1; i < n; i++) {
        for (int j = k; j > 1; j--) {
            long long add = query(0, m - 1, 0, a[i] - 1, 0, j - 1);
            dp[j][i] = add % M;
            last[j][a[i]] = add % M;
            update(0, m - 1, a[i], add % M, 0, j);
        }
        dp[1][i] = dp[1][i - 1] + 1 - last[1][a[i]];
        last[1][a[i]] = 1;
        update(0, m - 1, a[i], 1, 0, 1);
    }
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += last[k][i];
    }
    cout << ans % M;
    return 0;
}
