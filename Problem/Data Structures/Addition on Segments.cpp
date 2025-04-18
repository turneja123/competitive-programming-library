//https://codeforces.com/contest/981/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;

vector<int> segtree[4 * N];
vector<bitset<N>> restore;

bitset<N> cur;
bitset<N> ans;

void upd(int l, int r, int lq, int rq, int x, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(x);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, x, 2 * node + 1);
    upd(mid + 1, r, lq, rq, x, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct = 0;
    if (segtree[node].size()) {
        ct = 1;
        restore.push_back(cur);
        for (int x : segtree[node]) {
            cur |= cur << x;
            ans |= cur;
        }
    }
    if (l != r) {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    if (ct) {
        cur = restore.back();
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    cur[0] = 1;
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        upd(0, n - 1, l, r, x, 0);
    }
    dfs(0, n - 1, 0);
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            v.push_back(i);
        }
    }
    cout << v.size() << endl;
    for (int i : v) {
        cout << i << " ";
    }

    return 0;
}
