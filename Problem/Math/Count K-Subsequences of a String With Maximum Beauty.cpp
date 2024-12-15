//https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/description/
const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

class Solution {
public:
    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        return;
    }

    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    int countKSubsequencesWithMaxBeauty(string s, int k) {
        if (fact[0] == 0) {
            precalc();
        }
        if (k > 26) {
            return 0;
        }
        int n = s.size();
        vector<int> freq(26, 0);
        for (int i = 0; i < n; i++) {
            freq[s[i] - 'a']++;
        }
        sort(freq.begin(), freq.end(), greater<int>());
        int mn = n;
        for (int i = 0; i < k; i++) {
            mn = min(freq[i], mn);
        }
        if (mn == 0) {
            return 0;
        }
        long long ans = 1;
        int u = 0, v = 0;
        for (int i = 0; i < k; i++) {
            if (freq[i] > mn) {
                ans = ans * freq[i] % M;
            } else {
                u++, v++;
            }
        }
        for (int i = k; i < 26; i++) {
            if (freq[i] == mn) {
                u++;
            }
        }
        ans = ans * binomial(u, v) % M;
        for (int i = 0; i < v; i++) {
            ans = ans * mn % M;
        }
        return ans;
    }
};
