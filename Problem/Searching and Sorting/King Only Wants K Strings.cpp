//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            a[i] = {0, 0};
            for (int j = 0; j < s.size(); j++) {
                if (s[j] == '1') {
                    a[i].first++;
                } else {
                    a[i].second++;
                }
            }
        }
        sort(a.begin(), a.end());
        int ans = INF;
        priority_queue<int> pq;
        for (int i = 0; i < n;) {
            int x = a[i].first;
            while (i < n && a[i].first == x) {
                pq.push(a[i].second);
                i++;
            }
            while (pq.size() > k) {
                pq.pop();
            }
            if (pq.size() == k) {
                ans = min(ans, x + pq.top());
            }
        }
        cout << ans << endl;
    }

    return 0;
}
