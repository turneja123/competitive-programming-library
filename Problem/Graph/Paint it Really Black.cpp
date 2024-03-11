//https://dmoj.ca/problem/bbc09c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
int c[N];
list<int> adj[N];

void dfs(int v, int p) {
    cout << v + 1 << " ";
    if (v != 0) {
        c[v]++;
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != p) {
            dfs(*it, v);
            cout << v + 1 << " ";
            c[v]++;
        }
    }
    if (v != 0) {
        if (c[v] % 2 == 0) {
            cout << p + 1 << " " << v + 1 << " ";
            c[p]++, c[v]++;
        }
    } else {
        if (c[0] % 2 == 0) {
            cout << *adj[v].begin() + 1 << " " << 1 << " " << *adj[v].begin() + 1 << " ";
        }
    }
}

int main() {
    IOS;
    int n; bool flag = false;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i] == -1) {
            c[i] = 0;
            flag = true;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (!flag) {
        cout << 1 << endl;
        return 0;
    }
    dfs(0, 0);
    cout << endl;

    return 0;
}
