//https://codeforces.com/contest/2007/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int ct[N];
vector<int> st;
vector<int> belongs[N];

void dfs(int u, int p) {
    if (u != 0) {
        st.push_back(u);
    }
    while (st.size()) {
        ct[u]++;
        belongs[st.back()].push_back(u);
        st.pop_back();
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    if (u != 0) {
        st.push_back(u);
    } else {
        while (st.size()) {
            ct[u]++;
            belongs[st.back()].push_back(u);
            st.pop_back();
        }
    }
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long w;
        cin >> n >> w;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        dfs(0, 0);
        long long free = w, add = 0; int ct_free = n;
        for (int i = 0; i < n - 1; i++) {
            int u; long long x;
            cin >> u >> x;
            u--;
            free -= x;
            add += 2 * x;
            for (int v : belongs[u]) {
                ct[v]--;
                if (ct[v] == 0) {
                    ct_free--;
                }
            }
            cout << free * ct_free + add << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            belongs[i].clear();
            ct[i] = 0;
        }
    }
    return 0;
}
