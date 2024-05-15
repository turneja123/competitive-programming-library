//https://leetcode.com/problems/find-the-minimum-cost-array-permutation/description/
class Solution {
public:
    int INF = 1e9;
    int dp[1 << 14][14];
    __int128 best[1 << 14][14];
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size(), bits = 1 << n;
        for (int i = 0; i < n; i++) {
            for (int mask = 1; mask < bits; mask++) {
                if (__builtin_popcount(mask) != i + 1) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    dp[mask][j] = INF;
                }
            }
        }
        dp[1][0] = 0;
        best[1][0] = 1;
        for (int i = 1; i < n; i++) {
            for (int mask = 1; mask < bits; mask++) {
                if (__builtin_popcount(mask) != i + 1) {
                    continue;
                }
                for (int j = 1; j < n; j++) {
                    int cj = mask & (1 << j);
                    if (!cj) {
                        continue;
                    }
                    for (int prv = 0; prv < n; prv++) {
                        int c = mask & (1 << prv);
                        if (!c) {
                            continue;
                        }
                       // cout << prv << endl;
                        if (dp[mask ^ (1 << j)][prv] == INF) {
                            continue;
                        }
                        int d = dp[mask ^ (1 << j)][prv] + abs(prv - nums[j]);
                        if (i == n - 1) {
                            d += abs(j - nums[0]);
                        }
                        __int128 hsh = (__int128)(n + 1) * best[mask ^ (1 << j)][prv] + (j + 1);
                        if (dp[mask][j] > d) {
                            dp[mask][j] = d;
                            best[mask][j] = hsh;
                        } else if (dp[mask][j] == d && hsh < best[mask][j]) {
                            best[mask][j] = hsh;
                        }
                    }
                } 
            }
        }
        int mask = bits - 1, ans = INF; __int128 hsh;
        for (int j = 0; j < n; j++) {
            if (dp[mask][j] < ans) {
                ans = dp[mask][j];
                hsh = best[mask][j];
            } else if (dp[mask][j] != INF && dp[mask][j] <= ans && best[mask][j] < hsh) {
                hsh = best[mask][j];
            }
        }
        vector<int> perm;
        while (hsh > 0) {
            perm.push_back(hsh % (n + 1) - 1);
            hsh /= n + 1;
        }
        reverse(perm.begin(), perm.end());
        return perm;
    }
};