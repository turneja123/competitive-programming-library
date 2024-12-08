//https://leetcode.com/contest/biweekly-contest-145/problems/digit-operations-to-make-two-integers-equal/
const int N = 1e4;
const int INF = 1e18;
bool composite[N];
long long dist[N];
class Solution {
public:
    void precalc() {
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
        }
        composite[1] = true;
        for (int i = 2; i < N; i++) {
            if (!composite[i]) {
                for (int j = 2 * i; j < N; j += i) {
                    composite[j] = true;
                }
            }
        }
    }

    int minOperations(int n, int m) {
        if (!composite[4]) {
            precalc();
        }
        if (!composite[n] || !composite[m]) {
            return -1;
        }
        priority_queue<pair<long long, int>> q;
        dist[n] = 0;
        q.push(make_pair(0, n));
        vector<int> upd;
        while (q.size()) {
            int pw = 1;
            int u = q.top().second, n = u;
            long long cost = -q.top().first;
            q.pop();
            if (cost != dist[n]) {
                continue;
            }
            upd.push_back(n);
            while (u > 0) {
                int d = u % 10;
                u /= 10;
                if (d != 9) {
                    int nx = n + pw;
                    if (dist[nx] > cost + n && composite[nx]) {
                        dist[nx] = cost + n;
                        q.push(make_pair(-dist[nx], nx));
                    }
                }
                if (d != 0) {
                    int nx = n - pw;
                    if (dist[nx] > cost + n && composite[nx]) {
                        dist[nx] = cost + n;
                        q.push(make_pair(-dist[nx], nx));
                    }
                }
                pw *= 10;
            }
        }
        int ans = dist[m];
        for (int u : upd) {
            dist[u] = INF;
        }
        if (ans == INF) {
            return -1;
        }
        return ans + m;
    }
};
