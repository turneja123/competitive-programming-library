//https://atcoder.jp/contests/abc359/tasks/abc359_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N], d[N];

int main() {
    IOS;
    int n;
    cin >> n;
    priority_queue<pair<long long, int>> pq;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
        d[i] = 1;
        long long nw = a[i] * (d[i] + 1) * (d[i] + 1) - a[i] * d[i] * d[i];
        pq.push(make_pair(-nw, i));
    }
    for (int i = 0; i < n - 2; i++) {
        int u = pq.top().second; long long wt = -pq.top().first;
        ans += wt;
        d[u]++;
        long long nw = a[u] * (d[u] + 1) * (d[u] + 1) - a[u] * d[u] * d[u];
        pq.pop();
        pq.push(make_pair(-nw, u));
    }
    cout << ans;
    return 0;
}
