//https://atcoder.jp/contests/abc393/tasks/abc393_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int R = 1e9 + 5;
const int MAX = 2e7 + 5;

int a[N];
int ansq[N];

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2;
    int ans = 0;
    if (nodes[node].left != -1) {
        ans = max(ans, query(nodes[node].left, l, mid, lq, rq));
    }
    if (nodes[node].right != -1) {
        ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq));
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = max(nodes[node].val, val);
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
    if (nodes[node].left != -1) {
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].left].val);
    }
    if (nodes[node].right != -1) {
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].right].val);
    }
}


int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int r, x;
        cin >> r >> x;
        r--;
        queries.push_back(make_tuple(r, x, i));

    }
    sort(queries.begin(), queries.end());
    int j = 0;
    for (int i = 0; i < n; i++) {
        int best = query(0, 0, R - 1, 0, a[i] - 1);
        update(0, 0, R - 1, a[i], best + 1);
        while (j < q && get<0>(queries[j]) == i) {
            auto [cc, x, ind] = queries[j];
            ansq[ind] = query(0, 0, R - 1, 0, x);
            j++;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ansq[i] << endl;
    }

    return 0;
}
