//https://www.spoj.com/problems/BDOI16E/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct VeniceSet {
	set<long long> S;
	long long inc = 0;
	void add(long long v) {
		S.insert(v - inc);
	}
	void remove(long long v) {
		S.erase(S.find(v - inc));
	}
	void updateAll(long long v) {
		inc += v;
	}
	long long getMin() {
		return *S.begin() + inc;
	}
	int size() {
		return S.size();
	}
};

VeniceSet st[N];
vector<pair<int, long long>> adj[N];
int a[N], p[N];
int parent[N];
int ans[N];
long long wt[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].S.begin(); it != st[a].S.end(); ++it) {
        st[b].add(*it + st[a].inc);
    }
    return;
}

void dfs(int u, int p) {
    for (pair<int, long long> pr : adj[u]) {
        int v = pr.first;
        if (v != p) {
            dfs(v, u);
        }
    }

    for (pair<int, long long> pr : adj[u]) {
        int v = pr.first; long long wt = pr.second;
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            st[b].updateAll(wt);
            dsu_merge(a, b);
        }
    }
    int par = dsu_find(u);
    st[par].add(a[u]);
    ans[u] = st[par].size();
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    int root = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        if (p[i] == -1) {
            root = i;
        }
        parent[i] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    for (int i = 0; i < n; i++) {
        if (i == root) {
            continue;
        }
        adj[i].push_back(make_pair(p[i], wt[i]));
        adj[p[i]].push_back(make_pair(i, wt[i]));
    }
    dfs(root, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
