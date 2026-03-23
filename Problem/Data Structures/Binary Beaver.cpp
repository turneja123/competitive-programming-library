//https://mitit.org/Contest/ViewProblem/binary-beaver?cid=qualification-2026-1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 25000000;

struct Node {
    int left;
    int right;
    int ct;
    int freq;
    int ans;
    Node() {
        left = -1;
        right = -1;
        ct = 0;
        freq= 0;
        ans = 0;

    }
}__attribute__((packed));
static_assert(sizeof(Node) == 20, "");

Node nodes[MAX];
int idx = 0, K;

void add(int node, int d, ll val) {
    if (d == K) {
        return;
    }
    ll c = val & (1ll << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d + 1, val);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d + 1, val);
        return;
    }
}

void upd(int node, int d, ll val, int x) {
    if (d == K) {
        nodes[node].freq += x;
        if (x == 1 && nodes[node].freq == 1) {
            nodes[node].ct++;
        }
        if (nodes[node].freq == 0) {
            nodes[node].ct--;
        }

        return;
    }
    ll c = val & (1ll << d);
    if (c == 0) {
        upd(nodes[node].left, d + 1, val, x);
    } else {
        upd(nodes[node].right, d + 1, val, x);
    }
    nodes[node].ct = (nodes[node].left == -1 ? 0 : nodes[nodes[node].left].ct) + (nodes[node].right == -1 ? 0 : nodes[nodes[node].right].ct);
    nodes[node].freq = (nodes[node].left == -1 ? 0 : nodes[nodes[node].left].freq) + (nodes[node].right == -1 ? 0 : nodes[nodes[node].right].freq);
    nodes[node].ans = 0;
    ll full = 1ll << (K - d - 1);
    if (nodes[node].left != -1 && nodes[nodes[node].left].ct < full) {
        nodes[node].ans = max(nodes[node].ans, nodes[nodes[node].left].freq + nodes[nodes[node].left].ans);
    }
    if (nodes[node].right != -1 && nodes[nodes[node].right].ct < full) {
        nodes[node].ans = max(nodes[node].ans, nodes[nodes[node].right].freq + nodes[nodes[node].right].ans);
    }
}


int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        nodes[idx++] = Node();
        int n, q;
        cin >> n >> q >> K;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            add(0, 0, a[i]);
        }
        vector<pair<int, ll>> queries;
        for (int i = 0; i < q; i++) {
            int j; ll x;
            cin >> j >> x;
            j--;
            queries.push_back({j, x});
            add(0, 0, x);
        }
        for (int i = 0; i < n; i++) {
            upd(0, 0, a[i], 1);
        }
        cout << nodes[0].ans << endl;
        for (int i = 0; i < q; i++) {
            auto [j, x] = queries[i];
            upd(0, 0, a[j], -1);
            a[j] = x;
            upd(0, 0, a[j], 1);
            cout << nodes[0].ans << endl;
        }
        idx = 0;
    }

    return 0;
}
