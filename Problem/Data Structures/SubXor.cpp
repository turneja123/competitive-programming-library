//https://www.spoj.com/problems/SUBXOR/
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
    long long val;
    Node() : left(-1), right(-1), val(0) {}
};

Node nodes[MAX];
int idx = 0;

long long query(int node, int d, int val, int k) {
    if (d == -1) {
        return nodes[node].val;
    }
    int c = val & (1 << d), x = k & (1 << d);
    long long sum = 0;
    if (c == 0) {
        if (nodes[node].right != -1) {
            if (x != 0) {
                sum += query(nodes[node].right, d - 1, val, k);
            }
        }
        if (nodes[node].left != -1) {
            if (x != 0) {
                sum += nodes[nodes[node].left].val;
            } else {
                sum += query(nodes[node].left, d - 1, val, k);
            }
        }
    } else {
        if (nodes[node].left != -1) {
            if (x != 0) {
                sum += query(nodes[node].left, d - 1, val, k);
            }
        }
        if (nodes[node].right != -1) {
            if (x != 0) {
                sum += nodes[nodes[node].right].val;
            } else {
                sum += query(nodes[node].right, d - 1, val, k);
            }
        }
    }
    return sum;
}

void add(int node, int d, int val) {
    if (d < 0) {
        nodes[node].val++;
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val);
    }
    nodes[node].val = 0;
    if (nodes[node].left != -1) {
        nodes[node].val += nodes[nodes[node].left].val;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        nodes[idx++] = Node();
        int n, k;
        cin >> n >> k;
        add(0, 20, 0);
        int sum = 0; long long ans = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            sum ^= a;
            ans += query(0, 20, sum, k - 1);
            add(0, 20, sum);
        }
        cout << ans << endl;
        idx = 0;
    }

    return 0;
}
