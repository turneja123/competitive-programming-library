//https://atcoder.jp/contests/abc360/tasks/abc360_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const int INF = 1e9;

pair<int, int> a[N];
int val[N];

int best = 0;
pair<int, int> ans = make_pair(0, 1);
vector<pair<int, int>> add[N], rem[N];

struct Node {
    int lazy;
    int val;
    int pos;
    Node() {
        lazy = 0, val = 0, pos = INF;
    }
    Node(int p) : lazy(0), val(0), pos(p) {}
};

Node nodes[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val > right.val) {
        node.val = left.val;
        node.pos = left.pos;
    } else if (left.val < right.val) {
        node.val = right.val;
        node.pos = right.pos;
    } else {
        node.val = right.val;
        node.pos = min(left.pos, right.pos);
    }
    return node;
}

void compose(int parent, int child) {
    nodes[child].lazy += nodes[parent].lazy;
}

void apply(int node, int l, int r) {
    nodes[node].val += nodes[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    nodes[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        nodes[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
}

Node getMax(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return Node();
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return nodes[node];
    }
    int mid = (l + r) / 2;
    return combine(getMax(l, mid, lq, rq, 2 * node + 1), getMax(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        nodes[node] = Node(l);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    a[n++] = make_pair(0, INF);
    vector<pair<int, int>> compr;
    for (int i = 0; i < n; i++) {
        compr.push_back(make_pair(a[i].first, 2 * i));
        compr.push_back(make_pair(a[i].second, 2 * i + 1));
        if (a[i].first != 0) {
            compr.push_back(make_pair(a[i].first - 1, -1));
        }
        compr.push_back(make_pair(a[i].first + 1, -1));
        compr.push_back(make_pair(a[i].second - 1, -1));
        if (a[i].second != INF) {
            compr.push_back(make_pair(a[i].second + 1, -1));
        }
    }
    int m = 0;
    sort(compr.begin(), compr.end());
    int last = 0;
    for (int i = 0; i < compr.size(); i++) {
        if (last != compr[i].first) {
            m++;
            val[m] = compr[i].first;
            last = compr[i].first;
        }
        if (compr[i].second != -1) {
            if (compr[i].second % 2 == 0) {
                a[compr[i].second / 2].first = m;
            } else {
                a[compr[i].second / 2].second = m;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i].first + 1 == a[i].second) {
            continue;
        }
        if (a[i].first != 0) {
            add[0].push_back(make_pair(a[i].first + 1, a[i].second - 1));
            rem[a[i].first].push_back(make_pair(a[i].first + 1, a[i].second - 1));
        }
        if (a[i].second != m - 1) {
            add[a[i].first + 1].push_back(make_pair(a[i].second + 1, m - 1));
            rem[a[i].second].push_back(make_pair(a[i].second + 1, m - 1));
        }
    }
    build(0, m - 1, 0);
    for (int i = 0; i < m - 1; i++) {
        for (auto [l, r] : add[i]) {
            incUpdate(0, 0, m - 1, l, r, 1);
        }
        for (auto [l, r] : rem[i]) {
            incUpdate(0, 0, m - 1, l, r, -1);
        }
        Node node = getMax(0, m - 1, i + 1, m - 1, 0);
        if (node.val > best) {
            best = node.val;
            ans = make_pair(i, node.pos);
        } else if (node.val == best) {
            if (i < ans.first) {
                ans = make_pair(i, node.pos);
            } else if (i == ans.first && node.pos < ans.second) {
                ans = make_pair(i, node.pos);
            }
        }
    }
    if (best == 0) {
        cout << "0 1";
    } else {
        cout << val[ans.first] <<  " " << val[ans.second];
    }
    return 0;
}
