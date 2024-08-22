//https://atcoder.jp/contests/abc365/tasks/abc365_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int R = 1e9 + 5;
const int B = 450;

const int MAX = 6e7 + 5;

struct Node {
    int val;
    bool lazy;
    int left;
    int right;
    Node() : val(0), lazy(false), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

void compose(int parent, int node) {
    nodes[node].lazy |= nodes[parent].lazy;
}

void apply(int node, int l, int r) {
    if (nodes[node].lazy) {
        nodes[node].val = r - l + 1;
    }
    if (l != r && nodes[node].lazy) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].left);
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        compose(node, nodes[node].right);
    }
    nodes[node].lazy = false;
}

void setUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (lq <= l && rq >= r) {
        nodes[node].lazy = true;
        return;
    }
    int mid = (l + r) / 2;
    apply(node, l, r);

    if (nodes[node].left == -1) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
    }
    if (nodes[node].right == -1) {
        nodes[node].right = idx;
        nodes[idx++] = Node();
    }

    setUpdate(nodes[node].left, l, mid, lq, rq);
    setUpdate(nodes[node].right, mid + 1, r, lq, rq);

    apply(nodes[node].left, l, mid);
    apply(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
}

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    apply(node, l, r);

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

int open[N];
int ans[N];

tuple<int, int, int> queries[N];

vector<vector<int>> a[N];
vector<int> v(2, 0);

int interval_intersect(vector<vector<int>>& ans, vector<vector<int>>& add) {
    vector<vector<int>> temp;
    int ip = 0, jp = 0;
    while (ip < ans.size() && jp < add.size()) {
        v[0] = max(ans[ip][0], add[jp][0]), v[1] = min(ans[ip][1], add[jp][1]);
        if (v[0] <= v[1]) {
            temp.push_back(v);
        }
        if (ans[ip][1] < add[jp][1]) {
            ip++;
        } else {
            jp++;
        }
    }
    int sum = 0;
    for (int i = 0; i < temp.size(); i++) {
        sum += temp[i][1] - temp[i][0];
    }
    return sum;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        nodes[idx++] = Node();
    }

    for (int i = 0; i < m; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (open[u] == 0) {
            open[u] = t;
        } else {
            v[0] = open[u], v[1] = t;
            a[u].push_back(v);
            open[u] = 0;
        }
    }
    map<long long, int> mp;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (a[u].size() > a[v].size()) {
            swap(u, v);
        }
        queries[i] = make_tuple(v, u, i);
    }
    sort(queries, queries + q);

    int last = -1;
    for (int i = 0; i < q; i++) {
        int u = get<1>(queries[i]), v = get<0>(queries[i]), cur = get<2>(queries[i]);
        if (last != v) {
            last = v;
            if (a[v].size() > B) {
                idx = 0;
                nodes[idx++] = Node();
                for (int j = 0; j < a[v].size(); j++) {
                    setUpdate(0, 0, R - 1, a[v][j][0], a[v][j][1] - 1);
                }
            }
        }
        long long ind = (long long)u * N + v;
        auto it = mp.find(ind);
        if (it != mp.end()) {
            ans[cur] = it->second;
            continue;
        }
        int sum = 0;
        if (a[v].size() > B) {
            for (int j = 0; j < a[u].size(); j++) {
                sum += query(0, 0, R - 1, a[u][j][0], a[u][j][1] - 1);
            }
        } else {
            sum = interval_intersect(a[u], a[v]);
        }
        mp[ind] = sum;
        ans[cur] = sum;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
