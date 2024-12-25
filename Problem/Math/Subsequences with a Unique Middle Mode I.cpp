//https://leetcode.com/contest/biweekly-contest-146/problems/subsequences-with-a-unique-middle-mode-i/
const int N = 1005;
const long long M = 1e9 + 7;

class Solution {
public:
    pair<int, int> compr[N];
    int a[N];
    int freq[N][N];

    long long sum(long long n) {
        return (n * (n - 1) / 2) % M;
    }


    int subsequencesWithMiddleMode(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            compr[i] = make_pair(nums[i], i);
        }
        sort(compr, compr + n);
        int m = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && compr[i].first > compr[i - 1].first) {
                m++;
            }
            a[compr[i].second] = m;
        }
        m++;
        for (int i = 0; i < n; i++) {
            freq[i][a[i]]++;
            for (int j = 0; j < m && i != 0; j++) {
                freq[i][j] += freq[i - 1][j];
            }
        }
        long long ans = 0;
        for (int i = 2; i < n - 2; i++) {
            int l = freq[i - 1][a[i]], r = freq[n - 1][a[i]] - freq[i][a[i]];
            //2
            long long tot = sum(n - i - 1 - r);
            for (int j = 0; j < m; j++) {
                if (j != a[i]) {
                    tot -= sum(freq[n - 1][j] - freq[i][j]);
                }
            }
            for (int j = 0; j < i; j++) {
                if (a[j] != a[i]) {
                    ans = (ans + (tot - (n - i - 1 - r - (freq[n - 1][a[j]] - freq[i][a[j]])) * (freq[n - 1][a[j]] - freq[i][a[j]])) % M * l) % M;
                }
            }
            tot = sum(i - l);
             for (int j = 0; j < m; j++) {
                if (j != a[i]) {
                    tot -= sum(freq[i - 1][j]);
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (a[j] != a[i]) {
                    ans = (ans + (tot - (i - l - freq[i - 1][a[j]]) * (freq[i - 1][a[j]])) % M * r) % M;
                }
            }
            //3
            ans = (ans + sum(l) * sum(n - i - 1 - r) + sum(r) * sum(i - l)) % M;
            ans = (ans + (long long)l * r * (n - i - 1 - r) * (i - l)) % M;
            //4
            ans = (ans + sum(l) * r % M * (n - i - 1 - r) + sum(r) * l % M * (i - l)) % M;
            //5
            ans = (ans + sum(l) * sum(r)) % M;

        }
        return ans;
    }
};
