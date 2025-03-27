//https://dmoj.ca/problem/mmcc14p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;
const int INF = 1e9;
const long long M = 1e9 + 7;
const long long P = 26, INV_P = 576923081;
const long long Q = 9923, INV_Q = 452282579;

long long pw_p[N], pw_q[N];
long long inv_p[N], inv_q[N];

int id[N];
pair<long long, long long> pref[N / 2][N];
int nx[N];


int segtree[4 * N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return INF;
    }

    int mid = (l + r) / 2;
    return min(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = nx[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int common(int a, int b, int m) {
    int l = 0, r = m - 1, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (pref[a][mid] == pref[b][mid]) {
            ans = mid + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    pw_p[0] = 1, pw_q[0] = 1;
    inv_p[0] = 1, inv_q[0] = 1;
    for (int i = 1; i < m; i++) {
        pw_p[i] = pw_p[i - 1] * P % M;
        pw_q[i] = pw_q[i - 1] * Q % M;
        inv_p[i] = inv_p[i - 1] * INV_P % M;
        inv_q[i] = inv_q[i - 1] * INV_Q % M;
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        id[i] = i;
        for (int j = 0; j < m; j++) {
            pref[i][j].first = ((j == 0 ? 0 : pref[i][j - 1].first) + (s[j] - '0' + 1) * pw_p[j]) % M;
            pref[i][j].second = ((j == 0 ? 0 : pref[i][j - 1].second) + (s[j] - '0' + 1) * pw_q[j]) % M;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        nx[i] = common(i, i + 1, m);
    }
    build(0, n - 1, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (l == r) {
            cout << m << endl;
            continue;
        }
        int best = rmq(0, n - 1, l, r - 1, 0);
        cout << best * (r - l + 1) << endl;
        swap(id[l], id[r]);
        if (l != 0) {
            nx[l - 1] = common(id[l - 1], id[l], m);
            update(0, n - 1, l - 1, nx[l - 1], 0);
        }
        if (l != n - 1) {
            nx[l] = common(id[l], id[l + 1], m);
            update(0, n - 1, l, nx[l], 0);
        }

        if (r != 0) {
            nx[r - 1] = common(id[r - 1], id[r], m);
            update(0, n - 1, r - 1, nx[r - 1], 0);
        }
        if (r != n - 1) {
            nx[r] = common(id[r], id[r + 1], m);
            update(0, n - 1, r, nx[r], 0);
        }
    }
    return 0;
}
