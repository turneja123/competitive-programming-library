//https://judge.beecrowd.com/en/problems/view/1691
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1e4 + 5;

ld pi = 3.1415926535897932384626433832;
ld eps = 1e-9;
vector<ld> v(2, 0);

vector<vector<ld>> interval_union(vector<vector<ld>>& intervals) {
    vector<vector<ld>> ans;
    if (intervals.size() == 0) {
        return ans;
    }
    sort(intervals.begin(), intervals.end());
    int active = 0;
    priority_queue<ld> pq;
    for (int i = 0; i < intervals.size(); i++) {
        while (pq.size() && -pq.top() < intervals[i][0]) {
            ld r = -pq.top();
            pq.pop();
            active--;
            if (active == 0) {
                ans[ans.size() - 1][1] = r;
            }
        }
        if (active == 0) {
            vector<ld> v(2, 0);
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

vector<vector<ld>> interval_intersect(vector<vector<ld>>& ans, vector<vector<ld>>& add) {
    vector<vector<ld>> temp;
    int ip = 0, jp = 0;
    while (ip < ans.size() && jp < add.size()) {
        v[0] = max(ans[ip][0], add[jp][0]), v[1] = min(ans[ip][1], add[jp][1]);
        if (v[0] <= v[1]) {
            temp.push_back(v);
        }
        if (ans[ip][1] < add[jp][1]) {
            ip++;
        } else {
            jp++;
        }
    }
    return temp;
}

vector<vector<ld>> ivals[N];

vector<vector<ld>> extend(vector<vector<ld>> &cur, ld len) {
    vector<vector<ld>> ans;
    for (int i = 0; i < cur.size(); i++) {
        ld l = cur[i][0], r = cur[i][1];

        if (l - len < 0) {
            ld L = 2 * pi + (l - len);
            v[0] = L, v[1] = 2 * pi;
            ans.push_back(v);
            l = 0;
        } else {
            l -= len;
        }
        if (r + len > 2 * pi) {
            ld R = r + len - 2 * pi;
            v[0] = 0, v[1] = R;
            ans.push_back(v);
            r = 2 * pi;
        } else {
            r += len;
        }
        v[0] = l, v[1] = r;
        ans.push_back(v);
    }
    return interval_union(ans);
}

int calc(int n, ld len) {

    vector<vector<ld>> cur;
    v[0] = 0, v[1] = 2.0 * pi;
    cur.push_back(v);

    for (int i = 0; i < n; i++) {
        cur = extend(cur, len);
        cur = interval_intersect(cur, ivals[i]);
        if (cur.empty()) {
            return 0;
        }
    }
    return 1;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(4);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            vector<vector<ld>> walls;
            vector<ld> v(2, 0);
            for (int j = 0; j < k; j++) {
                ld l, r;
                cin >> l >> r;
                if (l <= r) {
                    v[0] = l, v[1] = r;
                    walls.push_back(v);
                } else {
                    v[0] = 0, v[1] = r;
                    walls.push_back(v);
                    v[0] = l, v[1] = 2 * pi;
                    walls.push_back(v);

                }
            }
            sort(walls.begin(), walls.end());
            ld last = 0.0;
            for (int j = 0; j < walls.size(); j++) {
                if (last < walls[j][0]) {
                    v[0] = last, v[1] = walls[j][0];
                    ivals[i].push_back(v);
                }
                last = walls[j][1];
            }
            v[0] = last, v[1] = 2.0 * pi;
            if (v[0] < v[1]) {
                ivals[i].push_back(v);
            }
        }
        ld l = 0, r = 1.0 - eps, ans = r;


        for (int it = 0; it < 60; it++) {
            ld mid = (l + r) / 2.0;
            int can = calc(n, mid * 2.0 * pi);
            if (can) {
                ans = mid;
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;

        for (int i = 0; i < n; i++) {
            ivals[i].clear();
        }

    }

    return 0;
}
