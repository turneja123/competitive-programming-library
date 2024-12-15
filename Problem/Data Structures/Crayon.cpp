//https://www.spoj.com/problems/CRAYON/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

const int R = 1e9 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
pair<int, int> ivals[N];

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val += val;
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
    nodes[idx++] = Node();
    nodes[idx++] = Node();
    int t, m = 0, sz = 0;
    cin >> t;
    while (t--) {
        char c;
        cin >> c;
        if (c == 'D') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ivals[m++] = make_pair(l, r);
            update(0, 0, R - 1, l, 1);
            update(1, 0, R - 1, r, 1);
            sz++;
        } else if (c == 'Q') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int ans = sz - query(0, 0, R - 1, r + 1, R - 1) - query(1, 0, R - 1, 0, l - 1);
            cout << ans << endl;
        } else {
            int j;
            cin >> j;
            j--;
            int l = ivals[j].first, r = ivals[j].second;
            update(0, 0, R - 1, l, -1);
            update(1, 0, R - 1, r, -1);
            sz--;
        }
    }

    return 0;
}
