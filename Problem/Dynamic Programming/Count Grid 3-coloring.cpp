//https://atcoder.jp/contests/abc379/tasks/abc379_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 15;
const int MAX = 3e4;
const int K = 2e7;
const long long M = 998244353;

int pw[N];
int pos[K];
vector<int> col[MAX];
vector<int> adj[MAX];
long long dp[N * N][MAX];

void get_all(int i, int j, int prv, int n, int mask) {
    if (i == n) {
        adj[j].push_back(mask);
        return;
    }
    if (col[j][i] != 0 && prv != 0) {
        get_all(i + 1, j, 0, n, mask + 0 * pw[i]);
    }
    if (col[j][i] != 1 && prv != 1) {
        get_all(i + 1, j, 1, n, mask + 1 * pw[i]);
    }
    if (col[j][i] != 2 && prv != 2) {
        get_all(i + 1, j, 2, n, mask + 2 * pw[i]);
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mat(n, vector<char>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    if (n > m) {
        vector<vector<char>> temp(m, vector<char>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                temp[j][i] = mat[i][j];
            }
        }
        swap(n, m);
        mat = temp;
    }
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * 3;
    }
    vector<int> masks;
    int ct = 0;
    for (int mask = 0; mask < pw[n]; mask++) {
        vector<int> v(n, 0);
        int j = mask;
        for (int k = 0; k < n; k++) {
            v[k] = j % 3;
            j /= 3;
        }
        int bad = 0;
        for (int k = 1; k < n && !bad; k++) {
            if (v[k] == v[k - 1]) {
                bad = 1;
            }
        }
        if (!bad) {
            masks.push_back(mask);
            col[ct] = v;
            pos[mask] = ct++;
        }
    }
    for (int mask : masks) {
        get_all(0, pos[mask], -1, n, 0);
        bool can = true;
        for (int j = 0; j < n; j++) {
            if (mat[j][0] != '?' && mat[j][0] - '1' != col[pos[mask]][j]) {
                can = false;
            }
        }
        if (can) {
            dp[0][pos[mask]] = 1;
        }
    }
    for (int i = 1; i < m; i++) {
        for (int mask : masks) {
            bool can = true;
            for (int j = 0; j < n; j++) {
                if (mat[j][i] != '?' && mat[j][i] - '1' != col[pos[mask]][j]) {
                    can = false;
                }
            }
            if (!can) {
                continue;
            }
            for (int prv : adj[pos[mask]]) {
                dp[i][pos[mask]] = (dp[i][pos[mask]] + dp[i - 1][pos[prv]]) % M;
            }
        }
    }
    long long ans = 0;
    for (int mask : masks) {
        ans += dp[m - 1][pos[mask]];
    }
    cout << ans % M;
    return 0;
}
