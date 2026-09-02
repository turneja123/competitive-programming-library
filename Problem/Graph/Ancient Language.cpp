//https://codeforces.com/contest/1424/problem/M
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 26;

int seen[N];
int deg[N];
set<int> adj[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<tuple<int, int, string>> v;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < k; j++) {
            string s;
            cin >> s;
            for (char c : s) {
                seen[c - 'a'] = 1;
            }
            v.push_back({m, j, s});
        }
    }
    int ok = 1;
    sort(v.begin(), v.end());
    for (int i = 1; i < v.size(); i++) {
        string x = get<2>(v[i - 1]);
        string y = get<2>(v[i]);

        int m = min((int)x.size(), (int)y.size());

        int j = -1;
        for (int i = 0; i < m; i++) {
            if (x[i] != y[i]) {
                j = i;
                break;
            }
        }
        if (j != -1) {
            int u = x[j] - 'a', v = y[j] - 'a';
            if (adj[u].find(v) == adj[u].end()) {
                deg[v]++;
                adj[u].insert(v);
            }
        } else if (y.size() < x.size()) {
            ok = 0;
        }
    }
    int m = 0;
    string ans = "";
    priority_queue<int> pq;
    for (int i = 0; i < 26; i++) {
        if (seen[i]) {
            m++;
            if (deg[i] == 0) {
                pq.push(-i);
            }
        }
    }
    while (pq.size()) {
        int u = -pq.top();
        ans += 'a' + u;
        m--;
        pq.pop();
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                pq.push(-v);
            }
        }
    }
    if (m || !ok) {
        cout << "IMPOSSIBLE";
    } else {
        cout << ans;

    }

    return 0;
}
