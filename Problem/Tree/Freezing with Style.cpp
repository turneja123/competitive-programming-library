//https://codeforces.com/contest/150/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
vector<pair<int, int>> adj[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

int ans = 0, U = 0, V = 1;
int best[N];
int cur[N];
int pref[N];
int suf[N];
int window[N];

int who_best[N];
int who_cur[N];
int who_pref[N];
int who_suf[N];
int who_window[N];
int q[N];

int dfs_depth1(int u, int p) {
    int low = depth[u];

    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            low = max(low, dfs_depth1(v, u));
        }
    }
    return low;
}

void dfs_depth2(int u, int p, int mid, int e) {
    if (cur[depth[u]] < e) {
        cur[depth[u]] = e;
        who_cur[depth[u]] = u;
    }


    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            wt = (wt >= mid ? 1 : -1);
            dfs_depth2(v, u, mid, e + wt);
        }
    }
    return;
}



int calc(int l, int r, int val, int n) {
    int ans, who;
    if (l == 0) {
        ans = pref[r];
        who = who_pref[r];
    } else if (r == n) {
        ans = suf[l];
        who = who_suf[l];
    } else {
        ans = window[l];
        who = who_window[l];
    }
    if (val + ans >= 0) {
        return who;
    }
    return -1;
}

void build(int u, int p, int l, int r) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    vector<tuple<int, int, int>> child;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            int m = dfs_depth1(v, v);
            child.push_back({m, v, wt});
        }
    }
    sort(child.begin(), child.end());

    int L = ans + 1, R = 1e9;

    while (L <= R) {
        int mid = (L + R) / 2;


        int mx = 0;
        for (auto [m, v, wt] : child) {
            wt = (wt >= mid ? 1 : -1);
            dfs_depth2(v, v, mid, wt);

            for (int i = 0; i <= m; i++) {
                if (i >= l && i <= r && cur[i] >= 0) {
                    ans = mid;
                    U = c;
                    V = who_cur[i];
                }

                int lf = max(0, l - i);
                int rt = min(mx, r - i);
                if (lf > rt) {
                    continue;
                }
                int other = calc(lf, rt, cur[i], mx);
                if (other != -1) {
                    ans = mid;
                    U = other;
                    V = who_cur[i];
                }

            }

            mx = max(mx, m);

            for (int i = 0; i <= mx; i++) {
                if (cur[i] > best[i]) {
                    best[i] = cur[i];
                    who_best[i] = who_cur[i];
                }
                cur[i] = -INF;
                pref[i] = best[i];
                who_pref[i] = who_best[i];
                if (i != 0 && pref[i - 1] > pref[i]) {
                    pref[i] = pref[i - 1];
                    who_pref[i] = who_pref[i - 1];
                }
            }
            for (int i = mx; i >= 0; i--) {
                suf[i] = best[i];
                who_suf[i] = who_best[i];
                if (i != mx && suf[i + 1] > suf[i]) {
                    suf[i] = suf[i + 1];
                    who_suf[i] = who_suf[i + 1];
                }
            }
            int ql = 0, qr = -1;

            int k = r - l + 1;
            for (int i = 0, ptr = 0; i <= mx; i++) {
                while (ql <= qr && q[ql] <= i - k) {
                    ql++;
                }
                while (ql <= qr && best[q[qr]] <= best[i]) {
                    qr--;
                }
                q[++qr] = i;
                if (i >= k - 1) {
                    window[ptr] = best[q[ql]];
                    who_window[ptr++] = who_best[q[ql]];
                }
            }
        }
        if (ans == mid) {
            L = mid + 1;
        } else {
            R = mid - 1;
        }
        for (int i = 0; i <= mx; i++) {
            best[i] = -INF;
            cur[i] = -INF;
            pref[i] = -INF;
            suf[i] = -INF;
            window[i] = -INF;
        }
    }

    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c, l, r);
        }
    }
    return;
}

int main() {
    IOS;
    int n, l, r;
    cin >> n >> l >> r;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    for (int i = 0; i < n; i++) {
        best[i] = -INF;
        cur[i] = -INF;
        pref[i] = -INF;
        suf[i] = -INF;
        window[i] = -INF;
    }
    build(0, -1, l, r);
    cout << U + 1 << " " << V + 1;

    return 0;
}
