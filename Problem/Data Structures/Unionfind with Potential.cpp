//https://judge.yosupo.jp/problem/unionfind_with_potential
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 998244353;

int parent[N];
int sz[N];
int wt[N];

pair<int, int> dsu_find(int a) {
    if (parent[a] == a) {
        return {a, 0};
    }
    auto [p, x] = dsu_find(parent[a]);
    parent[a] = p;
    wt[a] = (x + wt[a]) % M;
    return {p, wt[a]};
}

int dsu_unite(int a, int b, int w) {
    //f(a) = f(b) + w
    int pa = dsu_find(a).first;
    int pb = dsu_find(b).first;
    if (pa == pb) {
        return wt[a] == (wt[b] + w) % M;
    }
    if (sz[pa] > sz[pb]) {
        swap(pa, pb);
        swap(a, b);
        w = M - w;
    }
    parent[pa] = pb;
    sz[pb] += sz[pa];
    wt[pa] = ((ll)w - wt[a] + wt[b] + M) % M;
    return 1;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, x;
            cin >> u >> v >> x;
            cout << dsu_unite(u, v, x) << endl;
        } else {
            int u, v;
            cin >> u >> v;
            if (dsu_find(u).first != dsu_find(v).first) {
                cout << -1 << endl;
            } else {
                cout << (wt[u] - wt[v] + M) % M << endl;
            }
        }
    }
    return 0;
}
