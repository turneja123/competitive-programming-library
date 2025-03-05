//https://codeforces.com/contest/2031/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

int ans[N];
int a[N];

struct Node {
    int mn;
    int mx;
    int mnpos;
    int mxpos;
    Node() : mn(INF), mx(-INF), mnpos(-1), mxpos(-1) {}
    Node(int x, int i) : mn(x), mx(x), mnpos(i), mxpos(i) {}
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.mxpos == -1) {
        return right;
    }
    if (right.mxpos == -1) {
        return left;
    }

    if (left.mx > right.mx) {
        node.mx = left.mx;
        node.mxpos = left.mxpos;
    } else {
        node.mx = right.mx;
        node.mxpos = right.mxpos;
    }

    if (left.mn < right.mx) {
        node.mn = left.mn;
        node.mnpos = left.mnpos;
    } else {
        node.mn = right.mn;
        node.mnpos = right.mnpos;
    }

    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return Node();
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = Node();
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l], l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            v[i] = make_pair(a[i], i);
            ans[i] = -1;
        }
        build(0, n - 1, 0);
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        for (auto [x, i] : v) {
            if (ans[i] != -1) {
                continue;
            }
            queue<int> q;
            q.push(i);
            update(0, n - 1, i, 0);
            while (q.size()) {
                int j = q.front();
                q.pop();
                ans[j] = x;
                while (1) {
                    Node qr = query(0, n - 1, 0, j - 1, 0);
                    if (qr.mx <= a[j]) {
                        break;
                    }
                    q.push(qr.mxpos);
                    update(0, n - 1, qr.mxpos, 0);
                }
                while (1) {
                    Node qr = query(0, n - 1, j + 1, n - 1, 0);
                    if (qr.mn >= a[j]) {
                        break;
                    }
                    q.push(qr.mnpos);
                    update(0, n - 1, qr.mnpos, 0);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
