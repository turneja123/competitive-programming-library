//https://www.codechef.com/problems/YATP
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 17;
const int MAX = 2e7;
const int R = 5e6 + 5;

vector<int> adj[N];
vector<int> aux[N];
int tour[2 * N];

int depth[N];
int pos[N];
int euler = 0;
int timer = 0;
int table[K][2 * N];
int mn[K][2 * N];
int tin[N], tout[N];
int val[N];

int up[K][N];
int mx[K][N];

bool orig[N];
bool seen[N];
int id[N];
int rev_id[N];
int parent[N];

map<int, int> mp[N];

long long ans = 0;

struct Node {
    int val;
    long long sum;
    int left;
    int right;
    Node() : val(0), sum(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

pair<int, long long> query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return make_pair(0, 0);
    }
    if (lq <= l && rq >= r) {
        return make_pair(nodes[node].val, nodes[node].sum);
    }
    int mid = (l + r) / 2;
    pair<int, long long> ans = make_pair(0, 0);
    if (nodes[node].left != -1) {
        pair<int, long long> lf = query(nodes[node].left, l, mid, lq, rq);
        ans.first += lf.first;
        ans.second += lf.second;
    }
    if (nodes[node].right != -1) {
        pair<int, long long> rt = query(nodes[node].right, mid + 1, r, lq, rq);
        ans.first += rt.first;
        ans.second += rt.second;
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val += val;
        nodes[node].sum += (long long)val * l;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = 0;
    nodes[node].sum = 0;
    if (nodes[node].left != -1) {
        nodes[node].val += nodes[nodes[node].left].val;
        nodes[node].sum += nodes[nodes[node].left].sum;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
        nodes[node].sum += nodes[nodes[node].right].sum;
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
    for (auto it = mp[a].begin(); it != mp[a].end(); it++) {
        pair<int, long long> lf = query(b, 0, R - 1, 0, it->first);
        ans += (long long)it->first * lf.first * it->second;
        pair<int, long long> rt = query(b, 0, R - 1, it->first + 1, R - 1);
        ans += (long long)it->second * rt.second;
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); it++) {
        mp[b][it->first] += it->second;
        update(b, 0, R - 1, it->first, it->second);
    }
    return;
}

int kth(int u, int d) {
    int cur = 0;
    for (int k = K - 1; k >= 0; k--) {
        int c = d & (1 << k);
        if (c) {
            cur = max(cur, mx[k][u]);
            u = up[k][u];
        }
    }
    return cur;

}

void dfs_aux(int u, int p) {
    for (int v : aux[u]) {
        if (v != p) {
            dfs_aux(v, u);
            int d = depth[rev_id[v]] - depth[rev_id[u]];
            int wt = kth(rev_id[v], d);
            int b = dsu_find(v);
            int sum = 0;
            while (mp[b].size()) {
                auto it = mp[b].begin();
                if (it->first >= wt) {
                    break;
                }
                sum += it->second;
                update(b, 0, R - 1, it->first, -it->second);
                mp[b].erase(mp[b].begin());
            }
            if (sum != 0) {
                mp[b][wt] += sum;
                update(b, 0, R - 1, wt, sum);
            }
            if (orig[rev_id[u]]) {
                pair<int, long long> cur = query(b, 0, R - 1, 0, R - 1);
                ans += cur.second;
            }
            int a = dsu_find(u);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    if (orig[rev_id[u]]) {
        mp[a][0]++;
        update(a, 0, R - 1, 0, 1);
    }
    return;
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        int u = tour[i - 1];
        table[0][i] = depth[u];
        mn[0][i] = u;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] < table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] < table[k][r - (1 << k) + 1]) {
        return mn[k][l];
    }
    return mn[k][r - (1 << k) + 1];
}

int lca(int a, int b) {
    int l = pos[a];
    int r = pos[b];
    if (l > r) {
        swap(l, r);
    }
    return query(l, r);
}

void dfs(int u, int p) {
    pos[u] = euler;
    tour[euler++] = u;
    tin[u] = timer++;

    up[0][u] = p;
    mx[0][u] = val[u];
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
        mx[k][u] = max(mx[k - 1][u], mx[k - 1][up[k - 1][u]]);
    }

    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour[euler++] = u;
        }
    }
    tout[u] = timer++;
    return;
}

vector<int> aux_tree(vector<int> nodes) {
    sort(nodes.begin(), nodes.end(), [](int u, int v) {
        return tin[u] < tin[v];
    });
    int k = nodes.size();
    for (int i = 1; i < k; i++) {
        int l = lca(nodes[i - 1], nodes[i]);
        if (!seen[l]) {
            seen[l] = true;
            nodes.push_back(l);
        }
    }
    sort(nodes.begin(), nodes.end(), [](int u, int v) {
        return tin[u] < tin[v];
    });
    k = nodes.size();

    for (int i = 0; i < k; i++) {
        id[nodes[i]] = i;
        rev_id[i] = nodes[i];
    }

    vector<int> st;
    st.push_back(nodes[0]);
    for (int i = 1; i < k; i++) {
        int cur = nodes[i];
        while (!st.empty() && !is_ancestor(st.back(), cur)) {
            st.pop_back();
        }
        int u = st.back(), v = cur;
        aux[id[u]].push_back(id[v]);
        aux[id[v]].push_back(id[u]);
        st.push_back(cur);
    }

    return nodes;
}
int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        for (int i = 1; i < n; i++) {
            cin >> val[i];
        }
        dfs(0, 0);
        build(2 * n - 1);
        for (int i = 0; i < q; i++) {
            int k;
            cin >> k;
            vector<int> nodes_aux;
            for (int j = 0; j < k; j++) {
                int u;
                cin >> u;
                u--;
                nodes_aux.push_back(u);
                seen[u] = true;
                orig[u] = true;
            }
            nodes_aux = aux_tree(nodes_aux);
            for (int j = 0; j < nodes_aux.size(); j++) {
                nodes[idx++] = Node();
                parent[j] = j;
            }
            dfs_aux(0, 0);
            cout << ans << " ";

            for (int j = 0; j < nodes_aux.size(); j++) {
                aux[j].clear();
                mp[j].clear();
                seen[nodes_aux[j]] = false;
                orig[nodes_aux[j]] = false;
            }
            idx = 0;
            ans = 0;
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        timer = 0;
        euler = 0;
    }
    return 0;
}
