//https://leetcode.com/problems/count-number-of-trapezoids-ii/description/
class Solution {
public:
    pair<int, int> K(int x, int y) {
        int dx = abs(x), dy = abs(y);
        int g = __gcd(dx, dy);
        dx /= g, dy /= g;
        if ((x > 0 && y > 0) || (x < 0 && y < 0)) {
            return {dx, dy};
        }
        return {-dx, dy};
    }

    int S(int n) {
        return n * (n - 1) / 2;
    }

    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        map<pair<int, int>, map<int, set<int>>> mp;
        map<pair<int, int>, int> rem;
        map<pair<int, int>, map<pair<int, int>, int>> remcol;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                pair<int, int> k = K(x2 - x1, y2 - y1);
                auto [dx, dy] = k;
                int b = dy * x1 - dx * y1;
                mp[k][b].insert(i);
                mp[k][b].insert(j);
                rem[{x1 + x2, y1 + y2}]++;
                remcol[{x1 + x2, y1 + y2}][k]++;
            }
        }
        int ans = 0;
        for (auto it : mp) {
            auto m = it.second;
            int s = 0;
            for (auto [_, st] : m) {
                int x = st.size();
                x = S(x);
                ans += s * x;
                s += x;
            }

        }
        for (auto it : rem) {
            ans -= S(it.second);
        }
        for (auto it : remcol) {
            auto m = it.second;
            for (auto [_, x] : m) {
                ans += S(x);
            }
        }
        return ans;
    }
};
