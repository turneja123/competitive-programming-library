//https://www.spoj.com/problems/ADABRANC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 3e5 + 5;

pair<int, pair<int, int>> e[N];
pair<int, pair<int, int>> queries[N];

int ans[N];
int parent[N];
int sz[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (sz[a] > sz[b]) {
        swap(a, b);
    }
    parent[a] = b;
    sz[b] += sz[a];
    return;
}

int main(){
	IOS;
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
        sz[i] = 1, parent[i] = i;
	}
	for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        e[i] = make_pair(wt, make_pair(u, v));
	}
	sort(e, e + m);
	for (int i = 0; i < q; i++) {
        int u, wt;
        cin >> u >> wt;
        queries[i] = make_pair(wt, make_pair(u, i));
	}
	sort(queries, queries + q);
	for (int i = q - 1, j = m - 1; i >= 0; i--) {
        int wt = queries[i].first, u = queries[i].second.first, cur = queries[i].second.second;
        while (j >= 0 && wt <= e[j].first) {
            int a = dsu_find(e[j].second.first), b = dsu_find(e[j].second.second);
            if (a != b) {
                dsu_merge(a, b);
            }
            j--;
        }
        ans[cur] = sz[dsu_find(u)];
	}
	for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
	}


	return 0;
}
