//https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-2/problems/C
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int bit[N][N];

void update(int x, int y, int n, int m, int val){
    for (int i = x; i <= n; i += -i & i) {
        for (int j = y; j <= m; j += -j & j) {
            bit[i][j] += val;
        }
    }
}

int query(int x, int y){
    int sum = 0;
    for (int i = x; i > 0; i -= -i & i) {
        for (int j = y; j > 0; j -= -j & j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int calc(int x1, int y1, int x2, int y2) {
    int sum = query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    return sum;
}

vector<pair<int, int>> pos[N * N];

int main() {
    //IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, m; long long k;
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
                update(i, j, n, m, 1);
                pos[a[i][j]].push_back(make_pair(i, j));
            }
        }
        int l = 1, r = n + m, ans = r;
        while (l <= r) {
            int mid = (l + r) / 2;
            long long ct = 0;
            for (int p = 1; p <= n * m; p++) {
                for (auto [x, y] : pos[p]) {
                    update(x, y, n, m, -1);
                }
                for (auto [x, y] : pos[p]) {
                    ct += calc(max(1, x - mid), max(1, y - mid), min(n, x + mid), min(m, y + mid));
                }
                for (auto [x, y] : pos[p]) {
                    update(x, y, n, m, 1);
                }
            }
            if (ct >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        for (int p = 1; p <= n * m; p++) {
            pos[p].clear();
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                update(i, j, n, m, -1);
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;
    }


    return 0;
}
