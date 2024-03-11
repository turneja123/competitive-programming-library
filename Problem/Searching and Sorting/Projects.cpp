//solution for https://cses.fi/problemset/task/1140/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

tuple<long long, long long, long long> a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> get<0>(a[i]) >> get<2>(a[i]) >> get<1>(a[i]);
    }
    sort(a, a + n);
    priority_queue<pair<long long, long long>> pq;
    long long best = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long cur = get<0>(a[i]);
        while (pq.size() && -(pq.top().first) < cur) {
            best = max(best, pq.top().second);
            pq.pop();
        }
        long long now = best + get<1>(a[i]);
        ans = max(ans, now);
        pq.push({-get<2>(a[i]), now});
    }
    cout << ans << endl;
    return 0;
}
