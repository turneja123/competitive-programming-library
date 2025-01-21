//https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/description/
class Solution {
public:
    const long long M = 1e9 + 7;
    long long modPow(long long a, long long y) {
        long long res = 1;
        while(y > 0) {
            if(y % 2 != 0) {
                res = (res * a) % M;
            }
            y /= 2;
            a = (a * a) % M;
        }
        return res;
    }

    vector<int> getFinalState(vector<int>& nums, int k, int m) {
        if (m == 1) {
            return nums;
        }
        priority_queue<pair<long long, int>> pq;
        long long mx = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mx = max(mx, (long long)nums[i]);
            pq.push(make_pair(-nums[i], -i));
        }
        while (k > 0) {
            long long x = -pq.top().first; int j = -pq.top().second;
            if (x * m > mx) {
                break;
            }
            nums[j] = x * m;
            pq.pop();
            pq.push(make_pair(-nums[j], -j));
            k--;
        }
        vector<pair<long long, int>> sorted;
        for (int i = 0; i < n; i++) {
            sorted.push_back(make_pair(nums[i], i));
        }
        sort(sorted.begin(), sorted.end());
        long long ct = k / n;
        for (int i = 0; i < k % n; i++) {
            nums[sorted[i].second] = sorted[i].first % M * modPow(m, ct + 1) % M;
        }
        for (int i = k % n; i < n; i++) {
            nums[sorted[i].second] = sorted[i].first % M * modPow(m, ct) % M;
        }
        return nums;
    }
};
