//https://cses.fi/problemset/task/2103/
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
    vector<int> leaf;
    vector<int> adj;
    Node() : val(0), go(vector<int>(26, -1)), leaf(), adj() {}
};

Node nodes[MAX];
int fail[MAX];
int ans[MAX];
int idx = 0;

void add(int node, int i, int j, string &s) {
    if (i == s.size()) {
        nodes[node].leaf.push_back(j);
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

void calc(string &s) {
    int n = s.size();
    int node = 0;
    for (int i = 0; i < n; i++) {
        node = nodes[node].go[s[i] - 'a'];
        nodes[node].val++;
    }
    return;
}

int dfs(int node) {
    int cur = nodes[node].val;
    for (int nx : nodes[node].adj) {
        cur += dfs(nx);
    }
    for (int j : nodes[node].leaf) {
        ans[j] = cur;
    }
    return cur;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    string s;
    cin >> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        add(0, 0, i, a);
    }
    build();
    calc(s);
    dfs(0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
