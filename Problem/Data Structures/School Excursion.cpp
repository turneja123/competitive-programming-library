//https://cses.fi/problemset/task/1706/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

bitset<N> b;

int parent[N];
int sz[N];
bool seen[N];

int dsu_find(int a) {
    while (parent[a] != a) {
        a = parent[a];
    }
    return a;
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
	for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_unite(a, b);
        }
	}
	vector<int> wt;
	for (int i = 0; i < n; i++) {
        int a = dsu_find(i);
        if (!seen[a]) {
            wt.push_back(sz[a]);
            seen[a] = true;
        }
	}
    b.set(0);
    for (int i = 0; i < wt.size(); i++) {
        b |= (b << wt[i]);
    }
    for (int i = 1; i <= n; i++) {
        cout << b[i];
    }


	return 0;
}
