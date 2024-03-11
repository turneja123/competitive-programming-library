//https://leetcode.com/problems/earliest-second-to-mark-indices-i/description/
class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();
        int l = n, r = m, ans = m + 1;
        while (l <= r) {
            bool good = true;
            int mid = (l + r) / 2;
            vector<int> rightmost(n, -1);
            vector<bool> flag(mid, false);
            for (int i = 0; i < mid; i++) {
                rightmost[changeIndices[i] - 1] = i;
            }
            priority_queue<pair<int, int>> pq;
            for (int i = 0; i < n; i++) {
                if (rightmost[i] == -1) {
                    good = false;
                }
                pq.push(make_pair(-rightmost[i], i));
            }
            if (!good) {
                l = mid + 1;
                continue;
            }
            int j = 0;
            while (pq.size() && good) {
                int i = nums[pq.top().second], k = -pq.top().first;
                while (j < k && i > 0) {
                    if (!flag[j]) {
                        flag[j] = true;
                        i--;
                    }
                    j++;
                }
                if (j == k && i > 0) {
                    good = false;
                } else {
                    flag[k] = true;
                }
                pq.pop();
            }
            if (!good) {
                l = mid + 1;
            } else {
                ans = min(ans, mid);
                r = mid - 1;
            }
        }
        if (ans == m + 1) {
            return -1;
        }
        return ans;
        
        
    }
};