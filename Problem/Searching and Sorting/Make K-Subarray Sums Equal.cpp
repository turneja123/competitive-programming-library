//https://leetcode.com/contest/biweekly-contest-101/problems/make-k-subarray-sums-equal/
class Solution {
public:
    long long solve(vector<int> &a) {
        sort(a.begin(), a.end());
        int n = a.size();
        long long pref = 0, suf = 0, ans = 1e18;
        for (int i = 0; i < n; i++) {
            suf += a[i];
        }
        for (int i = 0; i < n; i++) {
            pref += a[i], suf -= a[i];
            ans = min(ans, (long long)a[i] * (i + 1) - pref + suf - (long long)a[i] * (n - 1 - i));
        }
        return ans;
    }

    long long makeSubKSumEqual(vector<int>& arr, int k) {
        long long ans = 0;
        int n = arr.size();
        k = __gcd(n, k);
        for (int i = 0; i < k; i++) {
            vector<int> a;
            for (int j = i; j < n; j += k) {
                a.push_back(arr[j]);
            }
            ans += solve(a);
        }
        return ans;
    }
};
