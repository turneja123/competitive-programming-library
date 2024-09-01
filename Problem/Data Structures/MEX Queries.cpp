//https://codeforces.com/contest/817/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long R = 1e18 + 5;
const int MAX = 1e7 + 5 + 1e6 + 5;

struct Node {
    long long val;
    bool lazy;
    bool setVal;
    bool setValid;

    int left;
    int right;
    Node() : val(0), lazy(false), left(-1), right(-1), setVal(false), setValid(false) {}
};

Node nodes[MAX];
int idx = 0;
long long ind;

void compose(int parent, int child) {
    if (nodes[parent].setValid) {
        nodes[child].setValid = 1;
        nodes[child].setVal = nodes[parent].setVal;
        nodes[child].lazy = nodes[parent].lazy;
    } else {
        nodes[child].lazy ^= nodes[parent].lazy;
    }
}

void apply(int node, long long l, long long r) {
    if (nodes[node].setValid) {
        if (nodes[node].setVal) {
            nodes[node].val = r - l + 1;
        } else {
            nodes[node].val = 0;
        }
    }
    if (nodes[node].lazy) {
        nodes[node].val = r - l + 1 - nodes[node].val;
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
    nodes[node].setVal = false;
    nodes[node].setValid = false;
}

void setUpdate(int node, long long l, long long r, long long lq, long long rq, bool val) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy = false;
        nodes[node].setValid = true;
        nodes[node].setVal = val;
        return;
    }
    long long mid = (l + r) / 2;
    apply(node, l, r);

    setUpdate(nodes[node].left, l, mid, lq, rq, val);
    setUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
}

void incUpdate(int node, long long l, long long r, long long lq, long long rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy = !nodes[node].lazy;
        return;
    }
    long long mid = (l + r) / 2;
    apply(node, l, r);

    incUpdate(nodes[node].left, l, mid, lq, rq);
    incUpdate(nodes[node].right, mid + 1, r, lq, rq);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
}

void query(int node, long long l, long long r) {
    apply(node, l, r);
    if (l == r) {
        ind = l;
        return;
    }
    long long mid = (l + r) / 2;

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);

    if (nodes[nodes[node].left].val != mid - l + 1) {
        query(nodes[node].left, l, mid);
    } else {
        query(nodes[node].right, mid + 1, r);
    }
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int q;
    cin >> q;
    setUpdate(0, 0, R - 1, 0, 0, 1);
    for (int i = 0; i < q; i++) {
        int t; long long l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            setUpdate(0, 0, R - 1, l, r, 1);
        } else if (t == 2) {
            setUpdate(0, 0, R - 1, l, r, 0);
        } else {
            incUpdate(0, 0, R - 1, l, r);
        }
        ind = 0;
        query(0, 0, R - 1);
        cout << ind << endl;
        assert(idx < MAX - 300);

    }
    return 0;
}
