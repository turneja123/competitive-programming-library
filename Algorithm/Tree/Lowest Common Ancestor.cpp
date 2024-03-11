#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll N = 1000005;

list <int> adj[N];
pair<int,int> tour[2 * N - 1];

bool visited[N] = { };
int segtree[4 * N - 2];
int depth[N];
int pre[N];
int ct = 0;

void dfs(int n) {
    visited[n] = true;
    pre[n] = ct;
    tour[ct].first = n;
    tour[ct].second = depth[n];
    ct++;
    for (auto it = adj[n].begin(); it != adj[n].end(); ++it) {
        if (!visited[*it]) {
            depth[*it] = depth[n] + 1;
            dfs(*it);
            tour[ct].first = n;
            tour[ct].second = depth[n];
            ct++;
        }
    }
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mn = 1e9;
    int pos;
    while (l < r) {
        if (l % 2 == 1) {
            if (segtree[l] < mn) {
                mn = segtree[l];
                pos = l;
            }
            l++;
        }
        if (r % 2 == 1) {
            r--;
            if (segtree[r] < mn) {
                mn = segtree[r];
                pos = r;
            }
        }
        r /= 2;
        l /= 2;
    }
    return pos;
}

int index(int pos, int n) {
    int ind = pos;
    while (ind < n) {
        if (segtree[ind * 2] == segtree[ind]) {
            ind = ind * 2;
        } else {
            ind = ind * 2 + 1;
        }
    }
    return ind - n;
}

int main() {
    IOS;
    int n, m;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[0] = 1;
    dfs(0);
    int sz = 2 * n - 1;
    for (int i = 0; i < sz; i++) {
        segtree[sz + i] = tour[i].second;
    }
    for (int i = sz - 1; i >= 1; i--) {
        segtree[i] = min(segtree[2 * i], segtree[2 * i + 1]);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int l = pre[a];
        int r = pre[b];
        if (l > r) {
            swap (l, r);
        }
        cout << tour[index(rmq(l, r + 1, sz), sz)].first + 1 << endl;
    }
    return 0;

}
