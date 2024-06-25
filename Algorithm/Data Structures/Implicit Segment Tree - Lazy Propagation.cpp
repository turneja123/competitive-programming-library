//https://oj.uz/problem/view/IZhO12_apple
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int R = 1e9 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    bool lazy;
    int left;
    int right;
    Node() : val(0), lazy(false), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

void compose(int parent, int node) {
    nodes[node].lazy |= nodes[parent].lazy;
}

void apply(int node, int l, int r) {
    if (nodes[node].lazy) {
        nodes[node].val = r - l + 1;
    }
    if (l != r) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].left);
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].right);
    }
    nodes[node].lazy = false;
}

void setUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy = true;
        return;
    }
    int mid = (l + r) / 2;
    apply(node, l, r);

    setUpdate(nodes[node].left, l, mid, lq, rq);
    setUpdate(nodes[node].right, mid + 1, r, lq, rq);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
}

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    apply(node, l, r);

    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }

    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int q;
    cin >> q;
    int c = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int l, r;
            cin >> l >> r;
            setUpdate(0, 0, R - 1, l + c, r + c);
        } else {
            int l, r;
            cin >> l >> r;
            int q = query(0, 0, R - 1, l + c, r + c);
            cout << q << endl;
            c = q;
        }
    }
    return 0;
}
