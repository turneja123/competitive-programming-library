//https://leetcode.com/problems/merge-intervals/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
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
};