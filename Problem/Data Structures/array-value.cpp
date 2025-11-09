//https://codeforces.com/contest/1983/problem/F
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
    int mx;
    Node() {
        left = -1;
        right = -1;
        mx = -1;
    }
};

Node nodes[MAX];
int idx = 0;

void add(int node, int d, int val, int j) {
    nodes[node].mx = max(nodes[node].mx, j);
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val, j);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val, j);
        return;
    }
}

int query(int node, int d, int val, int k) {
    if (d < 0) {
        return -1;
    }
    int ans = -1;
    int ca = val & (1 << d), cb = k & (1 << d);
    if (ca && cb) {
        if (nodes[node].right != -1) {
            ans = max(ans, nodes[nodes[node].right].mx);
        }
        if (nodes[node].left != -1) {
            ans = max(ans, query(nodes[node].left, d - 1, val, k));
        }
    } else if (ca && !cb) {
        if (nodes[node].right != -1) {
            ans = max(ans, query(nodes[node].right, d - 1, val, k));
        }
    } else if (!ca && cb) {
        if (nodes[node].left != -1) {
            ans = max(ans, nodes[nodes[node].left].mx);
        }
        if (nodes[node].right != -1) {
            ans = max(ans, query(nodes[node].right, d - 1, val, k));
        }
    } else if (!ca && !cb) {
        if (nodes[node].left != -1) {
            ans = max(ans, query(nodes[node].left, d - 1, val, k));
        }
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; ll k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll tot = (ll)n * (n - 1) / 2;
        int l = 0, r = 2e9, spl = -1;
        while (l <= r) {
            int mid = ((ll)l + r) / 2;
            idx = 0;
            nodes[idx++] = Node();
            ll ans = 0; int j = 0;
            for (int i = 0; i < n; i++) {
                j = max(j, query(0, 30, a[i], mid) + 1);
                add(0, 30, a[i], i);
                ans += i - j;
            }
            if (tot - ans >= k) {
                spl = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }

        }
        cout << spl - 1 << endl;


    }

    return 0;
}
