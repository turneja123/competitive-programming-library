//https://dmoj.ca/problem/coci20c3p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1e6 + 5;

struct Node {
    int val[2];
    vector<int> child;
    Node() : child(vector<int>(26, -1)) {
        val[0] = 0, val[1] = 0;
    }
};

Node nodes[MAX];
int idx = 0;

void add(int node, int i, int j, string &s) {
    nodes[node].val[j]++;

    if (i == s.size()) {
        return;
    }
    int c = s[i] - 'a';
    if (nodes[node].child[c] == -1) {
        nodes[node].child[c] = idx;
        nodes[idx++] = Node();

    }
    add(nodes[node].child[c], i + 1, j, s);
    return;
}

int dfs(int node, int f) {
    int ans = f;
    for (int i = 0; i < 26; i++) {
        if (nodes[node].child[i] == -1 || nodes[nodes[node].child[i]].val[f] == 0) {
            continue;
        }
        if (f == 0) {
            ans = max(ans, dfs(nodes[node].child[i], 1));
        } else {
            ans = min(ans, dfs(nodes[node].child[i], 0));
        }
    }
    return ans;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(0, 0, 0, s);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        add(0, 0, 1, s);
    }
    string ans = "Nina";
    if (!dfs(0, 0)) {
        ans = "Emilija";
    }
    cout << ans;
    return 0;
}
