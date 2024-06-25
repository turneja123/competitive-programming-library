//https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/description/
class Solution {
public:

    int R = 1e5 + 5;
    int MAX = 1e7 + 5;

    int parent[100005];
    vector<int> adj[100005];
    set<int> mp[100005];
    int x[100005];
    int q;

    struct Node {
        int ct;
        int left;
        int right;
        Node() : ct(0), left(-1), right(-1) {}
    };

    vector<Node> nodes;
    int idx = 0;


    void query(int node, int l, int r) {
        if (l == r || nodes[node].left == -1) {
            q = l;
            return;
        }
        int mid = (l + r) / 2;
        if (nodes[nodes[node].left].ct < mid - l + 1) {
            query(nodes[node].left, l, mid);
        } else {
            if (nodes[node].right == -1) {
                q = mid + 1;
                return;
            }
            query(nodes[node].right, mid + 1, r);
        }
    }

    void update(int node, int l, int r, int ind) {
        if (l == r) {
            nodes[node].ct = 1;
            return;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            update(nodes[node].left, l, mid, ind);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            update(nodes[node].right, mid + 1, r, ind);
        }
        nodes[node].ct = 0;
        if (nodes[node].left != -1) {
            nodes[node].ct += nodes[nodes[node].left].ct;
        }
        if (nodes[node].right != -1) {
            nodes[node].ct += nodes[nodes[node].right].ct;
        }
    }

    int dsu_find(int p) {
        if (parent[p] == p) {
            return p;
        }
        parent[p] = dsu_find(parent[p]);
        return parent[p];
    }

    void dsu_merge(int a, int b) {
        if (mp[a].size() > mp[b].size()) {
            swap(a, b);
        }
        parent[a] = b;
        for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
            update(b, 0, R - 1, *it);
            mp[b].insert(*it);
        }
        return;
    }

    void dfs(int u, int p, vector<int> &ans) {
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, ans);
            }
        }
        for (int v : adj[u]) {
            if (v != p) {
                int a = dsu_find(u), b = dsu_find(v);
                dsu_merge(a, b);
            }
        }
        int a = dsu_find(u);
        mp[a].insert(x[u]);
        update(a, 0, R - 1, x[u]);
        q = -1;
        if (mp[a].find(0) == mp[a].end()) {
            ans[u] = 1;
        } else {
            query(a, 0, R - 1);
            ans[u] = q + 1;
        }
        return;
    }

    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        nodes.resize(min(MAX, 17 * 17 * n));
        for (int i = 0; i < n; i++) {
            x[i] = nums[i] - 1;
            nodes[idx++] = Node();
            parent[i] = i;
        }
        for (int i = 1; i < n; i++) {
            int u = i, v = parents[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> ans(n, 0);
        dfs(0, -1, ans);
        return ans;
    }
};
