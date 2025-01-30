//https://codeforces.com/contest/2063/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int deg[N];
vector<int> adj[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        multiset<int> st;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[v]++;
            deg[u]++;
        }
        for (int i = 0; i < n; i++) {
            st.insert(deg[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int cur = deg[i];
            st.erase(st.find(deg[i]));
            for (int v : adj[i]) {
                st.erase(st.find(deg[v]));
                st.insert(deg[v] - 1);
            }
            ans = max(ans, cur + *st.rbegin() - 1);
            st.insert(deg[i]);
            for (int v : adj[i]) {
                st.insert(deg[v]);
                st.erase(st.find(deg[v] - 1));
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
    }

    return 0;
}
