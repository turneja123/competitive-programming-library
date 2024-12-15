//https://leetcode.com/contest/weekly-contest-198/problems/maximum-number-of-non-overlapping-substrings/
const int N = 1e5 + 5;
const int K = 19;

class Solution {
public:
    int a[N], b[N];
    int table[2][K][N];

    static bool comp(pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    }

    void build(int n) {
        for (int i = 1; i <= n; i++) {
            table[0][0][i] = a[i - 1];
            table[1][0][i] = b[i - 1];
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                table[0][k][i] = max(table[0][k - 1][i], table[0][k - 1][i + (1 << (k - 1))]);
                table[1][k][i] = min(table[1][k - 1][i], table[1][k - 1][i + (1 << (k - 1))]);
            }
        }
        return;
    }

    int query(int l, int r, int n) {
        l++, r++;
        int k = 31 - __builtin_clz(r - l + 1);
        if (n == 0) {
            return max(table[0][k][l], table[0][k][r - (1 << k) + 1]);
        }
        return min(table[1][k][l], table[1][k][r - (1 << k) + 1]);
    }

    vector<string> maxNumOfSubstrings(string s) {
        map<int, int> right;
        map<int, int> left;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            right[s[i] - 'a'] = i;
        }
        for (int i = n - 1; i >= 0; i--) {
            left[s[i] - 'a'] = i;
        }
        for (int i = 0; i < n; i++) {
            a[i] = right[s[i] - 'a'];
            b[i] = left[s[i] - 'a'];
        }
        build(n);
        set<int> seen;
        vector<pair<int, int>> ivals;
        for (int i = 0; i < n; i++) {
            if (seen.find(s[i] - 'a') == seen.end()) {
                int j = i;
                while (1) {
                    int r = query(i, j, 0);
                    if (j == r) {
                        break;
                    }
                    j = r;
                }
                int mn = query(i, j, 1);
                if (mn >= i) {
                    ivals.push_back(make_pair(i, j));
                }
                seen.insert(s[i] - 'a');
            }
        }
        int m = ivals.size();
        vector<string> ans;
        vector<pair<int, int>> dp(m);
        vector<int> parent(m);
        sort(ivals.begin(), ivals.end(), comp);
        pair<int, int> mx = make_pair(0, 0); int best = -1;
        for (int i = 0; i < m; i++) {
            dp[i] = make_pair(1, ivals[i].second - ivals[i].first + 1);
            parent[i] = -1;
            for (int j = 0; j < i; j++) {
                if (ivals[j].second < ivals[i].first) {
                    pair<int, int> cur = make_pair(dp[j].first + 1, dp[j].second + ivals[i].second - ivals[i].first + 1);
                    if (cur.first > dp[i].first || cur.second < dp[i].second) {
                        dp[i] = cur;
                        parent[i] = j;
                    }
                }
            }
            if (dp[i].first > mx.first || dp[i].second < mx.second) {
                mx = dp[i];
                best = i;
            }
        }
        while (best != -1) {
            ans.push_back(s.substr(ivals[best].first, ivals[best].second - ivals[best].first + 1));
            best = parent[best];
        }
        return ans;
    }
};
