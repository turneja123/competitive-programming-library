//solution for https://www.codechef.com/problems/HOLLOW
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int col[N][N];
int pref[N][N];
int zeros = 0;

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

bool check(int sz, int n, int m, int k) {
    bool flag = false;
    for (int i = 0; i + sz - 1 < n; i++) {
        for (int j = 0; j + sz - 1 < m; j++) {
            int ones = query(i, j, i + sz - 1, j + sz - 1);
            if (ones <= k && zeros >= sz * sz) {
                flag = true;
            }
        }
    }
    return flag;
}

int BIN(int n, int m, int k) {
    int mx = 0;
    int l = 0;
    int r = min(n, m);
    while (l <= r) {
        int mid = (l + r) / 2;
        bool flag = check(mid, n, m, k);
        if (flag) {
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
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        zeros = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                if (s[j] == '0') {
                    zeros++;
                    a[i][j] = 0;
                } else {
                    a[i][j] = 1;
                }
            }
        }
        preprocess(n, m);
        cout << BIN(n, m, k) << endl;

    }

    return 0;
}
