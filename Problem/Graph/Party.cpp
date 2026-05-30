//https://codeforces.com/contest/575/problem/C
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 25;
const ll INF2 = 1e12;
const ll INF = 1e18;

ll cost[N][N];
ll a[N][N], b[N][N];
long long u[N], v[N];
long long minv[N];
bool used[N];
int p[N], way[N];
ll ans;

void go(int i, int n) {
    p[0] = i;
    int j0 = 0;
    for (int j = 0; j <= n; j++) {
        minv[j] = INF;
        used[j] = false;
    }
    do {
        used[j0] = true;
        int i0 = p[j0], j1 = 0;
        long long delta = INF;
        for (int j = 1; j <= n; j++) {
            if (!used[j]) {
                long long cur = cost[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
        }
        for (int j = 0; j <= n; j++) {
            if (used[j]) {
                u[p[j]] += delta;
                v[j] -= delta;
            } else {
                minv[j] -= delta;
            }
        }
        j0 = j1;
    } while (p[j0] != 0);
    do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
    } while (j0);
}

ll hungarian(int n) {
    for (int i = 0; i <= n; i++) {
        way[i] = 0, p[i] = 0;
        u[i] = 0, v[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        go(i, n);
    }
    long long c = -v[0];
    return c;

}

void upd(int j, int n) {
    int i = p[j];
    v[j] = INF;
    for (int k = 1; k <= n; k++) {
        v[j] = min(v[j], cost[k][j] - u[k]);
    }
    p[j] = 0;
    go(i, n);
}

void dfs(int j, int cnt, int n) {
    if (cnt > n / 2 || cnt + n - j + 1 < n / 2) {
        return;
    }
    if (j == n + 1) {
        ll cur = 0;
        for (int i = 1; i <= n; i++) {
            cur += cost[p[i]][i];
        }
        ans = max(ans, -cur);
        return;
    }
    dfs(j + 1, cnt, n);
    long long oldu[N], oldv[N], oldcost[N];
    int oldp[N], oldway[N];
    for (int i = 0; i <= n; i++) {
        oldu[i] = u[i];
        oldv[i] = v[i];
        oldp[i] = p[i];
        oldway[i] = way[i];
    }
    for (int i = 1; i <= n; i++) {
        oldcost[i] = cost[i][j];
        cost[i][j] = a[i][j];
    }
    upd(j, n);
    dfs(j + 1, cnt + 1, n);
    for (int i = 0; i <= n; i++) {
        u[i] = oldu[i];
        v[i] = oldv[i];
        p[i] = oldp[i];
        way[i] = oldway[i];
    }
    for (int i = 1; i <= n; i++) {
        cost[i][j] = oldcost[i];
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i + 1][j + 1];
            a[i + 1][j + 1] *= -1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i + 1][j + 1];
            b[i + 1][j + 1] *= -1;
            cost[i + 1][j + 1] = b[i + 1][j + 1];
        }
    }
    ans = 0;
    hungarian(n);
    dfs(1, 0, n);
    cout << ans;

    return 0;
}
