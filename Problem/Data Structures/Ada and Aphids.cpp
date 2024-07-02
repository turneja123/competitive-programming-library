//https://www.spoj.com/problems/ADAAPHID/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long R = 1e18 + 2e17;
const int MAX = 4e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

long long query(int node, long long l, long long r, long long lq, long long rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    long long mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(int node, long long l, long long r, long long ind, int val) {
    if (l == r) {
        nodes[node].val += val;
        return;
    }
    long long mid = (l + r) / 2;
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
    int n;
    cin >> n;
    long long lastans = 0;
    for (int i = 0; i < n; i++) {
        assert(idx < MAX - 1000);
        long long r, x;
        cin >> r >> x;
        r ^= lastans, x ^= lastans;
        long long k = query(0, 0, R - 1, 0, r);
        lastans = x + k;
        update(0, 0, R - 1, r, x);
        cout << r << " " << lastans << endl;
    }
    return 0;
}
