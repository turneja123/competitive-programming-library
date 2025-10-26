//https://cses.fi/problemset/task/2184
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 5e6;
const int INF = 1e9;


struct Node {
    ll val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];

int val[N];
vector<int> pos, sorted;

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

void update(int node_prev, int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, val);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

ll query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val - nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int j = -1;

void trav(int node_l, int node_r, int l, int r) {
    if (l == r) {
        j = l;
        return;
    }
    int mid = (l + r) / 2;
    int z = nodes[nodes[node_r].left].val - nodes[nodes[node_l].left].val;
    if (z > 0) {
        trav(nodes[node_l].left, nodes[node_r].left, l, mid);
    } else {
        trav(nodes[node_l].right, nodes[node_r].right, mid + 1, r);
    }

}

void query_mn(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l || j != -1) {
        return;
    }
    if (lq <= l && rq >= r) {
        if (nodes[node_r].val - nodes[node_l].val > 0) {
            trav(node_l, node_r, l, r);
        }
        return;
    }
    int mid = (l + r) / 2;
    query_mn(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq);
    query_mn(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}


int id(int x) {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    sorted.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorted[i] = a[i];
        if (a[i] == 1) {
            pos.push_back(i);
        }
    }
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int m = sorted.size();
    for (int i = 0; i < m; i++) {
        val[i] = sorted[i];
    }

    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, m - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, m - 1, id(a[i]), a[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        auto it = lower_bound(pos.begin(), pos.end(), l);
        if (it == pos.end() || *it > r) {
            cout << 1 << endl;
            continue;
        }
        ll ans = -1;
        ll x = query(root[l], root[r + 1], 0, m - 1, 0, 0);
        while (1) {
            j = -1;
            int k = id(x + 2);
            if (k == m) {
                break;
            }
            query_mn(root[l], root[r + 1], 0, m - 1, k, m - 1);
            ll s = query(root[l], root[r + 1], 0, m - 1, 0, k - 1);
            if (j == -1) {
                break;
            }
            if (s + 1 < val[j]) {
                ans = s + 1;
                break;
            }
            x = s;
            if (s > INF) {
                break;
            }
        }
        if (ans == -1) {
            ans = query(root[l], root[r + 1], 0, m - 1, 0, m - 1) + 1;
        }
        cout << ans << endl;
    }


    return 0;
}
