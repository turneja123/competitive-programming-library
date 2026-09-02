//https://codeforces.com/contest/1326/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

struct Node {
    int suf;
    int sum;
    int mn;
    Node() {}
    Node(int x) {
        suf = x, sum = x; mn = x;
    }
};

Node segtree[4 * N];
int cur[N];
int p[N];
int pos[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    node.suf = min(right.suf, right.sum + left.suf);
    node.mn = min(node.suf, right.suf);
    return node;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        cur[l] += val;
        segtree[node] = Node(cur[l]);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(0);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    cout << n << " ";
    build(0, n - 1, 0);
    int ans = n - 1;

    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        j--;
        if (i == n - 1) {
            break;
        }
        update(0, n - 1, j, 1, 0);
        while (ans > 0) {
            update(0, n - 1, pos[ans], -1, 0);
            if (segtree[0].mn < 0) {
                update(0, n - 1, pos[ans], 1, 0);
                break;
            }
            ans--;
        }
        cout << ans + 1 << " ";
    }


    return 0;
}
