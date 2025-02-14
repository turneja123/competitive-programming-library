//https://atcoder.jp/contests/abc392/tasks/abc392_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

int dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
    return a;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_unite(a, b);
        } else {
            edges.push_back(make_tuple(i, u, v));
        }
    }
    set<int> comps;
    for (int i = 0; i < n; i++) {
        comps.insert(dsu_find(i));
    }
    cout << comps.size() - 1 << endl;
    for (int i = 0; i < edges.size(); i++) {
        if (comps.size() == 1) {
            break;
        }

        auto [j, u, v] = edges[i];
        int a = dsu_find(u);
        auto it = comps.begin();
        if (*it == a) {
            it++;
        }
        int b = *it;

        cout << j + 1 << " " << u + 1 << " " << b + 1 << endl;
        int nw = dsu_unite(a, b);
        if (a != nw) {
            comps.erase(a);
        } else {
            comps.erase(b);
        }
    }

    return 0;
}
