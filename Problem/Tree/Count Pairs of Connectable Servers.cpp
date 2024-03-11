//https://leetcode.com/contest/biweekly-contest-125/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/
class Solution {
public:
    void dfs(int u, int p, vector<vector<pair<int, int>>> &adj, int speed, int dist, map<int, int> &cur, int *ans) {
        map<int, int> mp;
        if (p != -1) {
            cur[dist % speed]++;
            dist = dist % speed;
        }
        
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first, d = adj[u][i].second;
            if (v != p) {
                dfs(v, u, adj, speed, dist + d, cur, ans);
            }
            if (p == -1) {
                for (auto it = cur.begin(); it != cur.end(); ++it) {
                    int val = it->first;
                    if (val == 0 && mp.find((speed - val) % speed) != mp.end()) {
                        *ans += it->second * mp[(speed - val) % speed];
                    }
                }
                for (auto it = cur.begin(); it != cur.end(); ++it) {
                    mp[it->first] += it->second;
                }
                cur.clear();
            }  
        }
        return;
    }
    
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        int n = 0;
        vector<vector<pair<int, int>>> adj(1005);
        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
            n = max(edges[i][0], n);
            n = max(edges[i][1], n);
        }
        vector<int> ans(n + 1, 0);
        int cur = 0;
        for (int i = 0; i <= n; i++) {
            map<int, int> mp;
            dfs(i, -1, adj, signalSpeed, 0, mp, &cur);
            ans[i] = cur;
            cur = 0;
            mp.clear();
        }
        return ans;
    }
};