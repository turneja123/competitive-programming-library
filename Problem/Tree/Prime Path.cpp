//https://www.hackerearth.com/challenges/competitive/june-circuits-23/algorithm/prime-path-3-7426cdf8/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

list<int> adj[N];
bool composite[N];
long long ans = 0;
long long sz[N];
long long help[N];
int p[N];
int up[N];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                composite[j] = true;
            }
        }
    }
}

void dfs(int v, int prime, int parent, int first) {
    if (!composite[v]) {
        p[v] = prime;
        prime = v;
    } else {
        help[first]++;
    }
    up[v] = first;
    if (prime && v != prime) {
        ans++;
        ans += sz[prime];
    }

    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != parent) {
            if (v == prime) {
                first = *it;
            }
            dfs(*it, prime, v, first);
        }
    }

    if (v == first && composite[v]) {
        sz[prime] += help[v];
    }

    if (!prime) {
        sz[0]++;
    }
    return;
}

void dfs_diff(int v, int prime, int parent) {
    if (!composite[v]) {
        prime = v;
    }
    if (prime) {
        if (p[prime] == 0) {
            ans += sz[0];
        } else if (p[prime] != parent) {
            ans += help[up[prime]];
        }
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != parent) {
            dfs_diff(*it, prime, v);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    sieve(n);
    composite[1] = true;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0, -1, 0);
    dfs_diff(1, 0, -1);
    cout << ans << endl;
    return 0;
}
