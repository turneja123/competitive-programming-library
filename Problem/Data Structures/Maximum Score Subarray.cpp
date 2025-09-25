//https://www.codechef.com/problems/MAXSUBSCR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct Node {
    int sum;
    int lazy;
    int pos;
    Node() {
        lazy = 0, sum = -N, pos = 0;
    }
    Node(int x, int j) : sum(x), lazy(0), pos(j) {}
};

int a[N];
int b[N];
Node segtree[4 * N];
vector<int> pos[N];
int ptr[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sum > right.sum) {
        node.sum = left.sum;
        node.pos = left.pos;
    } else {
        node.sum = right.sum;
        node.pos = right.pos;
    }
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].sum += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel;
        return sentinel;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(b[l], l);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            b[i] = n - i;
            pos[a[i]].push_back(i);
        }
        build(0, n - 1, 0);
        int l = 0, ans = 1;
        for (int i = 0; i < n; i++) {
            for (int x = ptr[a[i]] - 1; x >= 0; x--) {
                if (pos[a[i]][x] < l) {
                    break;
                }
                incUpdate(0, 0, n - 1, 0, pos[a[i]][x], -1);
            }
            Node node = getSum(0, n - 1, l, i, 0);
            ans = max(ans, node.sum - (n - 1 - i));
            l = max(l, node.pos);
            ptr[a[i]]++;
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            ptr[a[i]] = 0;
            pos[a[i]].clear();
        }
    }


    return 0;
}
