//https://www.spoj.com/problems/BLUNIQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1e7 + 5;
const int R = 1e9 + 5 + (2e5 + 5);

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
        return R;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = R;
    if (nodes[node].left != -1) {
        ans = min(ans, query(nodes[node].left, l, mid, lq, rq));
    } else {
        if (mid >= lq) {
            ans = min(ans, max(l, lq));
        }
    }
    if (nodes[node].right != -1) {
        ans = min(ans, query(nodes[node].right, mid + 1, r, lq, rq));
    } else {
        if (r >= lq) {
            ans = min(ans, max(mid + 1, lq));
        }
    }
    return ans;
}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = val;
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
    nodes[node].val = R;
    if (nodes[node].left != -1) {
        nodes[node].val = min(nodes[node].val, nodes[nodes[node].left].val);
    } else {
        nodes[node].val = min(nodes[node].val, l);
    }
    if (nodes[node].right != -1) {
        nodes[node].val = min(nodes[node].val, nodes[nodes[node].right].val);
    } else {
        nodes[node].val = min(nodes[node].val, mid + 1);
    }
    return;
}


int main() {
    IOS;
    nodes[idx++] = Node();
    int t;
    cin >> t;
    while (t--) {
        int q, x;
        cin >> q >> x;
        if (q == 1) {
            int y = query(0, 0, R - 1, x, R - 1);
            cout << y << endl;
            update(0, 0, R - 1, y, R);
        } else {
            update(0, 0, R - 1, x, x);
        }
    }
    return 0;

}
