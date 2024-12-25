//https://leetcode.com/contest/biweekly-contest-146/problems/check-if-grid-can-be-cut-into-sections/
const int N = 2;
class Solution {
public:
    vector<long long> v;

    vector<vector<long long>> interval_union(vector<vector<long long>>& intervals) {
        vector<vector<long long>> ans;
        if (intervals.size() == 0) {
            return ans;
        }
        sort(intervals.begin(), intervals.end());
        int active = 0;
        priority_queue<long long> pq;
        for (int i = 0; i < intervals.size(); i++) {
            while (pq.size() && -pq.top() <= intervals[i][0]) {
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

    bool checkValidCuts(int n, vector<vector<int>>& a) {
        v.resize(2);
        vector<vector<long long>> row, col;
        for (int i = 0; i < a.size(); i++) {
            v[0] = a[i][0], v[1] = a[i][2];
            row.push_back(v);
            v[0] = a[i][1], v[1] = a[i][3];
            col.push_back(v);
        }
        row = interval_union(row), col = interval_union(col);
        if (row.size() >= 3 || col.size() >= 3) {
            return true;
        }
        return false;
    }
};
