//https://codeforces.com/contest/842/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int left;
    int right;
    int val;
    Node() : left(-1), right(-1), val(0) {}
};

bool seen[N];
Node nodes[MAX];
int idx = 0;

int query(int node, int d, int val, int ans) {
    if (d == -1) {
        return ans + 1;
    }
    int c = val & (1 << d);
    int need = 1 << d;
    if (c == 0) {
        if (nodes[node].left == -1) {
            return ans;
        }
        if (nodes[nodes[node].left].val < need) {
            return query(nodes[node].left, d - 1, val, ans);
        }

        if (nodes[node].right != -1) {
            return query(nodes[node].right, d - 1, val, ans ^ (1 << d));
        } else {
            return ans + need;
        }
    } else {
        if (nodes[node].right == -1) {
            return ans;
        }
        if (nodes[nodes[node].right].val < need) {
            return query(nodes[node].right, d - 1, val, ans);
        }

        if (nodes[node].left != -1) {
            return query(nodes[node].left, d - 1, val, ans ^ (1 << d));
        } else {
            return ans + need;
        }
    }
}

void add(int node, int d, int val) {
    nodes[node].val++;
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val);
        return;
    }
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (seen[a]) {
            continue;
        }
        seen[a] = true;
        add(0, 20, a);
    }
    int sum = 0;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        sum ^= x;
        cout << query(0, 20, sum, 0) << endl;
    }

    return 0;
}
