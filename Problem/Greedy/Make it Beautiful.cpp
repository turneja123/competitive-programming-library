//https://codeforces.com/contest/2118/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long k;
        cin >> n >> k;
        priority_queue<pair<int, long long>> pq;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            for (int j = 0; j < 62; j++) {
                long long c = (1ll << j) & a;
                if (!c) {
                    pq.push(make_pair(-j, a));
                    break;
                }
            }
            ans += __builtin_popcount(a);
        }
        while (pq.size()) {
            auto [j, a] = pq.top();
            j = -j;
            pq.pop();
            long long cost = (1ll << j);
            if (cost > k) {
                break;
            }
            k -= cost;
            a |= cost;
            ans++;
            for (int j = 0; j < 62; j++) {
                long long c = (1ll << j) & a;
                if (!c) {
                    pq.push(make_pair(-j, a));
                    break;
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
