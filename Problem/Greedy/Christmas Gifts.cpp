//https://repovive.com/contests/5/problems/C
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
    while  (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<int> vis(n, 0);
        vector<int> ans(n, 0);
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
            pq.push(make_pair(a[i], i));
        }
        while (pq.size()) {
            auto [x, i] = pq.top();
            pq.pop();
            if (vis[i]) {
                continue;
            }
            vis[i] = 1;
            ans[i] = x;
            if (i != 0) {
                pq.push(make_pair(max(a[i - 1], x - b[i - 1]), i - 1));
            }
            if (i != n - 1) {
                pq.push(make_pair(max(a[i + 1], x - b[i + 1]), i + 1));
            }
        }
        ll s = 0;
        for (int i = 0; i < n; i++) {
            s += ans[i];
        }
        cout << s << endl;
    }
    return 0;
}
