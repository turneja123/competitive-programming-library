//https://cses.fi/problemset/task/1655/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int left;
    int right;
    Node() : left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int d, int val, int ans) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].right != -1) {
            return query(nodes[node].right, d - 1, val, ans ^ (1 << d));
        } else {
            return query(nodes[node].left, d - 1, val, ans);
        }
    } else {
        if (nodes[node].left != -1) {
            return query(nodes[node].left, d - 1, val, ans ^ (1 << d));
        } else {
            return query(nodes[node].right, d - 1, val, ans);
        }
    }
}

void add(int node, int d, int val) {
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
    int n;
    cin >> n;
    add(0, 30, 0);
    int sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sum ^= a;
        ans = max(ans, query(0, 30, sum, 0));
        add(0, 30, sum);
    }
    cout << ans;

    return 0;
}
