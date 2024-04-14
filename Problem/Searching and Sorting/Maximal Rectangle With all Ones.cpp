//https://leetcode.com/problems/maximal-rectangle/description/
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<vector<int>> heights(matrix.size(), vector<int>(matrix[0].size(), 0));
        for (int i = 0; i < matrix[0].size(); i++) {
            for (int j = 0; j < matrix.size();) {
                if (matrix[j][i] == '0') {
                    heights[j][i] = 0;
                    j++;
                } else {
                    int r = j, a = 1;
                    while (r < matrix.size() && matrix[r][i] == '1') {
                        r++;
                    }
                    for (int k = r - 1; k >= j; k--) {
                        heights[k][i] = a++;
                    }
                    j = r;
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < matrix.size(); i++) {
            int n = heights[i].size();
            stack<int> s;
            vector<long long> l(n, 0);
            vector<long long> r(n, 0);
            for (int j = 0; j < n; j++) {
                while (s.size() && heights[i][s.top()] >= heights[i][j]) {
                    s.pop();
                }
                if (s.empty()) {
                    l[j] = -1;
                } else {
                    l[j] = s.top();
                }
                s.push(j);
                
            }
            while (!s.empty()) {
                s.pop();
            }
            for (int j = n - 1; j >= 0 ; j--) {
                while (s.size() && heights[i][s.top()] >= heights[i][j]) {
                    s.pop();
                }
                if (s.empty()) {
                    r[j] = n;
                } else {
                    r[j] = s.top();
                }
                s.push(j);
            }
            for (int j = 0; j < n; j++) {
                ans = max(ans, (r[j] - l[j] - 1) * heights[i][j]);
            }
        }
        return ans;
    }
};