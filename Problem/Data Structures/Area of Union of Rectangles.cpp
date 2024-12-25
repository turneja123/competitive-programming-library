//https://judge.yosupo.jp/problem/area_of_union_of_rectangles
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int R = 1e9 + 5;
const int MAX = 4e7 + 5;

struct Node {
    int val;
    int ct;
    int lazy;
    int left;
    int right;
    Node() : val(0), ct(0), lazy(0), left(-1), right(-1) {}
    Node(int ct) : val(0), ct(ct), lazy(0), left(-1), right(-1) {}
};

vector<tuple<int, int, int, int>> event;

Node nodes[MAX];
int idx = 0;

void compose(int parent, int node) {
    nodes[node].lazy += nodes[parent].lazy;
}

void apply(int node, int l, int r) {
    if (nodes[node].lazy) {
        nodes[node].val += nodes[node].lazy;
    }
    if (l != r) {
        int mid = (l + r) / 2;
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(mid - l + 1);
        }
        compose(node, nodes[node].left);
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(r - mid);
        }
        compose(node, nodes[node].right);
    }
    nodes[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy += val;
        return;
    }
    int mid = (l + r) / 2;
    apply(node, l, r);

    incUpdate(nodes[node].left, l, mid, lq, rq, val);
    incUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    if (nodes[nodes[node].left].val < nodes[nodes[node].right].val) {
        nodes[node].val = nodes[nodes[node].left].val;
        nodes[node].ct = nodes[nodes[node].left].ct;
    } else if (nodes[nodes[node].left].val > nodes[nodes[node].right].val) {
        nodes[node].val = nodes[nodes[node].right].val;
        nodes[node].ct = nodes[nodes[node].right].ct;
    } else {
        nodes[node].val = nodes[nodes[node].left].val;
        nodes[node].ct = nodes[nodes[node].left].ct + nodes[nodes[node].right].ct;
    }
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node(R);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        event.push_back(make_tuple(x0, y0, y1, 1));
        event.push_back(make_tuple(x1, y0, y1, -1));
    }
    sort(event.begin(), event.end());
    long long ans = 0; int last = get<0>(event[0]);
    for (int i = 0; i < 2 * n; i++) {
        auto [x, y0, y1, add] = event[i];
        ans += (long long)(x - last) * (R - nodes[0].ct);
        incUpdate(0, 0, R - 1, y0, y1 - 1, add);
        last = x;
    }
    cout << ans;
    return 0;
}
