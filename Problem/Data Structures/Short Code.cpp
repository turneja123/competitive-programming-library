//https://codeforces.com/problemset/problem/965/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1e5 + 5;

struct Node {
    int val;
    vector<int> child;
    Node() : val(0), child(vector<int>(26, -1)) {}
};

Node nodes[MAX];
int idx = 0;

int parent[MAX];
map<int, int> mp[MAX];

void add(int node, int i, string &s) {
    if (i == s.size()) {
        nodes[node].val++;
        return;
    }
    int c = s[i] - 'a';
    if (nodes[node].child[c] == -1) {
        nodes[node].child[c] = idx;
        nodes[idx++] = Node();

    }
    add(nodes[node].child[c], i + 1, s);
    return;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] += it->second;
    }
    return;
}

void dfs(int node, int d) {
    for (int i = 0; i < 26; i++) {
        if (nodes[node].child[i] != -1) {
            dfs(nodes[node].child[i], d + 1);
        }
    }
    if (nodes[node].val != 0) {
        mp[node][d]++;
    }
    for (int i = 0; i < 26; i++) {
        if (nodes[node].child[i] != -1) {
            int a = dsu_find(node), b = dsu_find(nodes[node].child[i]);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(node);
    auto it = mp[a].rbegin();
    if (it->first > d && nodes[node].val == 0 && node != 0) {
        mp[a][it->first]--;
        mp[a][d]++;
        if (mp[a][it->first] == 0) {
            mp[a].erase(it->first);
        }
    }
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(0, 0, s);
    }
    for (int i = 0; i < idx; i++) {
        parent[i] = i;
    }
    dfs(0, 0);
    long long ans = 0;
    int a = dsu_find(0);
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        ans += (long long)it->first * it->second;
    }
    cout << ans;
    return 0;
}
