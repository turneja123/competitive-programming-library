//https://www.spoj.com/problems/TRYCOMP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 5e6 + 5;

struct Node {
    int val;
    int mx;
    vector<int> child;
    Node() : val(0), mx(0), child(vector<int>(26, -1)) {}
};

Node nodes[MAX];
int idx = 0, mx = -1;
string ans = "";

void traverse(int node) {
    if (nodes[node].val == nodes[node].mx) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (nodes[node].child[i] != -1 && nodes[nodes[node].child[i]].mx == nodes[node].mx) {
            ans += 'a' + i;
            traverse(nodes[node].child[i]);
            return;
        }
    }
}

void query(int node, int i, string &s) {
    if (i == s.size()) {
        mx = nodes[node].mx;
        traverse(node);
        return;
    }
    int c = s[i] - 'a';
    if (nodes[node].child[c] == -1) {
        return;
    } else {
        ans += s[i];
        query(nodes[node].child[c], i + 1, s);
    }
}

void add(int node, int i, string &s) {
    if (i == s.size()) {
        nodes[node].val++;
        nodes[node].mx = max(nodes[node].mx, nodes[node].val);
        return;
    }
    int c = s[i] - 'a';
    if (nodes[node].child[c] == -1) {
        nodes[node].child[c] = idx;
        nodes[idx++] = Node();
    }
    add(nodes[node].child[c], i + 1, s);
    nodes[node].mx = max(nodes[node].mx, nodes[nodes[node].child[c]].mx);
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(0, 0, s);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        ans = "";
        mx = -1;
        query(0, 0, s);
        if (mx == -1) {
            cout << -1 << endl;
        } else {
            cout << ans << " " << mx << endl;
        }
    }

    return 0;
}
