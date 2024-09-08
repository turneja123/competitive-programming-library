//https://leetcode.com/problems/maximum-genetic-difference-query
const int N = 1e5 + 5;
const int MAX = 1e7 + 5;
vector<int> adj[N];
vector<pair<int, int>> query[N];
struct Node {
    int left;
    int right;
    int val;
    Node() : left(-1), right(-1), val(0) {}
};
Node nodes[MAX];
class Solution {
public:
    int idx = 0;
    int get(int node, int d, int val, int ans) {
        if (d == -1) {
            return ans;
        }
        int c = val & (1 << d);
        if (c == 0) {
            if (nodes[node].right != -1 && nodes[nodes[node].right].val > 0) {
                return get(nodes[node].right, d - 1, val, ans ^ (1 << d));
            } else {
                return get(nodes[node].left, d - 1, val, ans);
            }
        } else {
            if (nodes[node].left != -1 && nodes[nodes[node].left].val > 0) {
                return get(nodes[node].left, d - 1, val, ans ^ (1 << d));
            } else {
                return get(nodes[node].right, d - 1, val, ans);
            }
        }
    }

    void add(int node, int d, int val, int sgn) {
        if (d < 0) {
            nodes[node].val += sgn;
            return;
        }
        int c = val & (1 << d);
        if (c == 0) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].left, d - 1, val, sgn);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].right, d - 1, val, sgn);
        }
        nodes[node].val = 0;
        if (nodes[node].left != -1) {
            nodes[node].val += nodes[nodes[node].left].val;
        }
        if (nodes[node].right != -1) {
            nodes[node].val += nodes[nodes[node].right].val;
        }
    }
    void dfs(int u, int p, vector<int> &ans) {
        add(0, 17, u, 1);
        for (int i = 0; i < query[u].size(); i++) {
            ans[query[u][i].second] = get(0, 17, query[u][i].first, 0);
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, ans);
            }
        }
        add(0, 17, u, -1);
    }

    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        nodes[idx++] = Node();
        int root = 0, n = parents.size();
        for (int i = 0; i < n; i++) {
            if (parents[i] == -1) {
                root = i;
            } else {
                adj[i].push_back(parents[i]);
                adj[parents[i]].push_back(i);
            }
        }
        for (int i = 0; i < queries.size(); i++) {
            query[queries[i][0]].push_back(make_pair(queries[i][1], i));
        }
        vector<int> ans(queries.size());
        dfs(root, root, ans);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            query[i].clear();
        }
        return ans;
    }
};
