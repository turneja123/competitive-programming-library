//https://leetcode.com/contest/weekly-contest-391/problems/minimize-manhattan-distances/
class Solution {
public:
    int calc(vector<pair<int, int>> &c) {
        int n = c.size();
        int maxx = c[0].first, maxy = c[0].second, minx = maxx, miny = maxy;
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (abs(c[i].first - minx) > ans) {
                ans = abs(c[i].first - minx);
            }
            if (abs(c[i].first - maxx) > ans) {
                ans = abs(c[i].first - maxx);
            }
            if (abs(c[i].second - maxy) > ans) {
                ans = abs(c[i].second - maxy);
            }
            if (abs(c[i].second - miny) > ans) {
                ans = abs(c[i].second - miny);
            }
            if (c[i].first > maxx) {
                maxx = c[i].first;
            }
            if (c[i].first < minx) {
                minx = c[i].first;
            }
            if (c[i].second > maxy) {
                maxy = c[i].second;
            }
            if (c[i].second < miny) {
                miny = c[i].second;
            }
        }
        return ans;
    }
    
    
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size();
        vector<pair<int, int>> c(n);
        for (int i = 0; i < n; i++) {
            c[i].first = points[i][0] + points[i][1];
            c[i].second = points[i][0] - points[i][1];
        }
        int ind1 = -1, ind2 = -1, ans = 0;
        
        int maxx = c[0].first, maxy = c[0].second, minx = maxx, miny = maxy;
        int indmaxx = 0, indmaxy = 0, indminx = 0, indminy = 0;
        for (int i = 1; i < n; i++) {
            if (abs(c[i].first - minx) > ans) {
                ans = abs(c[i].first - minx);
                ind1 = indminx;
                ind2 = i;
            }
            if (abs(c[i].first - maxx) > ans) {
                ans = abs(c[i].first - maxx);
                ind1 = indmaxx;
                ind2 = i;
            }
            if (abs(c[i].second - maxy) > ans) {
                ans = abs(c[i].second - maxy);
                ind1 = indmaxy;
                ind2 = i;
            }
            if (abs(c[i].second - miny) > ans) {
                ans = abs(c[i].second - miny);
                ind1 = indminy;
                ind2 = i;
            }
            if (c[i].first > maxx) {
                maxx = c[i].first;
                indmaxx = i;
            }
            if (c[i].first < minx) {
                minx = c[i].first;
                indminx = i;
            }
            if (c[i].second > maxy) {
                maxy = c[i].second;
                indmaxy = i;
            }
            if (c[i].second < miny) {
                miny = c[i].second;
                indminy = i;
            }
        }
        vector<pair<int, int>> try1;
        for (int i = 0; i < n; i++) {
            if (i != ind1) {
                try1.push_back(c[i]);
            }
        }
        vector<pair<int, int>> try2;
        for (int i = 0; i < n; i++) {
            if (i != ind2) {
                try2.push_back(c[i]);
            }
        }
        return min(calc(try1), calc(try2));
        
        
    }
};