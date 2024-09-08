//https://www.spoj.com/problems/ADAINDEX/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1e6 + 5;

struct Node {
    int val;
    vector<int> child;
    Node() : val(0), child(vector<int>(26, -1)) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int i, string &s) {
    if (i == s.size()) {
        return nodes[node].val;
    }
    int c = s[i] - 'a';
    if (nodes[node].child[c] == -1) {
        return 0;
    } else {
        return query(nodes[node].child[c], i + 1, s);
    }
}

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
    nodes[node].val -= nodes[nodes[node].child[c]].val;
    add(nodes[node].child[c], i + 1, s);
    nodes[node].val += nodes[nodes[node].child[c]].val;
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(0, 0, s);
    }
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        cout << query(0, 0, s) << endl;
    }

    return 0;
}
