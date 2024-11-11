//https://leetcode.com/contest/weekly-contest-422/problems/find-minimum-time-to-reach-last-room-ii/
const int N = 755;
const int INF = 2e9;
int dist[N][N][2];
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dist[i][j][0] = INF;
                dist[i][j][1] = INF;
            }
        }
        dist[0][0][0] = 0;
        priority_queue<pair<pair<int, int>, pair<int, int>>> pq;
        pq.push(make_pair(make_pair(0, 0), make_pair(0, 0)));
        while (pq.size()) {
            int d = -pq.top().first.first, f = pq.top().first.second;
            int x = pq.top().second.first, y = pq.top().second.second;
            pq.pop();
            if (dist[x][y][f] < d) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
                        if (f == 0) {
                            int cur = max(d, a[x + dx][y + dy]) + 1;
                            if (cur < dist[x + dx][y + dy][1]) {
                                dist[x + dx][y + dy][1] = cur;
                                pq.push(make_pair(make_pair(-cur, 1), make_pair(x + dx, y + dy)));
                            }
                        } else {
                            int cur = max(d, a[x + dx][y + dy]) + 2;
                            if (cur < dist[x + dx][y + dy][0]) {
                                dist[x + dx][y + dy][0] = cur;
                                pq.push(make_pair(make_pair(-cur, 0), make_pair(x + dx, y + dy)));
                            }
                        }
                    }
                }
            }
        }
        return min(dist[n - 1][m - 1][0], dist[n - 1][m - 1][1]);
    }
};
