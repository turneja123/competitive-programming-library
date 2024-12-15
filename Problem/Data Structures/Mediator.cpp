//https://atcoder.jp/contests/abc350/tasks/abc350_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

int parent[N];
int sz[N];
int time_changed[N];

set<int> adj[N];
vector<pair<int, int>> queries;

int dsu_find(int a, int time){
	if (parent[a] == a || time_changed[a] > time) {
		return a;
	}
	return dsu_find(parent[a], time);
}

void dsu_unite(int a, int b, int time){
	a = dsu_find(a, time);
	b = dsu_find(b, time);
	if (a == b) {
		return;
	}
	if (sz[a] > sz[b]) {
		swap(a, b);
	}
	parent[a] = b;
	time_changed[a] = time;
	sz[b] += sz[a];
	return;
}

int main() {
    IOS;
    int n, q, t = 0, last = 0;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < q; i++) {
        int c, u, v;
        cin >> c >> u >> v;
        c = 1 + ((long long)c * (1 + last) % M) % 2;
        u = 1 + ((long long)u * (1 + last) % M) % n;
        v = 1 + ((long long)v * (1 + last) % M) % n;
        if (c == 1) {
            u--, v--;
            dsu_unite(u, v, t++);
            queries.push_back(make_pair(u, v));
            adj[u].insert(v);
            adj[v].insert(u);
        } else {
            u--, v--;
            int l = 0, r = t - 1, tim = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (dsu_find(u, mid) == dsu_find(v, mid)) {
                    tim = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (tim == -1) {
                cout << 0 << endl;
                last = 0;
                continue;
            }
            auto [x, y] = queries[tim];
            if (u == x) {
                if (adj[y].find(v) != adj[y].end()) {
                    last = y + 1;
                } else {
                    last = 0;
                }
            } else if (v == x) {
                if (adj[y].find(u) != adj[y].end()) {
                    last = y + 1;
                } else {
                    last = 0;
                }
            } else if (u == y) {
                if (adj[x].find(v) != adj[x].end()) {
                    last = x + 1;
                } else {
                    last = 0;
                }
            } else if (v == y) {
                if (adj[x].find(u) != adj[x].end()) {
                    last = x + 1;
                } else {
                    last = 0;
                }
            } else {
                last = 0;
            }
            cout << last << endl;
        }
    }

    return 0;
}
