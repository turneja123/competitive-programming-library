//https://www.spoj.com/problems/ILD18ACP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e5 + 5;

bitset<N> b[N];
vector<int> adj[N];

set<pair<int, int>> st;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        auto it = st.find(make_pair(u, v));
        if (it != st.end() || u == v) {
            continue;
        }
        st.insert(make_pair(u, v));
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        bitset<N> mask;
        for (int j : adj[i]) {
            mask.set(j);
        }
        for (int j : adj[i]) {
            b[j] |= mask;
        }
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        b[i].reset(i);
        sum += b[i].count();
    }
    cout << sum / 2;

    return 0;
}
