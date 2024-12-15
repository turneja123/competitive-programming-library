//https://leetcode.com/problems/string-compression-ii
const int N = 105;
const int INF = 1e9;
int dp[N][N][N][27];
class Solution {
public:
    int calc(int x) {
        int ans = 0;
        if (x >= 1) {
            ans++;
        }
        if (x >= 2) {
            ans++;
        }
        if (x >= 10) {
            ans++;
        }
        if (x >= 100) {
            ans++;
        }
        return ans;
    }

    int diff(int a, int b, int x, int y) {
        if (a != b) {
            return calc(x);
        }
        return calc(x) - calc(y);
    }

    int getLengthOfOptimalCompression(string s, int k) {
        char last = s[0]; int ct = 1;
        vector<pair<int, int>> v{make_pair(0, 0)};
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != last) {
                v.push_back(make_pair(ct, last - 'a' + 1));
                ct = 0;
                last = s[i];
            }
            ct++;
        }
        v.push_back(make_pair(ct, last - 'a' + 1));
        int n = v.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int used = 0; used <= s.size(); used++) {
                    for (int last = 0; last <= 26; last++) {
                        dp[i][j][used][last] = INF;
                    }
                }
            }
        }
        dp[0][0][0][0] = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int used = 0; used <= s.size(); used++) {
                    for (int last = 0; last <= 26; last++) {
                        if (dp[i - 1][j][used][last] == INF) {
                            continue;
                        }
                        int ct = v[i].first;
                        if (v[i].second == last) {
                            ct += used;
                        }
                        dp[i][j][ct][v[i].second] = min(dp[i][j][ct][v[i].second], dp[i - 1][j][used][last] + diff(v[i].second, last, ct, used));
                        if (ct > 1 && j + ct - 1 <= k) {
                            dp[i][j + ct - 1][1][v[i].second] = min(dp[i][j + ct - 1][1][v[i].second], dp[i - 1][j][used][last] + diff(v[i].second, last, 1, used));
                        }
                        if (ct > 9 && j + ct - 9 <= k) {
                            dp[i][j + ct - 9][9][v[i].second] = min(dp[i][j + ct - 9][9][v[i].second], dp[i - 1][j][used][last] + diff(v[i].second, last, 9, used));
                        }
                        if (ct > 99 && j + ct - 99 <= k) {
                            dp[i][j + ct - 99][99][v[i].second] = min(dp[i][j + ct - 99][99][v[i].second], dp[i - 1][j][used][last] + diff(v[i].second, last, 99, used));
                        }
                        if (j + ct <= k && last != v[i].second) {
                            dp[i][j + ct][used][last] = min(dp[i][j + ct][used][last], dp[i - 1][j][used][last]);
                        }
                    }
                }
            }
        }
        int ans = INF;
        for (int j = 0; j <= k; j++) {
            for (int used = 0; used <= s.size(); used++) {
                for (int last = 0; last <= 26; last++) {
                    ans = min(ans, dp[n - 1][j][used][last]);
                }
            }
        }
        return ans;
    }
};
