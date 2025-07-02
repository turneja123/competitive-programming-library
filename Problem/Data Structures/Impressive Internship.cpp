//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define f first
#define s second

const int N = 4e5 + 5;
const int MAX = 1e7 + 5;
const int INF = 2e9 + 5;

map<int, pair<long long, long long>> mp;

mt19937 ge(chrono::steady_clock::now().time_since_epoch().count());

long long gen() {
    long long h = ge() + ((long long)ge() << 30);
    return h;
}

struct Node {
    pair<long long, long long> val;
    int left;
    int right;
    Node() : val({0, 0}), left(-1), right(-1) {}
};

Node nodes[MAX];
int root[N];
int idx =0;

void update(int node_prev, int node, int l, int r, int ind, pair<long long, long long> val) {
    if (l == r) {
        nodes[node].val.f = (node_prev == -1 ? 0 : nodes[node_prev].val.f) ^ val.f;
        nodes[node].val.s = (node_prev == -1 ? 0 : nodes[node_prev].val.s) ^ val.s;
        return;
    }
    int mid = ((long long)l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = (node_prev == -1 ? -1 : nodes[node_prev].right);
        update((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, l, mid, ind, val);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = (node_prev == -1 ? -1 : nodes[node_prev].left);
        update((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val.f = (nodes[node].left == -1 ? 0 : nodes[nodes[node].left].val.f) ^ (nodes[node].right == -1 ? 0 : nodes[nodes[node].right].val.f);
    nodes[node].val.s = (nodes[node].left == -1 ? 0 : nodes[nodes[node].left].val.s) ^ (nodes[node].right == -1 ? 0 : nodes[nodes[node].right].val.s);
    return;
}

int query(int node_l, int node_r, int l, int r) {
    pair<long long, long long> val;
    val.f = (node_l == -1 ? 0 : nodes[node_l].val.f) ^ (node_r == -1 ? 0 : nodes[node_r].val.f);
    val.s = (node_l == -1 ? 0 : nodes[node_l].val.s) ^ (node_r == -1 ? 0 : nodes[node_r].val.s);
    if (val.f == 0 && val.s == 0) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int lf = (node_l == -1 ? -1 : nodes[node_l].right);
    int rt = (node_r == -1 ? -1 : nodes[node_r].right);
    val.f = (lf == -1 ? 0 : nodes[lf].val.f) ^ (rt == -1 ? 0 : nodes[rt].val.f);
    val.s = (lf == -1 ? 0 : nodes[lf].val.s) ^ (rt == -1 ? 0 : nodes[rt].val.s);
    int mid = ((long long)l + r) / 2;
    if (val.f == 0 && val.s == 0) {
        return query((node_l == -1 ? -1 : nodes[node_l].left), (node_r == -1 ? -1 : nodes[node_r].left), l, mid);
    } else {
        return query(lf, rt, mid + 1, r);
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    int m = 1;
    root[0] = idx++;
    for (int i = 0; i < n; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            u--;
            root[m] = idx++;
            if (mp.find(v) == mp.end()) {
                mp[v] = {gen(), gen()};
            }
            update(root[u], root[m], 0, INF, v, mp[v]);
            m++;
        } else {
            u--, v--;
            cout << query(root[u], root[v], 0, INF) << endl;

        }

    }

    return 0;
}
