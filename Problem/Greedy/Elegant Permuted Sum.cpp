//https://www.spoj.com/problems/ELPESUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        deque<int> q;
        q.push_back(a[n - 1]);
        int l = 0, r = n - 2;
        while (l <= r) {
            q.push_front(a[l]);
            l++;
            if (l > r) {
                break;
            }
            q.push_back(a[l]);
            l++;
            if (l > r) {
                break;
            }
            q.push_front(a[r]);
            r--;
            if (l > r) {
                break;
            }
            q.push_back(a[r]);
            r--;
        }
        int x = 0, cur = q.front();
        q.pop_front();
        while (q.size()) {
            x += abs(cur - q.front());
            cur = q.front();
            q.pop_front();
        }

        q.push_back(a[0]);
        l = 1, r = n - 1;
        while (l <= r) {
            q.push_front(a[r]);
            r--;
            if (l > r) {
                break;
            }
            q.push_back(a[r]);
            r--;
            if (l > r) {
                break;
            }
            q.push_front(a[l]);
            l++;
            if (l > r) {
                break;
            }
            q.push_back(a[l]);
            l++;
        }
        int y = 0; cur = q.front();
        q.pop_front();
        while (q.size()) {
            y += abs(cur - q.front());
            cur = q.front();
            q.pop_front();
        }

        cout << "Case " << tt << ": " << max(x, y) << endl;
    }
    return 0;
}
