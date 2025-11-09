//https://leetcode.com/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array/description/
class Solution {
public:
    long long numGoodSubarrays(vector<int>& a, int k) {
        map<int, int> mp;
        int n = a.size();
        vector<int> pref(n);
        long long ans = a[0] % k == 0;
        pref[0] = a[0] % k;

        int l = -1, last = a[0], sz = 1, sum = a[0] % k;
        for (int i = 1; i < n; i++) {
            sum = (sum + a[i]) % k;
            pref[i] = sum;
            if (a[i] == last) {
                sz++;
                if (((long long)last * sz) % k == 0) {
                    ans++;
                }
            } else {
                for (int j = l; j < i - 1; j++) {
                    if (j == -1) {
                        mp[0]++;
                    } else {
                        mp[pref[j]]++;
                    }
                }
                l = i - 1;
                last = a[i];
                sz = 1;
                if (((long long)last * sz) % k == 0) {
                    ans++;
                }
            }
            ans += mp[sum];
        }
        return ans;


    }
};
