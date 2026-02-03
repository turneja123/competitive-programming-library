//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int need[N];
int ans[N];
int vis[N];
vector<pair<int, int>> adj[N];

int ok;

void dfs(int u, int p, int ed, int big) {
    vis[u] = 1;
    for (auto [v, e] : adj[u]) {
        if (!vis[v]) {
            dfs(v, u, e, big);
        }
    }
    if (ed == -1) {
        if (need[u] && !big) {
            ok = 0;
        }
    } else if (need[u]) {
        need[u] ^= 1;
        need[p] ^= 1;
        ans[ed] = 1;
    }
}


int main() {
    IOS;
    int n, m, k;
    cin >> n;
    vector<pair<int, int>> a, b;
    cin >> k;

    int big = 0;
    vector<int> compr;
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r + 1});
        compr.push_back(l);
        compr.push_back(r + 1);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        if (r == n) {
            big = 1;
        }
        b.push_back({l, r + 1});
        compr.push_back(l);
        compr.push_back(r + 1);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    n = compr.size();
    for (int i = 0; i < k; i++) {
        auto [l, r] = a[i];
        l = lower_bound(compr.begin(), compr.end(), l) - compr.begin();
        r = lower_bound(compr.begin(), compr.end(), r) - compr.begin();
        need[l] ^= 1;
        need[r] ^= 1;
    }

    for (int i = 0; i < m; i++) {
        auto [l, r] = b[i];
        l = lower_bound(compr.begin(), compr.end(), l) - compr.begin();
        r = lower_bound(compr.begin(), compr.end(), r) - compr.begin();
        adj[l].push_back({r, i});
        adj[r].push_back({l, i});
    }
    ok = 1;
    dfs(n - 1, n - 1, -1, big);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i, -1, 0);
        }
    }
    if (!ok) {
        cout << "NO";
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < m; i++) {
            cout << ans[i] << " ";
        }
    }




    return 0;
}
