//https://toph.co/arena?practice=668ee600a4f184cd2ac3fb1f#!/p/65b13bf9fb1dbd27709c36b7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> pos[26];
int idx[26];

vector<int> v(2, 0);

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

vector<vector<int>> interval_intersect(vector<vector<int>>& ans, vector<vector<int>>& add) {
    vector<vector<int>> temp;
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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'].push_back(i);
        }
        int ans = 1;
        for (int i = 0; i < n; i++) {
            vector<vector<int>> last;
            int r = -1;
            for (int j = 0; j < 26; j++) {
                if (idx[j] == pos[j].size()) {
                    r = n - 1;
                } else {
                    r = max(r, pos[j][idx[j]] - 1);
                }
            }
            v[0] = i, v[1] = r;
            last.push_back(v);
            for (int k = 1; k < 26 && last.size(); k++) {
                vector<vector<int>> cur;
                for (int j = 0; j < 26; j++) {
                    if (idx[j] + k - 1 >= pos[j].size()) {
                        continue;
                    }
                    int l = pos[j][idx[j] + k - 1], r = ((idx[j] + k == pos[j].size()) ? n - 1 : pos[j][idx[j] + k] - 1);
                    v[0] = l, v[1] = r;
                    cur.push_back(v);
                }
                cur = interval_union(cur);
                last = interval_intersect(last, cur);
                if (last.size() != 0) {
                    ans = max(ans, k + 1);
                }
            }
            idx[s[i] - 'a']++;
        }
        cout << ans << endl;
        for (int i = 0; i < 26; i++) {
            pos[i].clear();
            idx[i] = 0;
        }
    }
    return 0;
}
