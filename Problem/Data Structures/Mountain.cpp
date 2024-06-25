//https://dmoj.ca/problem/ioi05p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int R = 1e9 + 5;

int ans;

struct Node {
    int val;
    int pref;
    int lazy;
    int left;
    int right;
    Node() : val(0), pref(0), lazy(R), left(-1), right(-1) {}
};

vector<Node> nodes;


void compose(int parent, int node) {
    nodes[node].lazy = nodes[parent].lazy;
}

void apply(int node, int l, int r) {
    if (nodes[node].lazy != R) {
        nodes[node].val = nodes[node].lazy * (r - l + 1);
        nodes[node].pref = max(0, nodes[node].val);
    }
    if (l != r) {
        if (nodes[node].left == -1) {
            nodes.push_back(Node());
            nodes[node].left = nodes.size() - 1;
        }
        if (nodes[node].right == -1) {
            nodes.push_back(Node());
            nodes[node].right = nodes.size() - 1;
        }
    }
    if (l != r && nodes[node].lazy != R) {
        compose(node, nodes[node].left);
        compose(node, nodes[node].right);
    }
    nodes[node].lazy = R;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy = val;
        return;
    }
    int mid = (l + r) / 2;
    apply(node, l, r);
    setUpdate(nodes[node].left, l, mid, lq, rq, val);
    setUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    nodes[node].pref = max(nodes[nodes[node].left].pref, nodes[nodes[node].left].val + nodes[nodes[node].right].pref);
}

void query(int node, int l, int r, int cur, int h) {
    apply(node, l, r);
    if (cur + nodes[node].pref <= h) {
        ans = max(ans, r);
        return;
    }
    if (l == r) {
        if (cur + nodes[node].val <= h) {
            ans = max(ans, l);
        }
        return;
    }

    int mid = (l + r) / 2;
    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);

    if (cur + nodes[nodes[node].left].pref <= h) {
        ans = max(ans, mid);
        query(nodes[node].right, mid + 1, r, cur + nodes[nodes[node].left].val, h);
    } else {
        query(nodes[node].left, l, mid, cur, h);

    }
    return;
}

int main() {
    IOS;
    nodes.push_back(Node());
    int n;
    cin >> n;
    while (1) {
        char c;
        cin >> c;
        if (c == 'E') {
            break;
        }
        if (c == 'I') {
            int l, r, h;
            cin >> l >> r >> h;
            setUpdate(0, 0, n, l, r, h);
        } else {
            int h;
            cin >> h;
            ans = 0;
            query(0, 0, n, 0, h);
            cout << ans << endl;

        }

    }
    return 0;
}
