//https://leetcode.com/contest/biweekly-contest-143/problems/maximum-frequency-of-an-element-after-performing-operations-ii/
const int N = 1e5 + 5;
const int INF = 1e9 + 7;
class Solution {
public:
    pair<int, int> a[2 * N];
    map<int, int> freq;

    int maxFrequency(vector<int>& nums, int k, int ops) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            a[2 * i] = make_pair(nums[i] - k, nums[i] + k);
            a[2 * i + 1] = make_pair(nums[i], INF);
        }
        int ans = 0;
        sort(a, a + 2 * n);
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < 2 * n; i++) {
            while (pq.size() && pq.top() < a[i].first) {
                freq[pq.top() - k]--;
                pq.pop();
            }
            if (a[i].second != INF) {
                pq.push(a[i].second);
                freq[a[i].second - k]++;
                ans = max(ans, min((int)pq.size(), ops));
            } else {
                ans = max(ans, min((int)pq.size(), ops + freq[a[i].first]));

            }
        }
        return ans;
    }
};
