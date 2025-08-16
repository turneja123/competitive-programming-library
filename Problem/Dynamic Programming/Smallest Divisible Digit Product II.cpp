//https://leetcode.com/problems/smallest-divisible-digit-product-ii/description/
vector<int> primes{2, 3, 5, 7};
vector<vector<int>> add{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {2, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 1},
    {3, 0, 0, 0},
    {0, 2, 0, 0}
};

int dp[40][50][31][22][18];
int go[40][50][31][22][18];

const int INF = 1e9;

int calc(int n, int p, int q, int r, int s) {
    if (n == 0) {
        return dp[n][p][q][r][s] = (p + q + r + s == 0);
    }
    if (dp[n][p][q][r][s] != -1) {
        return dp[n][p][q][r][s];
    }
    dp[n][p][q][r][s] = 0;
    for (int d = 1; d < 10; d++) {
        int np = max(0, p - add[d][0]);
        int nq = max(0, q - add[d][1]);
        int nr = max(0, r - add[d][2]);
        int ns = max(0, s - add[d][3]);
        if (calc(n - 1, np, nq, nr, ns)) {
            dp[n][p][q][r][s] = 1;
            go[n][p][q][r][s] = d;
            break;
        }
    }
    return dp[n][p][q][r][s];
}

bool pre = false;

void precalc() {
    int m = 39;
    for (int i = 0; i <= m; i++) {
        for (int p = 0; p < 50; p++) {
            for (int q = 0; q < 31; q++) {
                for (int r = 0; r < 22; r++) {
                    for (int s = 0; s < 18; s++) {
                        dp[i][p][q][r][s] = -1;
                    }
                }
            }
        }
    }
    for (int p = 0; p < 50; p++) {
        for (int q = 0; q < 31; q++) {
            for (int r = 0; r < 22; r++) {
                for (int s = 0; s < 18; s++) {
                    calc(m, p, q, r, s);
                }
            }
        }
    }


}

class Solution {
public:
    string smallestNumber(string s, long long t) {
        if (!pre) {
            pre = true;
            precalc();
        }
        vector<int> need(4, 0);
        vector<int> cur(4, 0);

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                need[i]++;
                t /= primes[i];
            }
        }
        if (t > 1) {
            return "-1";
        }
        int n = s.size();
        int z = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                cur[j] += add[s[i] - '0'][j];
            }
            if (s[i] == '0') {
                z = 1;
            }
        }
        if (cur[0] >= need[0] && cur[1] >= need[1] && cur[2] >= need[2] && cur[3] >= need[3] && !z) {
            return s;
        }
        cur[0] = 0, cur[1] = 0, cur[2] = 0, cur[3] = 0;
        tuple<int, int, int, int, int, int> best = {INF, INF, INF, INF, INF, INF};
        int f = 1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                s[i] = '1';
                f = 0;
            }
            for (int d = (f == 0 ? 1 : s[i] - '0' + 1); d < 10; d++) {
                for (int j = 0; j < 4; j++) {
                    cur[j] += add[d][j];
                }
                int np = max(0, need[0] - cur[0]);
                int nq = max(0, need[1] - cur[1]);
                int nr = max(0, need[2] - cur[2]);
                int ns = max(0, need[3] - cur[3]);
                int m = min(39, n - i - 1);
                if (dp[m][np][nq][nr][ns] == 1) {
                    best = min(best, {-i, d, np, nq, nr, ns});
                }

                for (int j = 0; j < 4; j++) {
                    cur[j] -= add[d][j];
                }
            }
            for (int j = 0; j < 4; j++) {
                cur[j] += add[s[i] - '0'][j];
            }
            if (f == 0) {
                break;
            }
        }
        if (get<0>(best) != INF) {
            auto [i, d, np, nq, nr, ns] = best;
            i = -i;
            int m = min(39, n - i - 1);
            string ans = "";
            for (int j = 0; j < i; j++) {
                ans += s[j];
            }
            ans += '0' + d;
            for (int j = 0; j < n - i - 1 - 39; j++) {
                ans += '1';
            }
            while (m > 0) {
                int D = go[m][np][nq][nr][ns];
                ans += '0' + D;
                m--;
                np -= add[D][0], nq -= add[D][1], nr -= add[D][2], ns -= add[D][3];
                np = max(np, 0), nq = max(nq, 0), nr = max(nr, 0), ns = max(ns, 0);
            }
            return ans;
        }
        while (++n) {
            int np = need[0];
            int nq = need[1];
            int nr = need[2];
            int ns = need[3];
            int m = min(39, n);
            if (dp[m][np][nq][nr][ns]) {
                string ans = "";
                for (int j = 0; j < n - 39; j++) {
                    ans += '1';
                }
                while (m > 0) {
                    int D = go[m][np][nq][nr][ns];
                    ans += '0' + D;
                    m--;
                    np -= add[D][0], nq -= add[D][1], nr -= add[D][2], ns -= add[D][3];
                    np = max(np, 0), nq = max(nq, 0), nr = max(nr, 0), ns = max(ns, 0);
                }
                return ans;
            }
        }

        string ans;
        return ans;
    }
};
