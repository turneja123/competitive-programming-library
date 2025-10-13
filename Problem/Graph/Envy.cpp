//https://codeforces.com/contest/891/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int parent[N];
int sz[N];
string ans[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return dsu_find(parent[u]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

tuple<int, int, int> ed[N];
vector<pair<int, vector<int>>> process[N];
vector<pair<int, int>> all[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        ed[i] = {wt, u, v};
        all[wt].push_back({u, v});
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> inds;
        for (int j = 0; j < k; j++) {
            int ind;
            cin >> ind;
            ind--;
            inds.push_back(ind);
        }
        sort(inds.begin(), inds.end(), [](int a, int b) {
            return get<0>(ed[a]) < get<0>(ed[b]);
        });
        ans[i] = "YES";
        vector<int> st{inds[0]};
        for (int j = 1; j < k; j++) {
            if (get<0>(ed[inds[j]]) != get<0>(ed[st.back()])) {
                process[get<0>(ed[st.back()])].push_back({i, st});
                st.clear();
            }
            st.push_back(inds[j]);
        }
        process[get<0>(ed[st.back()])].push_back({i, st});
    }
    vector<tuple<int, int, int, int>> restore;
    for (int i = 0; i < N; i++) {
        for (auto [j, v] : process[i]) {
            for (int k : v) {
                auto [_, u, v] = ed[k];
                u = dsu_find(u), v = dsu_find(v);
                if (u == v) {
                    ans[j] = "NO";
                } else {
                    restore.push_back(make_tuple(u, sz[u], v, sz[v]));
                    dsu_unite(u, v);
                }
            }
            while (restore.size()) {
                auto [u, szu, v, szv] = restore.back();
                parent[u] = u;
                parent[v] = v;
                sz[u] = szu;
                sz[v] = szv;
                restore.pop_back();
            }
        }
        for (auto [u, v] : all[i]) {
            u = dsu_find(u), v = dsu_find(v);
            if (u != v) {
                dsu_unite(u, v);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
