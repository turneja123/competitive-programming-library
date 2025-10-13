//https://qoj.ac/contest/2539/problem/14433
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;

int a[N][N];
int ptr[N];
int last[N];

vector<int> col[N];


int main() {
    IOS;
    int n, k, m;
    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            col[j].push_back(a[i][j]);
        }
    }
    priority_queue<pair<int, int>> pq;
    for (int j = 0; j < n; j++) {
        sort(col[j].begin(), col[j].end());
        pq.push({0, j});
    }
    ll ans = 0;
    while (pq.size()) {
        auto [_, j] = pq.top();
        pq.pop();
        if (col[j][ptr[j]] - last[j] >= k) {
            ans += (ll)ptr[j] * k;
            break;
        }
        ans += (ll)ptr[j] * (col[j][ptr[j]] - last[j]);
        k -= col[j][ptr[j]] - last[j];
        last[j] = col[j][ptr[j]];
        ptr[j]++;
        pq.push({-ptr[j], j});
    }
    cout << ans;

    return 0;
}
