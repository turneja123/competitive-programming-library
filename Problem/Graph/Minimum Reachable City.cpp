//https://atcoder.jp/contests/abc295/tasks/abc295_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int up[N];
int id[N];

int parent[N];
int sz[N];
int val[N];

int dsu_find(int a) {
    while (parent[a] != a) {
        a = parent[a];
    }
    return a;
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    val[a] = min(val[a], val[b]);
    parent[b] = a;
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        val[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        up[i] = p;
        adj[p].push_back(i);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            u = dsu_find(u), v = dsu_find(v);
            vector<int> add;
            while (val[u] > val[v]) {
                add.push_back(u);
                u = dsu_find(up[val[u]]);
            }
            for (int x : add) {
                dsu_unite(x, dsu_find(v));
            }
        } else {
            int u;
            cin >> u;
            u--;
            cout << val[dsu_find(u)] + 1 << endl;
        }
    }

    return 0;
}
