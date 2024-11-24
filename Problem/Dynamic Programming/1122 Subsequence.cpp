//https://atcoder.jp/contests/abc381/tasks/abc381_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

vector<int> pos[K];
int dist[1 << K];
int up[K][N];
int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < K; j++) {
            int ind = lower_bound(pos[j].begin(), pos[j].end(), i) - pos[j].begin() + 1;
            if (ind >= pos[j].size()) {
                up[j][i] = -1;
            } else {
                up[j][i] = pos[j][ind] + 1;
            }
        }
    }

    for (int i = 0; i < 1 << K; i++) {
        dist[i] = N;
    }
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, 0));
    dist[0] = 0;
    while (pq.size()) {
        int d = -pq.top().first, mask = pq.top().second;
        pq.pop();
        if (d != dist[mask] || d == n) {
            continue;
        }
        for (int j = 0; j < K; j++) {
            int c = mask & (1 << j);
            if (!c) {
                if (up[j][d] != -1 && up[j][d]  < dist[mask | (1 << j)]) {
                    dist[mask | (1 << j)] = up[j][d];
                    pq.push(make_pair(-up[j][d], mask | (1 << j)));
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < 1 << K; i++) {
        int s = __builtin_popcount(i);
        if (dist[i] <= n) {
            ans = max(ans, s);
        }
    }
    cout << 2 * ans;

    return 0;
}
