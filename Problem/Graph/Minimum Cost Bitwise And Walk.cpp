//https://leetcode.com/contest/weekly-contest-392/problems/minimum-cost-walk-in-weighted-graph/
class Solution {
public:
    bool visited[100005];
    vector<pair<int, int>> adj[100005];
    int component[100005];
    int val[100005];
    int cur;
    vector<int> curcomponent;
    //bool singlecomponent;
    
    void dfs(int u, int i) {
        visited[u] = true;
        component[u] = i;
        curcomponent.push_back(u);
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            cur = cur & it->second;
            //singlecomponent = false;
            if (!visited[it->first]) {
                dfs(it->first, i);
            } 
        }
    }
    
    
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], wt = edges[i][2];
            adj[u].push_back(make_pair(v, wt));
            adj[v].push_back(make_pair(u, wt));
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                cur = (1 << 20) - 1;
                dfs(i, i);
                for (int x : curcomponent) {
                    val[x] = cur;
                }
                curcomponent.clear();
            }
        }
        vector<int> ans;
        for (int i = 0; i < query.size(); i++) {
            int u = query[i][0], v = query[i][1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            if (component[u] != component[v]) {
                ans.push_back(-1);
            } else {
                ans.push_back(val[u]);
            }
        }
        return ans;
        
    }
};