//https://atcoder.jp/contests/arc205/tasks/arc205_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> adj[N];
int sz[N];

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        dfs(v, u);
        sz[u] += sz[v];
    }
}

bool comp(int a, int b) {
    if (sz[a] != sz[b]) {
        return sz[a] > sz[b];
    }
    return a < b;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[p].push_back(i);
        }
        dfs(0, 0);
        for (int i = 0; i < n; i++) {
            if (adj[i].size()) {
                sort(adj[i].begin(), adj[i].end(), comp);
            }
        }
        vector<int> st;
        st.push_back(0);
        int have = 0, ans = 0;
        while (st.size()) {
            int u = st.back();
            st.pop_back();
            if (have) {
                have--;
                ans++;
            }
            if (adj[u].empty()) {
                break;
            }
            int s = 0;
            for (int i = 1; i < adj[u].size(); i++) {
                s += sz[adj[u][i]];
            }
            if (sz[adj[u][0]] > s) {
                have += s;
                st.push_back(adj[u][0]);
            } else {
                have += sz[u] - 1;
            }
        }
        ans += have / 2;
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            sz[i] = 0;
        }
    }


    return 0;
}
