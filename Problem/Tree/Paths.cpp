//https://oj.uz/problem/view/RMI21_paths
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll INF = 1e18;


int timer = 0;
int tin[N];
int leaf[N];
int tour[N];
int sz[N];
ll ans[N];

tree<pair<ll, int>, null_type, greater<pair<ll, int>>, rb_tree_tag, tree_order_statistics_node_update> tr;
vector<pair<int, int>> adj[N];

struct Node {
    ll mx;
    int u;
    Node() {
        mx = -INF;
        u = -1;

    }
    Node(int _u) {
        if (leaf[_u]) {
            mx = 0;
            u = _u;
        } else {
            mx = -INF;
            u = -1;
        }
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.mx == -INF) {
        return right;
    }
    if (right.mx == -INF) {
        return left;
    }
    if (left.mx > right.mx) {
        node.mx = left.mx;
        node.u = left.u;
    } else {
        node.mx = right.mx;
        node.u = right.u;
    }
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel = Node();
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int add, int node) {
    if (l == r) {
        segtree[node].mx += add;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, add, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, add, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(tour[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void dfs_tin(int u, int p) {
    tin[u] = timer;
    tour[timer] = u;
    timer++;
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs_tin(v, u);
            sz[u] += sz[v];
        }
    }
    if (adj[u].size() == 1) {
        leaf[u] = 1;
    }
}

ll sum = 0;

void rem(ll wt, int u, int k) {
    if (wt != 0) {
        int ord = tr.order_of_key({wt, u});
        tr.erase({wt, u});
        if (ord < k) {
            sum -= wt;
            if (tr.size() >= k) {
                sum += tr.find_by_order(k - 1)->first;
            }
        }
    }
}

void add(ll wt, int u, int k) {
    if (wt != 0) {
        int ord = tr.order_of_key({wt, u});
        if (ord < k) {
            sum += wt;
            if (tr.size() >= k) {
                sum -= tr.find_by_order(k - 1)->first;
            }
        }
        tr.insert({wt, u});
    }
}

void dfs_subtree(int u, int p, int k, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u, k, n);
            Node node = query(0, n - 1, tin[v], tin[v] + sz[v] - 1, 0);
            rem(node.mx, node.u, k);
            add(node.mx + wt, node.u, k);
            update(0, n - 1, tin[node.u], wt, 0);
        }
    }
}

vector<tuple<ll, int, int>> restore;

void dfs_dp(int u, int p, int k, int n) {
    ans[u] = sum;
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            Node nodeU = Node();
            int l = tin[v], r = tin[v] + sz[v] - 1;
            if (l != 0) {
                nodeU = combine(nodeU, query(0, n - 1, 0, l - 1, 0));
            }
            if (r != n - 1) {
                nodeU = combine(nodeU, query(0, n - 1, r + 1, n - 1, 0));
            }
            Node nodeD = query(0, n - 1, tin[v], tin[v] + sz[v] - 1, 0);

            restore.push_back({nodeD.mx, wt, nodeD.u});
            restore.push_back({nodeU.mx, -wt, nodeU.u});

            rem(nodeD.mx, nodeD.u, k);
            add(nodeD.mx - wt, nodeD.u, k);
            update(0, n - 1, tin[nodeD.u], -wt, 0);

            rem(nodeU.mx, nodeU.u, k);
            add(nodeU.mx + wt, nodeU.u, k);
            update(0, n - 1, tin[nodeU.u], wt, 0);


            dfs_dp(v, u, k, n);
            for (int i = 0; i < 2; i++) {
                auto [mx, wt, U] = restore.back();
                restore.pop_back();

                rem(mx - wt, U, k);
                add(mx, U, k);
                update(0, n - 1, tin[U], wt, 0);
            }

        }

    }

}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    dfs_tin(0, 0);
    build(0, n - 1, 0);
    dfs_subtree(0, 0, k, n);
    dfs_dp(0, 0, k, n);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
