//https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return dsu_find(parent[a]);
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
    int n, q;
    cin >> n >> q;
    int ans = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    vector<tuple<int, int, int, int>> restore;
    vector<int> st;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "persist") {
            st.push_back(restore.size());
        } else if (s == "rollback") {
            while (restore.size() > st.back()) {
                auto [u, su, v, sv] = restore.back();
                parent[u] = u;
                parent[v] = v;
                sz[u] = su;
                sz[v] = sv;
                restore.pop_back();
                ans++;
            }
            st.pop_back();
            cout << ans << endl;
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int x = dsu_find(u), y = dsu_find(v);
            if (x != y) {
                restore.push_back(make_tuple(x, sz[x], y, sz[y]));
                dsu_unite(x, y);
                ans--;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
