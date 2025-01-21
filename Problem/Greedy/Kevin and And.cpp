//https://codeforces.com/contest/2061/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int M = 11;
const int INF = 2e9;

int a[N];
int b[M];
int cost[N][M];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ans += a[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        vector<int> masks[m + 1];
        for (int j = 1; j < 1 << m; j++) {
            int mask = (1 << 30) - 1;
            for (int i = 0; i < m; i++) {
                int c = (1 << i) & j;
                if (c) {
                    mask &= b[i];
                }
            }
            masks[__builtin_popcount(j)].push_back(mask);
        }

        priority_queue<pair<int, pair<int, int>>> pq;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                cost[i][j] = INF;
                for (int k : masks[j]) {
                    cost[i][j] = min(cost[i][j], (int)a[i] & k);
                }
            }
            pq.push(make_pair(a[i] - cost[i][1], make_pair(i, 1)));
        }
        while (k > 0) {
            int d = pq.top().first;
            auto [i, j] = pq.top().second;
            pq.pop();
            a[i] -= d;
            ans -= d;
            if (j < m) {
                j++;
            }
            pq.push(make_pair(a[i] - cost[i][j], make_pair(i, j)));
            k--;
        }
        cout << ans << endl;
    }
    return 0;
}
