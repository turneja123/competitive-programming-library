//https://www.spoj.com/problems/VZLA2019F/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
pair<int, int> edges[N];
pair<int, pair<int, int>> queries[N];
bool f[N];

int parent[N];
int sz[N];
long long sum[N];
long long ans[N];

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
    sum[a] += sum[b];
    parent[b] = a;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];

    }
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int t; cin >> t;
        queries[i].first = t;
        if (t == 1) {
            int e; cin >> e;
            queries[i].second.first = e;
            f[e] = true;
        } else {
            int u, k;
            cin >> u >> k;
            queries[i].second.first = u, queries[i].second.second = a[u];
            a[u] = k;
        }
    }
    multiset<long long> st;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
        sum[i] = a[i];
        st.insert(sum[i]);
    }
    for (int i = 1; i <= m; i++) {
        if (!f[i]) {
            int x = dsu_find(edges[i].first), y = dsu_find(edges[i].second);
            if (x != y) {
                st.erase(st.find(sum[x]));
                st.erase(st.find(sum[y]));
                dsu_unite(x, y);
                st.insert(sum[dsu_find(x)]);
            }
        }
    }
    for (int i = q; i > 0; i--) {
        ans[i] = *st.rbegin();
        int t = queries[i].first;
        if (t == 1) {
            int e = queries[i].second.first;
            int x = dsu_find(edges[e].first), y = dsu_find(edges[e].second);
            if (x != y) {
                st.erase(st.find(sum[x]));
                st.erase(st.find(sum[y]));
                dsu_unite(x, y);
                st.insert(sum[dsu_find(x)]);
            }

        } else {
            int u = queries[i].second.first, k = queries[i].second.second;
            int x = dsu_find(u);
            st.erase(st.find(sum[x]));
            sum[x] += k - a[u];
            a[u] = k;
            st.insert(sum[x]);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
