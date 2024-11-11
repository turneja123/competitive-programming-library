//https://leetcode.com/contest/weekly-contest-338/problems/collect-coins-in-a-tree/
const int N = 3e4 + 5;
vector<int> adj[N];
int subtree[N], subtree_mx[N];
int dp[N], dp_mx[N];

class Solution {
public:
    void dfs_subtree(int u, int p, vector<int> &coins) {
        for (int v : adj[u]) {
            if (v != p) {
                dfs_subtree(v, u, coins);
                if (coins[v] || subtree_mx[v]) {
                    subtree_mx[u] = max(subtree_mx[u], subtree_mx[v] + 1);
                }
                if (subtree[v] == 0) {
                    if (subtree_mx[v] == 2) {
                        subtree[u] += 2;
                    }
                } else {
                    subtree[u] += subtree[v] + 2;
                }
            }
        }
        return;
    }

    void dfs(int u, int p, vector<int> &coins) {
        multiset<int> st;
        for (int v : adj[u]) {
            if (v != p) {
                if (subtree_mx[v] == 0 && !coins[v]) {
                    st.insert(-2);
                } else {
                    st.insert(subtree_mx[v]);
                }
            }
        }

        for (int v : adj[u]) {
            if (v != p) {
                if (subtree_mx[v] == 0 && !coins[v]) {
                    st.erase(st.find(-2));
                } else {
                    st.erase(st.find(subtree_mx[v]));
                }

                if (coins[u] || dp_mx[u]) {
                    dp_mx[v] = dp_mx[u] + 1;
                }
                if (st.size()) {
                    dp_mx[v] = max(dp_mx[v], *st.rbegin() + 2);
                }
                if (dp[u] == 0) {
                    if (dp_mx[u] == 2) {
                        dp[v] += 2;
                    }
                } else {
                    dp[v] += dp[u] + 2;

                }
                int add = subtree[u];
                if (subtree[v] == 0) {
                    if (subtree_mx[v] == 2) {
                        add -= 2;
                    }
                } else {
                    add -= subtree[v] + 2;
                }
                if (add > 0) {
                    if (dp[v] == 0) {
                        dp[v] += 2;
                    }
                    dp[v] += add;
                } else if (st.size() && *st.rbegin() > 0) {
                    dp[v] = max(dp[v], 2);
                }
                if (subtree_mx[v] == 0 && !coins[v]) {
                    st.insert(-2);
                } else {
                    st.insert(subtree_mx[v]);
                }
                dfs(v, u, coins);
            }
        }
    }

    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        dfs_subtree(0, 0, coins);
        dfs(0, 0, coins);
        int ans = 1e9;
        for (int i = 0; i < n; i++) {
            ans = min(ans, subtree[i] + dp[i]);
            subtree[i] = 0, dp[i] = 0;
            subtree_mx[i] = 0, dp_mx[i] = 0;
            adj[i].clear();

        }
        return ans;
    }
};
