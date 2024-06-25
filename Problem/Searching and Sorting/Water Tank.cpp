//https://atcoder.jp/contests/abc359/tasks/abc359_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long sum = a[1];
    ans[1] = sum + 1;
    priority_queue<pair<long long, int>> pq;
    pq.push(make_pair(-a[1], 1));

    for (int i = 2; i <= n; i++) {
        int ct = 1;
        while (pq.size() && -pq.top().first < a[i]) {
            sum -= (long long)-pq.top().first * pq.top().second;
            sum += a[i] * pq.top().second;
            ct += pq.top().second;
            pq.pop();
        }
        sum += (long long)a[i];
        ans[i] = sum + 1;
        pq.push(make_pair(-a[i], ct));
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
