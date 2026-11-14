//https://codeforces.com/gym/105493/problem/E
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> rev[N];
int deg[N];
int id[N];

int main() {
    int n, m;
    cin >> n >> m;
    int u, v;
    cin >> u >> v;
    u--, v--;
    vector<int> ans[2];
    ans[0].push_back(u);
    ans[1].push_back(v);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (rev[i].empty()) {
            continue;
        }
        sort(rev[i].begin(), rev[i].end());
        rev[i].erase(unique(rev[i].begin(), rev[i].end()), rev[i].end());

    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        deg[i] = rev[i].size();
        if (deg[i] == 0) {
            q.push(i);
        }

    }
    vector<int> ord;
    while (q.size()) {
        int u = q.front();
        ord.push_back(u);
        q.pop();
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        id[ord[i]] = i;
    }


    int i = 0;
    while (i < n) {
        if (ord[i] == u || ord[i] == v) {
            i++;
            continue;
        }

        int ct = 0, who = -1;
        for (int j : rev[ord[i]]) {
            if (j == ans[0].back()) {
                ct++;
                who = 0;
            }
            if (j == ans[1].back()) {
                ct++;
                who = 1;
            }
        }
        if (ct == 0) {
            cout << "NO";
            return 0;
        }
        if (ct == 1) {
            ans[who].push_back(ord[i]);
            i++;
            continue;
        }

        int j = i;
        vector<int> path{ord[i]};
        j++;
        while (j < n) {
            int ok = 0;
            for (int x : rev[ord[j]]) {
                if (x == path.back()) {
                    ok = 1;
                }
            }
            if (ok) {
                path.push_back(ord[j]);
                j++;
            } else {
                break;
            }
        }
        if (j == n) {
            for (int u : path) {
                ans[0].push_back(u);
            }
            break;
        }
        who = -1;
        for (int x : rev[ord[j]]) {
            if (x == ans[0].back()) {
                who = 0;
            }
            if (x == ans[1].back()) {
                who = 1;
            }
        }
        if (who != -1) {
            ans[who].push_back(ord[j]);
            for (int x : path) {
                ans[who ^ 1].push_back(x);
            }
            j++;
            i = j;
            continue;
        }
        int spl = -1;
        for (int x : rev[ord[j]]) {
            int ptr = id[x] - id[path[0]];
            if (ptr >= 0 && ptr < path.size()) {
                spl = ptr;
                break;
            }
        }
        if (spl == -1) {
            cout << "NO";
            return 0;
        }
        for (int x : path) {
            ans[0].push_back(x);
        }
        for (int i = 0; i <= spl; i++) {
            ans[1].push_back(path[i]);
        }
        ans[1].push_back(ord[j]);
        j++;
        i = j;
    }
    cout << "YES" << endl;
    cout << ans[0].size() << endl;
    for (int u : ans[0]) {
        cout << u + 1 << " ";
    }
    cout << endl;
    cout << ans[1].size() << endl;
    for (int u : ans[1]) {
        cout << u + 1 << " ";
    }




    return 0;
}
