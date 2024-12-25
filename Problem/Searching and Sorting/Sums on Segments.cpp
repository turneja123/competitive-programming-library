//https://codeforces.com/contest/2043/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int INF = 2e9;

int a[N];

vector<int> v(2, 0);
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
        while (pq.size() && -pq.top() + 1 < intervals[i][0]) {
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
        int ind = n - 1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (abs(a[i]) != 1) {
                ind = i;
            }
        }
        v[0] = 0, v[1] = 0;
        ivals.push_back(v);
        int suml = 0;
        set<int> stl;
        stl.insert(0);
        for (int i = 0; i < ind; i++) {
            suml += a[i];
            v[0] = suml - *stl.rbegin(), v[1] = suml - *stl.begin();
            ivals.push_back(v);
            stl.insert(suml);
        }
        v[0] = suml - *stl.rbegin() + a[ind], v[1] = suml - *stl.begin() + a[ind];
        ivals.push_back(v);
        int sumr = 0;
        set<int> str;
        str.insert(0);
        for (int i = ind + 1; i < n; i++) {
            sumr += a[i];
            v[0] = sumr - *str.rbegin(), v[1] = sumr - *str.begin();
            ivals.push_back(v);
            v[0] = sumr + suml + a[ind] - *stl.rbegin(), v[1] = sumr + suml + a[ind] - *stl.begin();

            ivals.push_back(v);
            str.insert(sumr);
        }
        ivals = interval_union(ivals);
        int ct = 0;
        for (int i = 0; i < ivals.size(); i++) {
            ct += ivals[i][1] - ivals[i][0] + 1;
        }
        cout << ct << endl;
        for (int i = 0; i < ivals.size(); i++) {
            for (int j = ivals[i][0]; j <= ivals[i][1]; j++) {
                cout << j << " ";
            }
        }
        cout << endl;
        ivals.clear();

    }
    return 0;
}
