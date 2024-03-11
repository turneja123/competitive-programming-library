//https://atcoder.jp/contests/abc344/tasks/abc344_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 85;
const long long INF = 1e18;

pair<long long, long long> dp[N][N][N * N];
long long a[N][N];
long long r[N][N];
long long c[N][N];

long long values[N * N];
map<long long, int> pos;
tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> tr;

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            tr.insert(a[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cin >> r[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    int t = 0;
    for (auto it = tr.begin(); it != tr.end(); ++it) {
        values[t] = *it;
        pos[*it] = t;
        t++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < t; k++) {
                dp[i][j][k] = make_pair(INF, 0);
            }
        }
    }
    dp[0][0][pos[a[0][0]]] = make_pair(0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int cur = pos[a[i][j]];
            for (int k = 0; k < t; k++) {
                if (i > 0 && dp[i - 1][j][k].first != INF) {
                    long long add_first, add_second;
                    long long rm = -dp[i - 1][j][k].second;
                    if (rm >= c[i - 1][j]) {
                        add_first = 0;
                        add_second = rm - c[i - 1][j];
                    } else {
                        add_first = (c[i - 1][j] - rm) / values[k];
                        if ((c[i - 1][j] - rm) % values[k] > 0) {
                            add_first++;
                        }
                        add_second = add_first * values[k] + rm - c[i - 1][j];
                    }
                    dp[i][j][max(k, cur)] = min(dp[i][j][max(k, cur)], make_pair(dp[i - 1][j][k].first + add_first, -add_second));
                }
                if (j > 0 && dp[i][j - 1][k].first != INF) {
                    long long add_first, add_second;
                    long long rm = -dp[i][j - 1][k].second;
                    if (rm >= r[i][j - 1]) {
                        add_first = 0;
                        add_second = rm - r[i][j - 1];
                    } else {
                        add_first = (r[i][j - 1] - rm) / values[k];
                        if ((r[i][j - 1] - rm) % values[k] > 0) {
                            add_first++;
                        }
                        add_second = add_first * values[k] + rm - r[i][j - 1];
                    }
                    dp[i][j][max(k, cur)] = min(dp[i][j][max(k, cur)], make_pair(dp[i][j - 1][k].first + add_first, -add_second));
                }
            }
        }
    }
    long long ans = INF;
    for (int i = 0; i < t; i++) {
        ans = min(ans, dp[n - 1][n - 1][i].first);
    }
    cout << ans + (n - 1) * 2 << endl;

    return 0;
}
