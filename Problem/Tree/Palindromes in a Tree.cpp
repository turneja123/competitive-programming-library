//https://codeforces.com/contest/914/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct VeniceSet {
	multiset<pair<int, int>> S;
	long long inc = 0;
	void add(int v, int u) {
		S.insert(make_pair(v - inc, u));
	}
	void updateAll(int v) {
		inc += v;
	}
	pair<long long, int> getMin() {
		return make_pair((long long)(*S.begin()).first + inc, (*S.begin()).second);
	}
	int size() {
		return S.size();
	}
};

vector<int> adj[N];
int parent[N];
int sz[N];
int val[N];
long long lca[N];
long long diff[N];
long long ans[N];
map<int, int> mp[N];
string s;

map<int, VeniceSet> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int u) {
    if (sz[a] > sz[b]) {
        swap(a, b);
    }
    parent[a] = b;
    sz[b] += sz[a];
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        int x = it->first ^ (1 << (s[u] - 'a'));
        auto f = mp[b].find(x);
        if (f != mp[b].end()) {
            lca[u] += (long long)it->second * f->second;
            st[a][it->first].updateAll(f->second);
            st[b][x].updateAll(it->second);
        }
        for (int j = 0; j < 20; j++) {
            auto f = mp[b].find(x ^ (1 << j));
            if (f != mp[b].end()) {
                lca[u] += (long long)it->second * f->second;
                st[a][it->first].updateAll(f->second);
                int vv = x ^ (1 << j);
                st[b][x ^ (1 << j)].updateAll(it->second);
            }
        }
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] += it->second;
    }
    mp[a].clear();
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        for (pair<int, int> u : (it->second).S) {
            st[b][it->first].add(0, u.second);
        }
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            val[v] = val[u] ^ (1 << (s[v] - 'a'));
            dfs(v, u);
        }
    }
    mp[u][val[u]]++;
    st[u][val[u]].add(0, u);
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    return;
}

long long dfs_calc(int u, int p) {
    ans[u] += diff[u];
    for (int v : adj[u]) {
        if (v != p) {
            ans[u] += dfs_calc(v, u);
        }
    }
    ans[u] -= lca[u];
    return ans[u] - lca[u];
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> s;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    val[0] = 1 << (s[0] - 'a');
    dfs(0, 0);
    for (int a = 0; a < n; a++) {
        for (auto it = st[a].begin(); it != st[a].end(); ++it) {
            while ((it->second).S.size()) {
                pair<long long, int> pr = (it->second).getMin();
                diff[pr.second] += pr.first;
                (it->second).S.erase((it->second).S.begin());
            }
        }
    }
    dfs_calc(0, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}
