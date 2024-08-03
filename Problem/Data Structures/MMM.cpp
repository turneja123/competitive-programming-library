//https://www.spoj.com/problems/DCEPCA09/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
int vals[N];
int freq[N];
long long pref[N];
int sz;
tuple<int, int, int> queries[N];
tuple<int, int, int> ans[N];
map<int, int> ct[N];

const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int val[N];
pair<int, int> compr[N];
int med;

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

void query(int node_l, int node_r, int l, int r, int k) {
    if (l == r) {
        med = l;
        return;
    }
    int mid = (l + r) / 2;
    int ct = nodes[nodes[node_r].left].val - nodes[nodes[node_l].left].val;
    if (ct > k) {
        query(nodes[node_l].left, nodes[node_r].left, l, mid, k);
    } else {
        query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, k - ct);
    }
    return;
}

bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    sz = sqrt(n);
    if (sz * sz != n) {
        sz++;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[i] = a[i];
        compr[i] = make_pair(a[i], i);
        pref[i] = a[i] + ((i == 0) ? 0 : pref[i - 1]);
        ct[0][vals[i]] = 1;
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        val[m] = a[compr[i].second];
        a[compr[i].second] = m;
    }
    m++;
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, m - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, m - 1, a[i]);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int mx = 0, best = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        while (r < rq) {
            r++;
            ct[freq[a[r]]].erase(vals[r]);
            freq[a[r]]++;
            ct[freq[a[r]]][vals[r]] = 1;
            if (freq[a[r]] > mx) {
                mx = freq[a[r]];
            }
        }
        while (r > rq) {
            ct[freq[a[r]]].erase(vals[r]);
            if (freq[a[r]] == mx && ct[freq[a[r]]].size() == 0) {
                mx--;
            }
            freq[a[r]]--;
            ct[freq[a[r]]][vals[r]] = 1;
            r--;
        }
        while (l < lq) {
            ct[freq[a[l]]].erase(vals[l]);
            if (freq[a[l]] == mx && ct[freq[a[l]]].size() == 0) {
                mx--;
            }
            freq[a[l]]--;
            ct[freq[a[l]]][vals[l]] = 1;
            l++;
        }
        while (l > lq) {
            l--;
            ct[freq[a[l]]].erase(vals[l]);
            freq[a[l]]++;
            ct[freq[a[l]]][vals[l]] = 1;
            if (freq[a[l]] > mx) {
                mx = freq[a[l]];
            }
        }
        int s = (r - l + 1);
        query(root[l], root[r + 1], 0, m - 1, s / 2);
        int mid = val[med];
        if (s % 2 == 0) {
            query(root[l], root[r + 1], 0, m - 1, s / 2 - 1);
            mid = (mid + val[med]) / 2;
        }
        ans[cur] = make_tuple((pref[r] - ((l == 0) ? 0 : pref[l - 1])) / s, mid, ct[mx].rbegin()->first);
    }
    for (int i = 0; i < q; i++) {
        cout << get<0>(ans[i]) << " " << get<1>(ans[i]) << " " << get<2>(ans[i]) << endl;
    }
    return 0;
}
