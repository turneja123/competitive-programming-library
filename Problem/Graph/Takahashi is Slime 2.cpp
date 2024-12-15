//https://atcoder.jp/contests/abc384/tasks/abc384_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

long long a[N][N];
bool seen[N][N];

int main() {
    IOS;
    int n, m; long long k;
    cin >> n >> m >> k;
    int p, q;
    cin >> p >> q;
    p--, q--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    long long val = 0;
    priority_queue<pair<long long, pair<int, int>>> pq;
    pq.push(make_pair(-a[p][q], make_pair(p, q)));
    seen[p][q] = true;

    while (pq.size()) {
        long long d = -pq.top().first;
        auto [x, y] = pq.top().second;
        if (x == p && y == q) {
            val += d;
        } else {
            long long can = val / k;
            if (val % k != 0) {
                can++;
            }
            if (d >= can) {
                break;
            }
            val += d;
        }
        pq.pop();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !seen[x + dx][y + dy]) {
                    pq.push(make_pair(-a[x + dx][y + dy], make_pair(x + dx, y + dy)));
                    seen[x + dx][y + dy] = true;
                }
            }
        }
    }
    cout << val;



    return 0;
}
