#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int M = 1e6 + 5;

int a[N][N];
int ct[M];
pair<int, int> yx[M];


int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        yx[i].first = -1;
        yx[i].second = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (yx[a[i][j]].first == -1) {
                yx[a[i][j]].first = i;
                yx[a[i][j]].second = j;
            }
            ct[a[i][j]]++;
        }
    }
    int ans = 0;
    for (int m = 1; m <= k; m++) {
        int y = yx[m].first;
        int x = yx[m].second;
        if (y == -1) {
            continue;
        }
        int cur = 0;
        int lim = x;
        while (lim < n && a[y][lim] == m) {
            cur++;
            lim++;
        }
        bool flag = true;
        for (int i = y + 1; i < n; i++) {
            if (a[i][x] != m || !flag) {
                break;
            }
            for (int j = x; j < lim; j++) {
                if (a[i][j] != m) {
                    flag = false;
                    break;
                }
                cur++;
            }
        }
        if (flag && cur == ct[m]) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
