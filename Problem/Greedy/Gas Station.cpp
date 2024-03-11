//https://leetcode.com/problems/gas-station/description/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            a[i] = gas[i] - cost[i];
        }
        int max = -1, ind = -1, sum = -1, ans = -1;
        for (int i = 0; i < 2 * n; i++) {
            if (sum < 0 && a[i % n] >= 0) {
                sum = a[i % n];
                ind = i % n;
            } else {
                sum += a[i % n];
            }
            if (sum > max) {
                max = sum;
                ans = ind;
            }
        }
        sum = 0;
        for (int i = ans; i < ans + n; i++) {
            sum += a[i % n];
            if (sum < 0) {
                return -1;
            }
        }
        return ans;
    }
};