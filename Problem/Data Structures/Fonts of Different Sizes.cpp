//https://ocpc2026w.eolymp.space/en/compete/7ds15ifh194hve0pf1tgf05pqs/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll INF = 1e18;
const int K = 20;

int table[K][N];
int a[N];
ll dp[N];

struct Node {
    bool setValid;
    ll setVal;
    ll sum;
    Node() {
        setValid = 0, setVal = 0, sum = INF;
    }
    Node(ll x) : setValid(0), setVal(0), sum(x) {}
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = min(left.sum, right.sum);
    return node;
}

void compose(int parent, int child) {
    if (segtree[parent].setValid) {
        segtree[child].setValid = 1;
        segtree[child].setVal = segtree[parent].setVal;
    }
}

void apply(int node, int l, int r) {
    if (!segtree[node].setValid) {
        return;
    }
    segtree[node].sum = segtree[node].setVal;

    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setValid = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r || lq > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setValid = true;
        segtree[node].setVal = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return min(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(INF);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    int n; ll h;
    cin >> n >> h;
    ll r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        r += a[i];
    }
    build(n);
    ll l = query(1, n), ans = INF;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll cur = 0;

        stack<pair<int, int>> st;
        build(0, n, 0);
        setUpdate(0, 0, n, 0, 0, 0);
        dp[0] = 0;

        for (int l = 0, i = 1; i <= n; i++) {
            cur += a[i];
            int mov = 0;
            while (cur > mid) {
                cur -= a[l + 1];
                l++;
                mov = 1;
            }
            if (mov) {
                setUpdate(0, 0, n, l, l, query(l + 1, i) + dp[l]);
            }
            while (st.size() && st.top().first <= a[i]) {
                st.pop();
            }

            int last = (st.empty() ? -1 : st.top().second + 1);
            last = max(last, l + 1);

            setUpdate(0, 0, n, last, i, INF);
            setUpdate(0, 0, n, last - 1, last - 1, dp[last - 1] + a[i]);

            st.push({a[i], i});

            dp[i] = getSum(0, n, l, i - 1, 0);
        }
        if (dp[n] <= h) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;



    return 0;
}
