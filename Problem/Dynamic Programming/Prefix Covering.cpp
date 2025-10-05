//https://atcoder.jp/contests/arc201/tasks/arc201_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

const int N = 5e5 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int left;
    int right;
    ll sum;
    int ct;
    int exist;
    Node() : left(-1), right(-1), sum(0), ct(0), exist(0) {}
};

ll pw[N];
Node nodes[MAX];
int idx = 0;

void add(int node, string &s, int d) {
    nodes[node].ct++;
    if (d != s.size()) {
        if (s[d] == 'A') {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].left, s, d + 1);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].right, s, d + 1);
        }
    } else {
        nodes[node].exist = 1;
    }
    nodes[node].sum = 0;
    if (nodes[node].left != -1 && nodes[node].right != -1) {
        nodes[node].sum = nodes[nodes[node].left].sum * nodes[nodes[node].right].sum % M;
    }
    if (nodes[node].exist) {
        nodes[node].sum = (nodes[node].sum + pw[nodes[node].ct - 1]) % M;
    }
}

int main() {
    IOS;
    nodes[idx++] = Node();
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        add(0, s, 0);
        cout << nodes[0].sum << endl;

    }
    return 0;
}
