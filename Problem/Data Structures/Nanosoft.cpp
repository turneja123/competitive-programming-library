//solution for https://codeforces.com/contest/1301/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int M = 11;

int table[M][M][N][N];
int val[N][N][4];
int pref[N][N][4];
int col[N][N][4];
int a[N][N];
int lg[N];

bool flag[N][N];

unordered_map<char, int> mp = {{'R', 0}, {'Y', 1}, {'G', 2}, {'B', 3}};

void preprocess(int n, int m, int k) {
    pref[0][0][k] = val[0][0][k];
    col[0][0][k] = val[0][0][k];
    for (int i = 1; i < m; i++) {
        pref[0][i][k] = pref[0][i - 1][k] + val[0][i][k];
        col[0][i][k] = val[0][i][k];
    }
    for (int i = 1; i < n; i++) {
        pref[i][0][k] = pref[i - 1][0][k] + val[i][0][k];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            col[i][j][k] = col[i - 1][j][k] + val[i][j][k];
            pref[i][j][k] = pref[i][j - 1][k] + col[i][j][k];
        }
    }
}

int sumQuery(int y1, int x1, int y2, int x2, int k) {
    int ret = pref[y2][x2][k];
    if (y1 > 0) {
        ret -= pref[y1 - 1][x2][k];
    }
    if (x1 > 0) {
        ret -= pref[y2][x1 - 1][k];
    }
    if (x1 > 0 && y1 > 0) {
        ret += pref[y1 - 1][x1 - 1][k];
    }
    return ret;
}

void init(int n, int m) {
    lg[1] = 0;
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    int K = M;
    for (int x = 0; x < K; x++) {
        for (int y = 0; y < K; y++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i + (1 << x) - 1 > n || j + (1 << y) - 1 > m) {
                        continue;
                    }
                    if (x == 0 && y == 0) {
                        table[0][0][i][j] = a[i][j];
                    } else if (x > 0) {
                        table[x][y][i][j] = max(table[x - 1][y][i][j], table[x - 1][y][i + (1 << (x - 1))][j]);
                    } else if (y > 0) {
                        table[x][y][i][j] = max(table[x][y - 1][i][j], table[x][y - 1][i][j + (1 << (y - 1))]);
                    }
                }
            }
        }
    }
}

int maxQuery(int x1, int y1, int x2, int y2) {
    int x = lg[x2 - x1 + 1], y = lg[y2 - y1 + 1];
    return max(max(table[x][y][x1][y1], table[x][y][x2 - (1 << x) + 1][y1]),
               max(table[x][y][x1][y2 - (1 << y) + 1], table[x][y][x2 - (1 << x) + 1][y2 - (1 << y) + 1]));
}

int bin(int x, int y, int n, int m, int k) {
    int l = 0;
    int r = min(n - x - 1, m - y - 1);
    int ret = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int ct = sumQuery(x, y, x + mid, y + mid, k);
        if (ct != (mid + 1) * (mid + 1)) {
            r = mid - 1;
        } else {
            ret = max(ret, mid);
            l = mid + 1;
        }
    }
    return ret;
}

int binAns(int x1, int y1, int x2, int y2, int n, int m) {
    int l = 1;
    int r = min(n, m);
    int mx = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        int xl = x1 + mid - 1, yl = y1 + mid - 1;
        int xr = x2 - mid, yr = y2 - mid;
        if (xl > xr || yl > yr || xl >= n || yl >= m || xr < 0 || yr < 0) {
            r = mid - 1;
            continue;
        }
        int k = maxQuery(xl, yl, xr, yr);
        if (k >= mid) {
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
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            val[i][j][mp[c]] = 1;
        }
    }
    for (int k = 0; k < 4; k++) {
        preprocess(n, m, k);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int rd = bin(i, j, n, m, 0) + 1;
            if (rd == 0) {
                a[i][j] = 0;
                continue;
            }
            int yl = bin(i + rd, j, n, m, 1) + 1;
            if (yl < rd) {
                a[i][j] = 0;
                continue;
            }
            int gr = bin(i, j + rd, n, m, 2) + 1;
            if (gr < rd) {
                a[i][j] = 0;
                continue;
            }
            int bl = bin(i + rd, j + rd, n, m, 3) + 1;
            if (bl < rd) {
                a[i][j] = 0;
                continue;
            }
            a[i][j] = rd;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0 && !flag[i][j]) {
                int v = a[i][j];
                for (int p = 0; p < v; p++) {
                    a[i + p][j + p] = 0;
                }
                a[i + v - 1][j + v - 1] = v;
                flag[i + v - 1][j + v - 1] = true;
            }
        }
    }
    init(n, m);
    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        int k = binAns(x1, y1, x2, y2, n, m);
        cout << 4 * k * k << endl;
    }

    return 0;
}
