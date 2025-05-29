//https://atcoder.jp/contests/abc407/tasks/abc407_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 21;

long long a[N][N];
bool vis[N][N];

long long all = 0, ans = 0, cur = 0;

void calc(int i, int j, int n, int m) {
    if (j == m) {
        j = 0;
        i++;
    }
    if (i == n) {
        ans = max(ans, all ^ cur);
        return;
    }
    if (i != n - 1 && !vis[i][j] && !vis[i + 1][j]) {
        vis[i][j] = true;
        vis[i + 1][j] = true;
        cur ^= a[i][j];
        cur ^= a[i + 1][j];
        calc(i, j + 1, n, m);
        vis[i][j] = false;
        vis[i + 1][j] = false;
        cur ^= a[i][j];
        cur ^= a[i + 1][j];
    }
    if (j != m - 1 && !vis[i][j] && !vis[i][j + 1]) {
        vis[i][j] = true;
        vis[i][j + 1] = true;
        cur ^= a[i][j];
        cur ^= a[i][j + 1];
        calc(i, j + 1, n, m);
        vis[i][j] = false;
        vis[i][j + 1] = false;
        cur ^= a[i][j];
        cur ^= a[i][j + 1];
    }
    calc(i, j + 1, n, m);
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            all ^= a[i][j];
        }
    }
    calc(0, 0, n, m);
    cout << ans;
    return 0;
}
