//https://codeforces.com/contest/1620/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 5e5 + 5;

int mp[N];
int ans[N];
int parent[N];
set<int> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

int dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (int x : st[a]) {
        st[b].insert(x);
    }
    return b;
}

int main(){
	IOS;
	for (int i = 0; i < N; i++) {
        mp[i] = -1;
	}
	int n, j = 0, m = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            if (mp[x] == -1) {
                mp[x] = j;
                parent[j] = j;
                st[j++].insert(m++);
            } else {
                st[mp[x]].insert(m++);
            }
        } else {
            int x, y;
            cin >> x >> y;
            if (x == y) {
                continue;
            }
            if (mp[x] == -1) {
                continue;
            }
            if (mp[y] == -1) {
                mp[y] = mp[x];
                mp[x] = -1;
            } else {
                int a = dsu_find(mp[x]), b = dsu_find(mp[y]);
                mp[y] = dsu_merge(a, b), mp[x] = -1;
            }
        }
	}
	for (int i = 0; i < N; i++) {
        if (mp[i] != -1) {
            for (auto x : st[mp[i]]) {
                ans[x] = i;
            }
        }
	}
	for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
	}

	return 0;
}
