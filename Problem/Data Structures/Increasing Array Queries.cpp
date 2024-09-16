//https://cses.fi/problemset/task/2416
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long segtree[4 * N];
long long old[4 * N];
long long setVal[4 * N];
bool setValid[4 * N];
int rt[N];

tuple<int, int, int> queries[N];
long long ans[N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node] - old[node];
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, long long val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        old[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    old[node] = old[node * 2 + 1] + old[node * 2 + 2];
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q, greater<tuple<int, int, int>>());
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (s.size() && a[s.top()] < a[i]) {
            rt[s.top()] = i - 1;
            s.pop();
        }
        s.push(i);
    }
    while (s.size()) {
        rt[s.top()] = n - 1;
        s.pop();
    }
    build(0, n - 1, 0);
    for (int i = 0, j = n - 1; i < q; i++) {
        int l = get<0>(queries[i]), r = get<1>(queries[i]);
        while (j >= l) {
            if (j != rt[j]) {
                setUpdate(0, 0, n - 1, j, rt[j], a[j]);
            }
            j--;
        }
        ans[get<2>(queries[i])] = getSum(0, n - 1, l, r, 0);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
