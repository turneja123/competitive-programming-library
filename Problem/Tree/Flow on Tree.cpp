//https://www.spoj.com/problems/PRJAN15E/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int parent[N];
int sz[N];

long long ans = 0;

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return dsu_find(parent[a]);
}

void dsu_unite(int a, int b, int wt) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    ans += (long long)wt * sz[a] * sz[b];
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges.push_back(make_tuple(-wt, u, v));
        }
        sort(edges.begin(), edges.end());
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (auto [wt, u, v] : edges) {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                dsu_unite(a, b, -wt);
            }
        }
        cout << ans * 2 << endl;
        ans = 0;
    }

    return 0;
}
