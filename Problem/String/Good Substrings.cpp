//https://codeforces.com/contest/271/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 2e6 + 5;

string a[MAX];

struct Node {
    vector<int> child;
    Node() : child(vector<int>(26, -1)) {}
};

Node nodes[MAX];
int idx = 0, ans = 0;

void query(int node, int i, int n) {
    if (i == n) {
        return;
    }
    for (int j = 0; j < 26; j++) {
        if (nodes[node].child[j] != -1) {
            ans++;
            query(nodes[node].child[j], i + 1, n);
        }
    }
    return;
}

void add(int node, int i, int j, string &s) {
    if (i >= j) {
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

int main() {
    IOS;
    nodes[idx++] = Node();
    string s, can; int k;
    cin >> s >> can >> k;
    int n = s.size(), ct = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n && ct <= k) {
            if (can[s[j] - 'a'] == '0') {
                ct++;
            }
            j++;
        }
        add(0, i, j - (ct > k), s);
        if (can[s[i] - 'a'] == '0') {
            ct--;
        }
    }
    query(0, 0, n);
    cout << ans;

    return 0;
}
