//https://codeforces.com/contest/717/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50000;

vector<int> adj[N];
vector<int> lst[N];

mt19937 gene(3);

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            t = max(t, x);
            x--;
            lst[i].push_back(x);
        }
    }
    vector<int> f(t, 0);
    vector<int> team(n, 0);
    for (int it = 0; it < 100; it++) {
        for (int i = 0; i < t; i++) {
            f[i] = gene() % 2;
        }
        for (int i = 0; i < n; i++) {
            int sz = lst[i].size();
            team[i] = lst[i][gene() % sz];
        }
        int ct = 0;
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                if (i < j && f[team[i]] != f[team[j]]) {
                    ct++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int nei[2] = {};
            for (int j : adj[i]) {
                nei[f[team[j]]]++;
            }
            int col = f[team[i]];
            if (nei[col] > nei[col ^ 1]) {
                for (int j : lst[i]) {
                    if (f[j] != col) {
                        team[i] = j;
                        ct += nei[col] - nei[col ^ 1];
                        break;
                    }
                }
            }
        }
        if (ct >= (m + 1) / 2) {
            for (int i = 0; i < n; i++) {
                cout << team[i] + 1 << " ";
            }
            cout << endl;
            for (int i = 0; i < t; i++) {
                cout << f[i] + 1 << " ";
            }
            return 0;
        }
    }

    return 0;
}
