//https://leetcode.com/contest/biweekly-contest-152/problems/longest-special-path-ii/
const int N = 5e4 + 5;
const int MAX = 3e6 + 5;
vector<pair<int, int>> adj[N];
multiset<int> st[N];
struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];

class Solution {
public:
    vector<vector<int>> up;
    int timer = 0, lg;
    int path[N];
    int depth[N];
    int last[N];

    void build(int node, int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = idx;
        nodes[idx++] = Node();
        build(nodes[node].left, l, mid);
        build(nodes[node].right, mid + 1, r);
        return;
    }

    void update(int node_prev, int node, int l, int r, int ind) {
        if (l == r) {
            nodes[node].val = nodes[node_prev].val + 1;
            return;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
            nodes[node].right = nodes[node_prev].right;
            update(nodes[node_prev].left, nodes[node].left, l, mid, ind);
        } else {
            nodes[node].right = idx;
            nodes[idx++] = Node();
            nodes[node].left = nodes[node_prev].left;
            update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind);
        }
        nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
        return;
    }

    int query(int node_l, int node_r, int l, int r, int lq, int rq) {
        if (lq > r || rq < l) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return nodes[node_r].val - nodes[node_l].val;
        }
        int mid = (l + r) / 2;
        return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
    }


    void dfs(int u, int p, int cur_root, int n, vector<int> &nums) {
        if (st[nums[u]].size()) {
            last[u] = *st[nums[u]].rbegin();
        } else {
            last[u] = -1;
        }
        if (last[u] == -1) {
            root[u] = cur_root;
        } else {
            root[u] = idx;
            nodes[idx++] = Node();
            update(cur_root, root[u], 0, n - 1, last[u]);
        }

        st[nums[u]].insert(depth[u]);
        up[u][0] = p;
        for (int i = 1; i <= lg; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto [v, wt] : adj[u]) {
            if (v != p) {
                path[v] = path[u] + wt;
                depth[v] = depth[u] + 1;
                dfs(v, u, root[u], n, nums);
            }
        }
        st[nums[u]].erase(st[nums[u]].find(depth[u]));
    }

    int kth(int v, int k) {
        while (k > 0) {
            int l = log2(k);
            v = up[v][l];
            k ^= 1 << l;
        }
        return v;
    }

    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
        }
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        nodes[idx++] = Node();
        build(0, 0, n - 1);

        dfs(0, 0, 0, n, nums);
        vector<int> ans{0, N};
        for (int i = 0; i < n; i++) {
            int l = 0, r = depth[i];
            while (l <= r) {
                int mid = (l + r) / 2;
                int anc = kth(i, mid);
                int ct = query(root[anc], root[i], 0, n - 1, depth[i] - mid, depth[i]);
                if (ct <= 1) {
                    l = mid + 1;
                    if (ans[0] < path[i] - path[anc]) {
                        ans[0] = path[i] - path[anc];
                        ans[1] = mid + 1;
                    } else if (ans[0] == path[i] - path[anc] && ans[1] > mid + 1) {
                        ans[1] = mid + 1;
                    }
                } else {
                    r = mid - 1;
                }
            }
            adj[i].clear();
            st[nums[i]].clear();
        }
        idx = 0;
        return ans;
    }
};
