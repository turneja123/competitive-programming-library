//https://cses.fi/problemset/task/1677/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<pair<int, int>> edges[N];

int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
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
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        mp[make_pair(u, v)] = k;
    }
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        mp[make_pair(u, v)] = i;
    }
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        edges[it->second].push_back(it->first);
    }
    int ans = n;
    vector<int> out;
    for (int i = k; i > 0; i--) {
        for (auto [u, v] : edges[i]) {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                ans--;
                dsu_unite(a, b);
            }
        }
        out.push_back(ans);
    }
    reverse(out.begin(), out.end());
    for (int x : out) {
        cout << x << " ";
    }
    return 0;
}
