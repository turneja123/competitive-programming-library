//solution for http://usaco.org/index.php?page=viewproblem2&cpid=1086
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int a[N];
int sol[N];
bool vis[N];

list <int> adj[N];
set <int> st[N];
vector <int> v;

void dfs(int u) {
    vis[u] = true;
    v.push_back(u);
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it);
        }
    }
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        st[i].insert(i);
        a[i] = i;
    }
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        st[a[x]].insert(y);
        st[a[y]].insert(x);
        swap(a[x], a[y]);
    }
    for (int i = 0; i < n; i++) {
        adj[i].push_back(a[i]);
        adj[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            set <int> uni;
            for (int j = 0; j < v.size(); j++) {
                uni.insert(st[v[j]].begin(), st[v[j]].end());
            }
            for (int j = 0; j < v.size(); j++) {
                sol[v[j]] = uni.size();
            }
            v.erase(v.begin(), v.end());
        }
        cout << sol[i] << endl;
    }
    return 0;
}
