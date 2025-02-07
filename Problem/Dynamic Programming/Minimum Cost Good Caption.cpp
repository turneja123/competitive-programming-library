//https://leetcode.com/contest/biweekly-contest-149/problems/minimum-cost-good-caption/
const int N = 5e4 + 5;
const int INF = 1e9;
int dp[N][26][3];
tuple<int, int, int> go[N][26][3];

class Solution {
public:

    int calc(int i, int j, int d, int n, string &s) {
        if (i == n - 1) {
            if (d != 2) {
                return dp[i][j][d] = INF;
            }
            int x = s[n - 1] - 'a';
            return abs(x - j);
        }
        if (dp[i][j][d] != -1) {
            return dp[i][j][d];
        }
        int mn = INF;
        if (d != 2) {
            mn = calc(i + 1, j, d + 1, n, s);
            go[i][j][d] = make_tuple(i + 1, j, d + 1);
        } else {
            for (int c = 0; c < 26; c++) {
                int cur = calc(i + 1, c, (c == j ? 2 : 0), n, s);
                if (cur < mn) {
                    mn = cur;
                    go[i][j][d] = make_tuple(i + 1, c, (c == j ? 2 : 0));
                }
            }

        }
        if (mn == INF) {
            return dp[i][j][d] = INF;
        }
        int x = s[i] - 'a';
        return dp[i][j][d] = mn + abs(x - j);
    }

    string minCostGoodCaption(string s) {
        int n = s.size();
        string ans = "";
        if (n < 3) {
            return ans;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
                dp[i][j][2] = -1;
            }
        }
        int mn = INF;
        tuple<int, int, int> t;
        for (int j = 0; j < 26; j++) {
            int cur = calc(0, j, 0, n, s);
            if (cur < mn) {
                mn = cur;
                t = make_tuple(0, j, 0);
            }
        }
        while (1) {
            auto [i, j, d] = t;
            ans += j + 'a';
            if (i == n - 1) {
                break;
            }
            t = go[i][j][d];
        }
        return ans;
    }
};
