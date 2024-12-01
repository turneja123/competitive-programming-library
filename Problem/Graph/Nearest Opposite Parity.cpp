//https://codeforces.com/contest/1272/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

vector<int> adj[N];
int dist[N];
int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dist[i] = N;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        int l = i - a[i], r = i + a[i];
        if ((l >= 0 && a[l] % 2 != a[i] % 2) || (r < n && a[r] % 2 != a[i] % 2)) {
            dist[i] = 1;
            q.push(i);
        }
        if (l >= 0) {
            adj[l].push_back(i);
        }
        if (r < n) {
            adj[r].push_back(i);
        }
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == N) {
            dist[i] = -1;
        }
        cout << dist[i] << " ";
    }


    return 0;
}
