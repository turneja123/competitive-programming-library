//https://leetcode.com/contest/biweekly-contest-85/problems/maximum-segment-sum-after-removals/
const int N = 1e5 + 5;
class Solution {
public:
    int parent[N];
    int sz[N];
    int seen[N];
    long long sum[N];

    int dsu_find(int a) {
        while (parent[a] != a) {
            a = parent[a];
        }
        return a;
    }

    void dsu_unite(int a, int b) {
        if (sz[b] > sz[a]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        sum[a] += sum[b];
        parent[b] = a;
    }

    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        int n = removeQueries.size();
        for (int i = 0; i < n; i++) {
            sz[i] = 1, parent[i] = i, sum[i] = nums[i];
        }
        vector<long long> ans{0};
        long long cur = 0;
        for (int i = n - 1; i > 0; i--) {
            int j = removeQueries[i];
            seen[j] = true;
            if (j - 1 >= 0 && seen[j - 1]) {
                dsu_unite(dsu_find(j), dsu_find(j - 1));
            }
            if (j + 1 < n && seen[j + 1]) {
                dsu_unite(dsu_find(j), dsu_find(j + 1));
            }
            cur = max(cur, sum[dsu_find(j)]);
            ans.push_back(cur);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
