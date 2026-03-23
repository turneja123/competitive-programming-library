//https://evaluator.hsin.hr/events/coci26_6/tasks/HONI252667skijanje/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

const int L = 0, R = 1e5 + 1;

const int MAX = 6e6;
const long long INF = 2e18;

struct Line {
    long long k, b;
    long long f(long long x) {
        return k * x + b;
    }
    Line(long long k, long long b) : k(k), b(b) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, -INF), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

void add(int l, int r, int node, Line cur) {
    if (l > r) {
        return;
    }
    int mid = (l + r) / 2;
    bool lf = cur.f(l) > nodes[node].line.f(l);
    bool md = cur.f(mid) > nodes[node].line.f(mid);
    if (md) {
        swap(nodes[node].line, cur);
    }
    if (l == r) {
        return;
    }
    if (lf != md) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(cur);
        } else {
            add(l, mid, nodes[node].left, cur);
        }
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(cur);
        } else {
            add(mid + 1, r, nodes[node].right, cur);
        }
    }
    return;
}

long long query(int l, int r, int node, long long x) {
    if (l > r) {
        return -INF;
    }
    int mid = (l + r) / 2;
    long long ans = nodes[node].line.f(x);
    if (l == r) {
        return ans;
    }
    if (x <= mid && nodes[node].left != -1) {
        ans = max(ans, query(l, mid, nodes[node].left, x));
    }
    if (x > mid && nodes[node].right != -1) {
        ans = max(ans, query(mid + 1, r, nodes[node].right, x));
    }
    return ans;
}


int segtree[4 * N];

ll query_seg(int l, int r, int lq, int rq, int x, int node) {
    if (l > rq || r < lq) {
        return -INF;
    }

    if (lq <= l && rq >= r) {
        return query(L, R, segtree[node], x);
    }

    int mid = (l + r) / 2;
    ll ans = max(query_seg(l, mid, lq, rq, x, 2 * node + 1), query_seg(mid + 1, r, lq, rq, x, 2 * node + 2));
    return ans;
}

void update(int l, int r, int ind, Line cur, int node) {

    add(L, R, segtree[node], cur);
    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, cur, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, cur, 2 * node + 2);
    }
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    segtree[node] = idx;
    nodes[idx++] = Node();
    if (l == r) {

        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
}

int up[N];
int z[N];
int b[N];
ll pref[N];
int out[N];
int tim = 0;

ll kk[N];
ll bb[N];

vector<int> st;
vector<int> adj[N];

void dfs1(int u, int p, int n, int k) {
    st.push_back(u);
    if (u != p) {
        pref[u] = pref[p] + b[u];

        int m = st.size();
        int j = max((m - 1) - (k - 1), 1);
        up[u] = st[j];
        kk[u] = -pref[p];
        bb[u] = (ll)z[u] * z[u];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u, n, k);
        }
    }
    st.pop_back();
    out[u] = tim++;

}


ll ans = -INF;

void dfs2(int u, int p, int n) {
    if (u != p) {
        Line cur = Line(kk[u], bb[u]);
        update(0, n - 1, out[u], cur, 0);
        ans = max(ans, (ll)z[u] * (z[u] + pref[u]) + query_seg(0, n - 1, out[u], out[up[u]], z[u], 0));
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u, n);
        }
    }
}



int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    for (int i = 1; i < n; i++) {
        cin >> z[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> b[i];
    }

    build(0, n - 1, 0);
    dfs1(0, 0, n, k);
    dfs2(0, 0, n);
    cout << ans;


    return 0;
}

