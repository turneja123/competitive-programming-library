//https://www.codechef.com/problems/GERALD07?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int B = 450;

pair<int, int> edges[N];
vector<tuple<int, int, int>> queries[B];

int parent[N];
int sz[N];
int ans[N];

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
    parent[b] = a;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            edges[i] = make_pair(u, v);
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries[l / B].push_back(make_tuple(r, l, i));
        }
        for (int i = 0; i < B; i++) {
            sort(queries[i].begin(), queries[i].end());
            int comp = n;
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                sz[i] = 1;
            }
            int ptr = (i + 1) * B;
            for (auto [r, l, ind] : queries[i]) {
                while (ptr <= r) {
                    auto [u, v] = edges[ptr];
                    int a = dsu_find(u), b = dsu_find(v);
                    if (a != b) {
                        dsu_unite(a, b);
                        comp--;
                    }
                    ptr++;
                }
                vector<tuple<int, int, int, int>> restore;
                for (int j = l; j <= min(r, (i + 1) * B - 1); j++) {
                    auto [u, v] = edges[j];
                    int a = dsu_find(u), b = dsu_find(v);
                    if (a != b) {
                        restore.push_back(make_tuple(a, sz[a], b, sz[b]));
                        dsu_unite(a, b);
                        comp--;
                    }
                }
                ans[ind] = comp;
                while (restore.size()) {
                    auto [u, su, v, sv] = restore.back();
                    parent[u] = u;
                    parent[v] = v;
                    sz[u] = su;
                    sz[v] = sv;
                    restore.pop_back();
                    comp++;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
        }
        for (int i = 0; i < B; i++) {
            queries[i].clear();
        }
    }
    return 0;
}
