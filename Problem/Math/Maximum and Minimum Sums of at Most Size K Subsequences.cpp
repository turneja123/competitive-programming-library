//https://leetcode.com/contest/weekly-contest-433/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];
class Solution {
public:
     long long binomial(long long n, long long k) {
        if (n < k) {
            return 0;
        }
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        return;
    }


    int minMaxSums(vector<int>& nums, int k) {
        if (fact[0] == 0) {
            precalc();
        }
        map<int, int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }
        vector<pair<int, int>> freq;
        for (auto it : mp) {
            freq.push_back(it);
        }
        int m = n;
        long long ans = 0;
        for (int i = 0; i < freq.size(); i++) {
            m -= freq[i].second;
            for (int j = 1; j <= min(k, freq[i].second); j++) {
                for (int p = 0; p + j <= k; p++) {
                    ans += (long long)freq[i].first * binomial(freq[i].second, j) % M * binomial(m, p) % M;
                }
            }
            ans %= M;
        }
        m = n;
        reverse(freq.begin(), freq.end());
        for (int i = 0; i < freq.size(); i++) {
            m -= freq[i].second;
            for (int j = 1; j <= min(k, freq[i].second); j++) {
                for (int p = 0; p + j <= k; p++) {
                    ans += (long long)freq[i].first * binomial(freq[i].second, j) % M * binomial(m, p) % M;
                }
            }
            ans %= M;
        }
        return ans;
    }
};
