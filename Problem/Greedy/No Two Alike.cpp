//https://www.codechef.com/problems/CPYD
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
bool seen[N];
vector<int> pos[N];

vector<long long> v(2, 0);

vector<vector<long long>> interval_union(vector<vector<long long>>& intervals) {
    vector<vector<long long>> ans;
    if (intervals.size() == 0) {
        return ans;
    }
    sort(intervals.begin(), intervals.end());
    int active = 0;
    priority_queue<long long> pq;
    for (int i = 0; i < intervals.size(); i++) {
        while (pq.size() && -pq.top() + 1 < intervals[i][0]) {
            int r = -pq.top();
            pq.pop();
            active--;
            if (active == 0) {
                ans[ans.size() - 1][1] = r;
            }
        }
        if (active == 0) {
            vector<long long> v(2, 0);
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

int solve(int l, int r) {
    vector<int> upd;
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (!seen[a[i]]) {
            seen[a[i]] = true;
            ans += 1;
            upd.push_back(a[i]);
        }
    }
    for (int x : upd) {
        seen[x] = false;
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
            cin >> a[i];
            a[i]--;
            pos[a[i]].push_back(i);
        }
        vector<vector<long long>> ivals;
        for (int i = 0; i < n; i++) {
            if (pos[i].size() > 1) {
                v[0] = pos[i][0];
                v[1] = pos[i][pos[i].size() - 1];
                ivals.push_back(v);
            }
        }
        vector<vector<long long>> vv = interval_union(ivals);
        int ans = 0;
        for (int i = 0; i < vv.size(); i++) {
            int l = vv[i][0], r = vv[i][1];
            ans += solve(l, r);
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            pos[i].clear();
        }

    }

    return 0;
}
