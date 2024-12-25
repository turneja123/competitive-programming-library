//https://atcoder.jp/contests/abc385/tasks/abc385_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

pair<int, int> a[N];

vector<long long> v(2, 0);

map<long long, vector<vector<long long>>> col;
map<long long, vector<vector<long long>>> row;

map<long long, vector<pair<long long, long long>>> coll;
map<long long, vector<pair<long long, long long>>> roww;

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

int main() {
    IOS;
    int n, m; long long x, y;
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < m; i++) {
        char c; int d;
        cin >> c >> d;
        if (c == 'U') {
            v[0] = y, v[1] = y + d;
            col[x].push_back(v);
            y += d;
        } else if (c == 'D') {
            v[0] = y - d, v[1] = y;
            col[x].push_back(v);
            y -= d;
        } else if (c == 'L') {
            v[0] = x - d, v[1] = x;
            row[y].push_back(v);
            x -= d;
        } else {
            v[0] = x, v[1] = x + d;
            row[y].push_back(v);
            x += d;
        }
    }
    for (auto it = col.begin(); it != col.end(); it++) {
        it->second = interval_union(it->second);
        for (int i = 0; i < (it->second).size(); i++) {
            coll[it->first].push_back(make_pair(it->second[i][0], it->second[i][1]));
        }
    }
    for (auto it = row.begin(); it != row.end(); it++) {
        it->second = interval_union(it->second);
        for (int i = 0; i < (it->second).size(); i++) {
            roww[it->first].push_back(make_pair(it->second[i][0], it->second[i][1]));
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int can = 0;
        int x = a[i].first, y = a[i].second;
        auto r = roww.find(y);
        if (r != roww.end()) {
            int it = upper_bound((r->second).begin(), (r->second).end(), make_pair((long long)x, INF)) - (r->second).begin();
            if (it != 0) {
                it--;
                if (x >= (r->second)[it].first && x <= (r->second)[it].second) {
                    can = 1;
                }
            }
        }
        auto c = coll.find(x);
        if (c != coll.end()) {
            int it = upper_bound((c->second).begin(), (c->second).end(), make_pair((long long)y, INF)) - (c->second).begin();
            if (it != 0) {
                it--;
                if (y >= (c->second)[it].first && y <= (c->second)[it].second) {
                    can = 1;
                }
            }
        }
        ans += can;
    }
    cout << x << " " << y << " " << ans;

    return 0;
}
