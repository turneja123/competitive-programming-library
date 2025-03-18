//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136697
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void preprocess(int n, int m, vector<vector<int>> &a, vector<vector<int>> &pref) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = max(0, a[i][j]) + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

int query(int x1, int y1, int x2, int y2, vector<vector<int>> &pref) {
    int ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 4, vector<int>(m + 4, -1)), ct(n + 4, vector<int>(m + 4, 1));
    vector<vector<int>> pref(n + 4, vector<int>(m + 4, 0)), prefct = pref;

    for (int i = 2; i <= n + 1; i++) {
        for (int j = 2; j <= m + 1; j++) {
            cin >> a[i][j];
            if (a[i][j] != -1) {
                ct[i][j] = 0;
            }
        }
    }
    n += 4, m += 4;
    preprocess(n, m, a, pref);
    preprocess(n, m, ct, prefct);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1) {
                continue;
            }
            int l = 0, r = min(n, m), sz = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x1 = i - mid, y1 = j - mid, x2 = i + mid, y2 = j + mid;
                if (x1 < 0 || y1 < 0 || x2 >= n || y2 >= m) {
                    r = mid - 1;
                    continue;
                }
                int ct = query(x1, y1, x2, y2, prefct);
                if (ct == 0) {
                    l = mid + 1;
                    sz = mid;
                } else {
                    r = mid - 1;
                }
            }
            int square = query(i - sz, j - sz, i + sz, j + sz, pref);
            sz++;
            if (a[i + sz][j + sz - 1] == -1) {
                ans = max(ans, square);
                continue;
            }
            //LURD
            int path = 0;
            //L
            int ctL = query(i + sz, j - sz, i + sz, j + sz - 1, prefct);
            if (ctL) {
                int l = j - sz, r = j + sz - 1, best = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int ct = query(i + sz, mid, i + sz, j + sz - 1, prefct);
                    if (ct == 0) {
                        best = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (best != -1) {
                    path += query(i + sz, best, i + sz, j + sz - 1, pref);
                }
                ans = max(ans, square + path);
                continue;
            }
            path += query(i + sz, j - sz, i + sz, j + sz - 1, pref);
            //U
            int ctU = query(i - sz, j - sz, i + sz - 1, j - sz, prefct);
            if (ctU) {
                int l = i - sz, r = i + sz - 1, best = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int ct = query(mid, j - sz, i + sz - 1, j - sz, prefct);
                    if (ct == 0) {
                        best = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (best != -1) {
                    path += query(best, j - sz, i + sz - 1, j - sz, pref);
                }
                ans = max(ans, square + path);
                continue;
            }
            path += query(i - sz, j - sz, i + sz - 1, j - sz, pref);
            //R
            int ctR = query(i - sz, j - sz + 1, i - sz, j + sz, prefct);
            if (ctR) {
                int l = j - sz + 1, r = j + sz, best = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int ct = query(i - sz, j - sz + 1, i - sz, mid, prefct);
                    if (ct == 0) {
                        best = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                if (best != -1) {
                    path += query(i - sz, j - sz + 1, i - sz, best, pref);
                }
                ans = max(ans, square + path);
                continue;
            }
            path += query(i - sz, j - sz + 1, i - sz, j + sz, pref);
            //D
            int ctD = query(i - sz + 1, j + sz, i + sz, j + sz, prefct);
            if (ctD) {
                int l = i - sz + 1, r = i + sz, best = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int ct = query(i - sz + 1, j + sz, mid, j + sz, prefct);
                    if (ct == 0) {
                        best = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                if (best != -1) {
                    path += query(i - sz + 1, j + sz, best, j + sz, pref);
                }
                ans = max(ans, square + path);
                continue;
            }
        }
    }
    cout << ans;

    return 0;
}
