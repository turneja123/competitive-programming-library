//https://leetcode.com/contest/weekly-contest-372/problems/find-building-where-alice-and-bob-can-meet/
const int N = 5e4 + 5;
const int K = 16;
int table[K][N];

class Solution {
public:
    void build(int n, vector<int> &a) {
        for (int i = 1; i <= n; i++) {
            table[0][i] = a[i - 1];
        }
        for (int k = 1; k < K; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
        return;
    }

    int query(int l, int r) {
        l++, r++;
        int k = 31 - __builtin_clz(r - l + 1);
        return max(table[k][l], table[k][r - (1 << k) + 1]);
    }

    vector<int> leftmostBuildingQueries(vector<int>& a, vector<vector<int>>& queries) {
        int n = a.size(), q = queries.size();
        build(n, a);
        vector<int> ans;
        for (int i = 0; i < q; i++) {
            int x = queries[i][0], y = queries[i][1];
            if (x > y) {
                swap(x, y);
            }
            if (a[x] < a[y] || x == y) {
                ans.push_back(y);
                continue;
            }
            int l = y, r = n - 1, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int v = query(y, mid);
                if (v > a[x]) {
                    spl = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans.push_back(spl);
        }
        return ans;
    }
};
