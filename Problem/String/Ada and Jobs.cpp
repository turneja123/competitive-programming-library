//https://www.spoj.com/problems/ADAJOBS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 2e6 + 5;

struct Node {
    int val;
    vector<int> go;
    vector<int> adj;
    Node() : val(MAX), go(vector<int>(26, -1)), adj() {}
};

Node nodes[MAX];
int fail[MAX];
int ans[MAX];
int idx = 0;

void add(int node, int i, int j, string &s) {
    if (i == s.size()) {
        nodes[node].val = min(nodes[node].val, j);
        return;
    }
    int c = s[i] - 'a';
    if (nodes[node].go[c] == -1) {
        nodes[node].go[c] = idx;
        nodes[idx++] = Node();
    }
    add(nodes[node].go[c], i + 1, j, s);

    return;
}

void build() {
    queue<int> q;
    fail[0] = 0;
    for (int i = 0; i < 26; i++) {
        if (nodes[0].go[i] != -1) {
            fail[nodes[0].go[i]] = 0;
            q.push(nodes[0].go[i]);
        } else {
            nodes[0].go[i] = 0;
        }
    }
    while (q.size()) {
        int node = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (nodes[node].go[i] != -1) {
                fail[nodes[node].go[i]] = nodes[fail[node]].go[i];
                q.push(nodes[node].go[i]);
            } else {
                nodes[node].go[i] = nodes[fail[node]].go[i];
            }
        }
    }
    for (int i = 1; i < idx; i++) {
        nodes[fail[i]].adj.push_back(i);
    }
    return;
}

int calc(string &s) {
    int n = s.size();
    int node = 0;
    int best = MAX;
    for (int i = 0; i < n; i++) {
        node = nodes[node].go[s[i] - 'a'];
        if (node != 0) {
            best = min(best, ans[node]);
        }
    }
    return best;
}

void dfs(int node) {
    if (node != 0) {
        ans[node] = min(ans[node], nodes[node].val);
    }
    for (int nx : nodes[node].adj) {
        ans[nx] = min(ans[nx], ans[node]);
        dfs(nx);
    }
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    for (int i = 0; i < MAX; i++) {
        ans[i] = MAX;
    }
    int n;
    cin >> n;
    vector<pair<string, int>> queries(n);
    for (int i = 0; i < n; i++) {
        cin >> queries[i].second >> queries[i].first;
        if (queries[i].second == 0) {
            add(0, 0, i, queries[i].first);
        }
    }
    build();
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (queries[i].second == 1) {
            int cur = calc(queries[i].first);
            if (cur < i) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
