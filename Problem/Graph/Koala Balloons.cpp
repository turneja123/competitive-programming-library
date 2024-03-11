//solution for https://dmoj.ca/problem/aac2p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1505;

int a[N][N];
int pref[N][N];
int col[N][N];
int val[N][N];
bool vis[N][N];
char c[N][N];


void preprocess(int n, int m) {
    pref[0][0] = a[0][0];
    col[0][0] = a[0][0];
    for (int i = 1; i < m; i++) {
        pref[0][i] = pref[0][i - 1] + a[0][i];
        col[0][i] = a[0][i];
    }
    for (int i = 1; i < n; i++) {
        pref[i][0] = pref[i - 1][0] + a[i][0];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            col[i][j] = col[i - 1][j] + a[i][j];
            pref[i][j] = pref[i][j - 1] + col[i][j];
        }
    }
}

int query(int y1, int x1, int y2, int x2) {

    int ret = pref[y2][x2];
    if (y1 > 0) {
        ret -= pref[y1 - 1][x2];
    }
    if (x1 > 0) {
        ret -= pref[y2][x1 - 1];
    }
    if (x1 > 0 && y1 > 0) {
        ret += pref[y1 - 1][x1 - 1];
    }
    return ret;
}

int bin(int i, int j, int n, int m) {
    int l = 0;
    int r = min(n - i - 1, m - j - 1);
    int mx = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int ct = query(i, j, i + mid, j + mid);
        if (ct == (mid + 1) * (mid + 1)) {
            mx = max(mx, mid);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return mx;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            if (c[i][j] == 'O') {
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }
    preprocess(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            val[i][j] = bin(i, j, n, m) + 1;
        }
    }
    int ans = 0;
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({val[0][0], {0, 0}});
    while (pq.size()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int k = pq.top().first;
        pq.pop();
        if (x + k == n && y + k == m) {
            ans = max(ans, k);
        }

        if (vis[x][y]) {
            continue;
        }
        vis[x][y] = true;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 2) {
                    continue;
                }
                if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !vis[x + dx][y + dy]) {
                    pq.push({min(k, val[x + dx][y + dy]), {x + dx, y + dy}});
                }
            }
        }
    }
    cout << ans << endl;


    return 0;
}
