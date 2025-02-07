//https://cses.fi/problemset/task/1692
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> ans;

int in_deg[N];
int out_deg[N];
string val[N];

void dfs(int u) {
    while (adj[u].size()) {
        int v = adj[u].back();
        adj[u].pop_back();
        dfs(v);
    }
    ans.push_back(u);
    return;
}

int main() {
	IOS;
	int n, m = 0;
	cin >> n;
	if (n == 1) {
        cout << "10";
        return 0;
	}
	map<string, int> mp;
	for (int i = 0; i < 1 << n; i++) {
        string s = "";
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (c) {
                s += '1';
            } else {
                s += '0';
            }
        }
        string a = s.substr(0, n - 1), b = s.substr(1, n - 1);
        int x, y;
        if (mp.find(a) == mp.end()) {
            mp[a] = m;
            x = m;
            val[m] = a;
            m++;
        } else {
            x = mp[a];
        }
        if (mp.find(b) == mp.end()) {
            mp[b] = m;
            y = m;
            val[m] = b;
            m++;
        } else {
            y = mp[b];
        }
        adj[x].push_back(y);
        out_deg[x]++;
        in_deg[y]++;

	}
	int st = -1, en = -1;

	for (int i = 0; i < m; i++) {
        if (out_deg[i] == in_deg[i] + 1) {
            st = i;
        } else if (out_deg[i] == in_deg[i] - 1) {
            en = i;
        }
	}
	if (st == -1) {
        st = 0;
	}
	dfs(st);
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) {
        string a = val[ans[i]];
        if (i == 0) {
            cout << a;
        } else {
            cout << a[n - 2];
        }
	}
	return 0;
}
