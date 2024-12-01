//https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/
const int INF = 1e9;
vector<pair<int, int>> moves{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& s) {
        int n = s.size(), m = s[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INF));
        dist[0][0] = 0;
        deque<pair<int, int>> q;
        q.push_front(make_pair(0, 0));
        while (q.size()) {
            int x = q.front().first, y = q.front().second;
            q.pop_front();
            for (int i = 0; i < 4; i++) {
                int dx = x + moves[i].first, dy = y + moves[i].second;
                if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                    if (s[dx][dy] == 0) {
                        if (dist[dx][dy] > dist[x][y]) {
                            dist[dx][dy] = dist[x][y];
                            q.push_front(make_pair(dx, dy));
                        }
                    } else {
                        if (dist[dx][dy] > dist[x][y] + 1) {
                            dist[dx][dy] = dist[x][y] + 1;
                            q.push_back(make_pair(dx, dy));
                        }
                    }
                }
            }
        }
        return dist[n - 1][m - 1];
    }
};
