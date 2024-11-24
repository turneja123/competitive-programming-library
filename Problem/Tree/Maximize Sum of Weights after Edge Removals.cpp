//https://leetcode.com/contest/weekly-contest-425/problems/maximize-sum-of-weights-after-edge-removals/
const int N = 1e5 + 5;
vector<pair<int, int>> adj[N];
long long dp[2][N];
int a[N];

class Solution {
public:
    void dfs(int u, int p, int k) {
        for (pair<int, int> pr : adj[u]) {
            int v = pr.first, w = pr.second;
            if (v != p) {
                a[v] = w;
                dfs(v, u, k);
            }
        }
        priority_queue<pair<long long, int>> pq;
        for (pair<int, int> pr : adj[u]) {
            int v = pr.first, w = pr.second;
            if (v != p) {
                if (max(dp[0][v], dp[1][v]) < dp[0][v] + w) {
                    pq.push(make_pair(dp[0][v] + w - max(dp[0][v], dp[1][v]), v));
                }
            }
        }
        priority_queue<pair<long long, int>> tmp = pq;
        int j = 1, last = -1; long long sum = 0;
        set<int> seen;
        while (pq.size() && j <= k) {
            long long val = pq.top().first, v = pq.top().second;
            pq.pop();
            if (j == k) {
                last = v;
                break;
            }
            sum += val + max(dp[0][v], dp[1][v]);
            seen.insert(v);
            j++;
        }
        dp[0][u] = sum;
        for (pair<int, int> pr : adj[u]) {
            int v = pr.first;
            if (v != p && seen.find(v) == seen.end()) {
                dp[0][u] += max(dp[0][v], dp[1][v]);
            }
        }
        if (last != -1) {
            dp[1][u] = dp[0][u] + dp[0][last] + a[last] - max(dp[0][last], dp[1][last]);
        } else {
            dp[1][u] = 0;
        }
    }

    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
        }
        dfs(0, 0, k);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        return max(dp[0][0], dp[1][0]);
    }
};
