//https://codesprintla26.kattis.com/contests/codesprintla26open/problems/mappingthegreatsea
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int b[N][N];
int pref[N][N];

void preprocess(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = b[i][j] + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

int query(int x1, int y1, int x2, int y2) {
    int ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    int m = n;
    vector<vector<int>> a(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> heights(n, vector<int>(m, 0));
    vector<vector<int>> add(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n;) {
            if (a[j][i] == 0) {
                heights[j][i] = 0;
                j++;
            } else {
                int r = j, A = 1;
                while (r < n && a[r][i] == 1) {
                    r++;
                }
                for (int k = r - 1; k >= j; k--) {
                    heights[k][i] = A++;
                }
                j = r;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        stack<int> s;
        vector<int> l(m, 0);
        vector<int> r(m, 0);
        for (int j = 0; j < m; j++) {
            while (s.size() && heights[i][s.top()] >= heights[i][j]) {
                s.pop();
            }
            if (s.empty()) {
                l[j] = -1;
            } else {
                l[j] = s.top();
            }
            s.push(j);

        }
        while (!s.empty()) {
            s.pop();
        }
        for (int j = m - 1; j >= 0 ; j--) {
            while (s.size() && heights[i][s.top()] > heights[i][j]) {
                s.pop();
            }
            if (s.empty()) {
                r[j] = m;
            } else {
                r[j] = s.top();
            }
            s.push(j);
        }
        vector<int> pref(m, 0);
        for (int j = 0; j < m; j++) {
            pref[j] = (j == 0 ? 0 : pref[j - 1]) + (i == 0 ? 0 : a[i - 1][j]);
        }

        for (int j = 0; j < m; j++) {
            if (heights[i][j] == 0 || (r[j] != m && heights[i][j] == heights[i][r[j]]) || (pref[r[j] - 1] - (l[j] == -1 ? 0 : pref[l[j]]) == r[j] - l[j] - 1)) {
                continue;
            }
            ans++;
            add[i][l[j] + 1]++;
            add[i + heights[i][j]][r[j]]++;
            add[i][r[j]]--;
            add[i + heights[i][j]][l[j] + 1]--;
        }

    }
    cout << ans << " ";
    ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            add[i][j] += (i == 0 ? 0 : add[i - 1][j]) + (j == 0 ? 0 : add[i][j - 1]) - (i == 0 || j == 0 ? 0 :  add[i - 1][j - 1]);
            b[i][j] = add[i][j] == 1;
        }
    }
    preprocess(n, m);
    for (int i = 0; i < n; i++) {
        stack<int> s;
        vector<int> l(m, 0);
        vector<int> r(m, 0);
        for (int j = 0; j < m; j++) {
            while (s.size() && heights[i][s.top()] >= heights[i][j]) {
                s.pop();
            }
            if (s.empty()) {
                l[j] = -1;
            } else {
                l[j] = s.top();
            }
            s.push(j);

        }
        while (!s.empty()) {
            s.pop();
        }
        for (int j = m - 1; j >= 0 ; j--) {
            while (s.size() && heights[i][s.top()] > heights[i][j]) {
                s.pop();
            }
            if (s.empty()) {
                r[j] = m;
            } else {
                r[j] = s.top();
            }
            s.push(j);
        }
        vector<int> pref(m, 0);
        for (int j = 0; j < m; j++) {
            pref[j] = (j == 0 ? 0 : pref[j - 1]) + (i == 0 ? 0 : a[i - 1][j]);
        }

        for (int j = 0; j < m; j++) {
            if (heights[i][j] == 0 || (r[j] != m && heights[i][j] == heights[i][r[j]]) || (pref[r[j] - 1] - (l[j] == -1 ? 0 : pref[l[j]]) == r[j] - l[j] - 1)) {
                continue;
            }
            if (query(i, l[j] + 1, i + heights[i][j] - 1, r[j] - 1)) {
                ans++;
            }
        }

    }
    cout << ans;


    return 0;
}
