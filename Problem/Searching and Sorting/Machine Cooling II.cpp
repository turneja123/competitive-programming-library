//https://www.spoj.com/problems/MACHCOOL2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];

int calc(int k, int n) {
    int ans = 86400;
    priority_queue<int> pq;
    for (int i = 0; i < k; i++) {
        pq.push(0);
    }
    for (int i = 0; i < n; i++) {
        int x = -pq.top();
        if (x > a[i].first) {
            return -1;
        }
        pq.pop();
        if (x != 0) {
            ans = min(ans, a[i].first - x);
        }
        pq.push(-a[i].second);
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            int x, b, c, d;
            cin >> x >> b >> c >> d;
            a[i].second = a[i].first + max({x, b, c, d});
        }
        sort(a, a + n);
        int l = 1, r = n, ans;
        while (l <= r) {
            int mid = (l + r) / 2;
            int val = calc(mid, n);
            if (val == -1) {
                l = mid + 1;
            } else {
                r = mid - 1;
                ans = val;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
