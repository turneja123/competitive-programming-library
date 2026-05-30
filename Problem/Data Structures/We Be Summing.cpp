//https://codeforces.com/contest/2064/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int l_less[N], l_greater[N];
int r_less[N], r_greater[N];

int a[N];
vector<int> pos[N];

vector<pair<int, int>> add[N], rem[N];

struct Node {
    int lazy;
    int ct;
    int mn;
    Node() {
        lazy = 0;
    }
    Node(int x) {
        lazy = 0;
        ct = 1;
        mn = x;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mn = min(left.mn, right.mn);
    node.ct = (left.mn == node.mn ? left.ct : 0) + (right.mn == node.mn ? right.ct : 0);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].mn += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node node = Node(INF);
        return node;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(0);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (st.size() && a[st.top()] <= a[i]) {
                st.pop();
            }
            if (st.empty()) {
                l_greater[i] = -1;
            } else {
                l_greater[i] = st.top();
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }

        for (int i = 0; i < n; i++) {
            while (st.size() && a[st.top()] >= a[i]) {
                st.pop();
            }
            if (st.empty()) {
                l_less[i] = -1;
            } else {
                l_less[i] = st.top();
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }

        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[st.top()] <= a[i]) {
                st.pop();
            }
            if (st.empty()) {
                r_greater[i] = n;
            } else {
                r_greater[i] = st.top();
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }

        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[st.top()] >= a[i]) {
                st.pop();
            }
            if (st.empty()) {
                r_less[i] = n;
            } else {
                r_less[i] = st.top();
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }

        for (int i = 0; i < n; i++) {
            int x = k - a[i];
            if (x <= 0 || x > n) {
                continue;
            }

            auto it2 = upper_bound(pos[a[i]].begin(), pos[a[i]].end(), i);
            int nx = (it2 == pos[a[i]].end() ? n : *it2);

            int st = i;
            while (1) {
                auto it = upper_bound(pos[x].begin(), pos[x].end(), st);
                if (it == pos[x].end()) {
                    break;
                }

                int j = *it;
                if (nx < r_less[i] && j > nx) {
                    break;
                }
                if (r_less[i] <= l_greater[j]) {
                    break;
                }

                int l = l_less[i] + 1, r = r_greater[j] - 1;

                add[l].push_back({j, r});
                rem[i + 1].push_back({j, r});

                st = r_greater[j];
            }
        }

        ll ans = 0;
        build(0, n - 1, 0);

        for (int i = 0; i < n; i++) {
            for (auto [l, r] : add[i]) {
                incUpdate(0, 0, n - 1, l, r, 1);
            }
            for (auto [l, r] : rem[i]) {
                incUpdate(0, 0, n - 1, l, r, -1);
            }
            Node node = getSum(0, n - 1, i, n - 1, 0);
            ans += n - i - (node.mn == 0 ? node.ct : 0);

        }
        cout << ans << endl;


        for (int i = 0; i <= n; i++) {
            add[i].clear();
            rem[i].clear();
            pos[i].clear();
        }
    }
    return 0;
}
