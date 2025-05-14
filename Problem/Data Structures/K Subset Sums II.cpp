//https://cses.fi/problemset/task/3109
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long INF = 1e15;

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    long long l = 0, r = 0, spl = -INF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < 0) {
            l += a[i];
        } else {
            r += a[i];
        }
    }
    sort(a.begin(), a.end());

    vector<long long> ans;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long s = 0;
        for (int i = 0; i < m; i++) {
            s += a[i];
        }
        if (s > mid) {
            l = mid + 1;
            continue;
        }
        priority_queue<tuple<long long, int, int>> pq;
        pq.push(make_tuple(-s, m - 1, m));
        vector<long long> cur{s};
        while (pq.size() && cur.size() < k) {
            auto [s, i, j] = pq.top();
            s = -s;
            pq.pop();
            if (i == n - 1) {
                continue;
            }
            for (int d = 1; d <= j; d++) {
                long long add = a[i + 1] - a[i - d + 1];
                if (s + add <= mid && cur.size() < k) {
                    pq.push(make_tuple(-(s + add), i + 1, d));
                    cur.push_back(s + add);
                } else {
                    break;
                }
            }
        }
        if (cur.size() == k) {
            spl = mid;
            r = mid - 1;
        } else {
            ans = cur;
            l = mid + 1;
        }
    }
    sort(ans.begin(), ans.end());
    for (long long x : ans) {
        cout << x << " ";
    }
    for (int i = ans.size(); i < k; i++) {
        cout << spl << " ";
    }
    return 0;
}
