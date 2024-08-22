//https://leetcode.com/contest/biweekly-contest-137/problems/maximum-value-sum-by-placing-three-rooks-ii/
class Solution {
public:
    vector<pair<int, int>> mx[505];

    long long maximumValueSum(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        if (n > m) {
            vector<vector<int>> t;
            for (int i = 0; i < m; i++) {
                vector<int> v;
                for (int j = 0; j < n; j++) {
                    v.push_back(a[j][i]);
                }
                t.push_back(v);
            }
            a = t;
            swap(n, m);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mx[i].push_back(make_pair(a[i][j], j));
            }
            sort(mx[i].begin(), mx[i].end());
            reverse(mx[i].begin(), mx[i].end());
        }
        long long ans = -1e10;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    long long cur = (long long)mx[i][0].first + mx[j][0].first + mx[k][0].first;
                    if (cur < ans) {
                        continue;
                    }
                    if (mx[i][0].second != mx[j][0].second && mx[j][0].second != mx[k][0].second && mx[i][0].second != mx[k][0].second) {
                        ans = cur;
                        continue;
                    }
                    for (int dx = 0; dx < 3; dx++) {
                        for (int dy = 0; dy < 3; dy++) {
                            for (int dz = 0; dz < 3; dz++) {
                                long long cur = (long long)mx[i][dx].first + mx[j][dy].first + mx[k][dz].first;
                                if (mx[i][dx].second != mx[j][dy].second && mx[j][dy].second != mx[k][dz].second
                                    && mx[i][dx].second != mx[k][dz].second) {
                                    ans = max(ans, cur);

                                }
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};
