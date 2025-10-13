//https://atcoder.jp/contests/arc176/tasks/arc176_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

int leq[N];
int fix[N];
int freq[N];
int pref[N];
int seen[N];

vector<pair<int, int>> adj[N];

ll ans = 1;

void setfix(int v, int c) {
    if (fix[v] != -1 && fix[v] != c) {
        ans = 0;
    }
    fix[v] = c;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--, c--;
        adj[u].push_back({c, v});
        adj[v].push_back({c, u});
    }
    for (int i = 0; i < n; i++) {
        leq[i] = n;
        fix[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        if (adj[i].empty()) {
            continue;
        }
        sort(adj[i].begin(), adj[i].end());
        int mn = adj[i][0].first;
        for (int j = 0; j < adj[i].size(); j++) {
            auto [c, v] = adj[i][j];
            if (j != 0 && c == adj[i][j - 1].first) {
                setfix(i, c);
            }
            leq[i] = min(leq[i], c);
            leq[v] = min(leq[v], c);
            if (c != mn) {
                setfix(v, c);
            }
        }
    }
    vector<pair<int, int>> process;
    for (int i = 0; i < n; i++) {
        if (fix[i] != -1) {
            if (fix[i] > leq[i]) {
                ans = 0;
            }
            freq[fix[i]]++;
            seen[i] = 1;
        }
        process.push_back({leq[i], i});
    }
    sort(process.begin(), process.end());
    vector<pair<int, int>> pairs;
    for (auto [_, u] : process) {
        if (seen[u]) {
            continue;
        }
        int v = -1;
        for (auto [_, k] : adj[u]) {
            if (!seen[k]) {
                v = k;
            }
        }
        seen[u] = 1;
        if (leq[u] != n && v != -1) {
            freq[leq[u]]++;
        }
        if (v != -1) {
            seen[v] = 1;
            ans = ans * 2 % M;
        }
        pairs.push_back({u, v});
    }

    for (int i = 0; i < n; i++) {
        if (freq[i] > 1) {
            ans = 0;
        }
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + 1 - freq[i];
    }
    int ct = 0;
    for (auto [u, v] : pairs) {
        if (v == -1) {
            ll mul = max(0, pref[min(n - 1, leq[u])] - ct);
            ans = ans * mul % M;
            ct++;
        } else {
            ll mul = max(0, pref[leq[u]] - ct);
            ans = ans * mul % M;
            ct++;
        }
    }

    cout << ans;
    return 0;
}
