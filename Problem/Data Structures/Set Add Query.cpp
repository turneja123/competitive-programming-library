//https://atcoder.jp/contests/abc347/tasks/abc347_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
long long ans[N];
vector<int> pos[N];

long long segtree[4 * N];

long long query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    set<int> st;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x; x--;
        if (st.find(x) != st.end()) {
            st.erase(x);
        } else {
            st.insert(x);
        }
        a[i] = st.size();
        pos[x].push_back(i);
    }
    build(0, q - 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < pos[i].size(); j += 2) {
            int l = pos[i][j], r = (j == pos[i].size() - 1) ? q - 1 : pos[i][j + 1] - 1;
            ans[i] += query(0, q - 1, l, r, 0);
        }
        cout << ans[i] << " ";
    }
    return 0;
}
