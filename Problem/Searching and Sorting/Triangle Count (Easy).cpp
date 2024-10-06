//https://www.codechef.com/problems/TRICOUNT1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

vector<vector<int>> ivals;

vector<vector<int>> interval_union(vector<vector<int>>& intervals) {
    vector<vector<int>> ans;
    if (intervals.size() == 0) {
        return ans;
    }
    sort(intervals.begin(), intervals.end());
    int active = 0;
    priority_queue<int> pq;
    for (int i = 0; i < intervals.size(); i++) {
        while (pq.size() && -pq.top() < intervals[i][0]) {
            int r = -pq.top();
            pq.pop();
            active--;
            if (active == 0) {
                ans[ans.size() - 1][1] = r;
            }
        }
        if (active == 0) {
            vector<int> v(2, 0);
            v[0] = intervals[i][0];
            ans.push_back(v);
        }
        active++;
        pq.push(-intervals[i][1]);
    }
    while (pq.size()) {
        ans[ans.size() - 1][1] = -pq.top();
        pq.pop();
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

        vector<int> v(2, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        for (int i = 0; i < n - 1; i++) {
            int r = a[i], l = a[i + 1] - a[i];
            if (l <= r) {
                v[0] = l, v[1] = r;
                ivals.push_back(v);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            int r = a[i + 1], l = a[i];
            l = max(l, a[i + 1] - a[i]);
            if (l <= r) {
                v[0] = l, v[1] = r;
                ivals.push_back(v);
            }
        }
        for (int i = 1; i < n; i++) {
            int l = a[i], r = a[i] + a[i - 1] - 1;
            if (l <= r) {
                v[0] = l, v[1] = r;
                ivals.push_back(v);
            }
        }
        vector<vector<int>> ans = interval_union(ivals);
        int sum = 0;
        for (int i = 0; i < ans.size(); i++) {
            sum += ans[i][1] - ans[i][0];
        }
        cout << sum << endl;
        ivals.clear();

    }

    return 0;
}
