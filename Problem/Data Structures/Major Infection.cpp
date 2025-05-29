//https://www.codechef.com/problems/INFECTMAJ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    int lazy;
    int val;
    Node() {
        lazy = N;
        val = N;
    }
    Node(int x) : lazy(N), val(x) {}
};

int a[N];
int lf[N];
int rt[N];
int ans[N];
Node segtree[4 * N];

void compose(int parent, int child) {
    if (segtree[parent].lazy != N) {
        segtree[child].lazy = segtree[parent].lazy;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy != N) {
        segtree[node].val = segtree[node].lazy;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = N;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = Node();
}

void dfs(int l, int r, int node) {
    if (l > r) {
        return;
    }
    apply(node, l, r);
    if (l == r) {
        ans[l] = segtree[node].val;
        return;
    }
    int mid = (l + r) / 2;
    dfs(l, mid, node * 2 + 1);
    dfs(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[st.top()] >= a[i]) {
                st.pop();
            }
            if (st.empty()) {
                rt[i] = n - 1;
            } else {
                rt[i] = st.top() - 1;
            }
            st.push(i);
        }
        build(0, n - 1, 0);
        priority_queue<pair<int, int>> sta;
        sta.push(make_pair(a[0], 0));
        for (int i = 1; i < n;) {
            if (a[i - 1] == a[i]) {
                int mn = i;
                while (sta.size() && sta.top().first > a[i]) {
                    setUpdate(0, 0, n - 1, sta.top().second, rt[i], a[i]);
                    mn = min(mn, sta.top().second);
                    sta.pop();
                }
                setUpdate(0, 0, n - 1, i, rt[i], a[i]);
                sta.push(make_pair(a[i], mn));
                i = rt[i] + 1;
            } else if (i > 1 && a[i - 2] == a[i]) {
                int mn = i;
                int b = 0;
                while (sta.size() && sta.top().first > a[i]) {
                    setUpdate(0, 0, n - 1, sta.top().second, rt[i], a[i]);
                    mn = min(mn, sta.top().second);
                    sta.pop();
                    b = 1;
                }
                sta.push(make_pair(a[i], mn));
                if (i != n - 1 && a[i] == a[i + 1]) {
                    setUpdate(0, 0, n - 1, i, rt[i], a[i]);
                    i = rt[i] + 1;
                } else if (b) {
                    i = rt[i] + 1;
                } else {
                    i = i + 1;
                }
            } else {
                sta.push(make_pair(a[i], i));
                i++;
            }
        }
        dfs(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
