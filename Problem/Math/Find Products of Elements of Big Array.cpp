//https://leetcode.com/problems/find-products-of-elements-of-big-array/description/
class Solution {
public:
    long long ct[64];
    
    long long modPow(long long a, long long y, long long M) {
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
    
    long long bits(long long n, long long k) {
        long long ans = (n >> (k + 1)) << k;
        if ((n >> k) & (long long)1) {
            ans += n & (((long long)1 << k) - 1);
        }
        return ans;
    }
    
    void calc(long long n, long long sgn) {
        if (n == 0) {
            return;
        }
        
        long long l = 1, r = 1e15, targ = 0;
        while (l <= r) {
            long long total = 0, mid = (l + r) / 2;
            long long pw = 1;
            for (int i = 0; pw <= mid; i++, pw *= 2) {
                total += bits(mid + 1, i);
            }
            if (total <= n) {
                targ = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        long long pw = 1, remain = n;
        for (int i = 0; pw <= targ; i++, pw *= 2) {
            long long b = bits(targ + 1, i);
            ct[i] += b * sgn;
            remain -= b;
        }
        targ++;
        pw = 1;
        for (long long i = 0; pw <= targ && remain > 0; i++, pw *= 2) {
            long long c = targ & pw;
            if (c > 0) {
                ct[i] += sgn;
                remain--;
            }
        }
        return;
    }
     
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        int n = queries.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            long long a = queries[i][0], b = queries[i][1], m = queries[i][2];
            calc(b + 1, 1);
            calc(a, -1);
            long long cur = 0;
            for (int j = 1; j < 64; j++) {
                cur += ct[j] * j;
            }
            long long pows = modPow(2, cur, m);
            ans.push_back(pows % m);
            for (int j = 0; j < 64; j++) {
                ct[j] = 0;
            }
        }
        
        return ans;
    }
};