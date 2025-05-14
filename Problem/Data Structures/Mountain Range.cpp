//https://cses.fi/problemset/task/3314/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int l[N];
int r[N];

vector<int> pos[N];

int segtree[4 * N];

void compose(int parent, int child) {
    segtree[child] = max(segtree[child], segtree[parent]);
}

void apply(int node, int l, int r) {
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node] = max(segtree[node], val);
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
}


int get(int l, int r, int node, int ind) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return (ind <= mid ? get(l, mid, 2 * node + 1, ind) : get(mid + 1, r, 2 * node + 2, ind));
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr.push_back(make_pair(a[i], i));
    }
    int last = -1, m = -1;
    sort(compr.begin(), compr.end());
    for (int i = 0; i < n; i++) {
        if (compr[i].first != last) {
            last = compr[i].first;
            m++;
        }
        a[compr[i].second] = m;
        pos[m].push_back(compr[i].second);
    }
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.empty()) {
            l[i] = 0;
        } else {
            l[i] = st.top() + 1;
        }
        st.push(i);
    }
    while (st.size()) {
        st.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (st.empty()) {
            r[i] = n - 1;
        } else {
            r[i] = st.top() - 1;
        }
        st.push(i);
    }
    int ans = 0;
    for (int j = m; j >= 0; j--) {
        for (int i : pos[j]) {
            int cur = 1 + get(0, n - 1, 0, i);
            ans = max(ans, cur);
            setUpdate(0, 0, n - 1, l[i], r[i], cur);
        }
    }
    cout << ans;

    return 0;
}
