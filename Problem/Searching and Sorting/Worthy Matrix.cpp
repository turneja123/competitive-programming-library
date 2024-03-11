//solution for https://www.codechef.com/APRIL21C/problems/KAVGMAT
#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> a;
vector<vector<long long>> pref;
vector<vector<long long>> col;

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

long long query(int y1, int x1, int y2, int x2) {

    long long ret = pref[y2][x2];
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

long long binsearch(int x, int y, int n, int m, int k) {
    int l = 0;
    int r = min(m - y, n - x) - 1;
    long long mn = max(n + 1, m + 1);
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long val = query(x, y, x + mid, y + mid) / ((mid + 1) * (mid + 1));
        if (val >= k) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mn;


}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            vector<long long> v;
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;
                v.push_back(x);
            }
            a.push_back(v);
            pref.push_back(v);
            col.push_back(v);

        }
        preprocess(n, m);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int mov = binsearch(i, j, n, m, k);
                ans += min(max(0, n - (i + mov)), max(0, m - (j + mov)));
            }
        }
        cout << ans << endl;
        a.clear();
        pref.clear();
        col.clear();

    }
    return 0;
}
