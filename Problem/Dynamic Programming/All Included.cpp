//https://atcoder.jp/contests/abc419/tasks/abc419_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 105;
const int K = 257;

const ll M = 998244353;

struct Node {
    int val;
    vector<int> go;
    vector<int> adj;
    Node() : val(0), go(vector<int>(26, -1)), adj() {}
};

Node nodes[MAX];
int fail[MAX];
int ans[MAX];
int idx = 0;

int mask[MAX];
ll dp[MAX][MAX][K];

void add(int node, int i, int j, string &s) {
    if (i == s.size()) {
        mask[node] |= 1 << j;
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
        mask[node] |= mask[fail[node]];
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


int main() {
    IOS;
    nodes[idx++] = Node();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        add(0, 0, i, a);
    }
    build();
    dp[0][0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int node = 0; node < idx; node++) {
            for (int j = 0; j < 1 << n; j++) {
                for (int d = 0; d < 26; d++) {
                    int node_nx = nodes[node].go[d];
                    int j_nx = j | mask[node_nx];
                    dp[i + 1][node_nx][j_nx] = (dp[i + 1][node_nx][j_nx] + dp[i][node][j]) % M;
                }
            }
        }
    }
    ll ans = 0;
    for (int node = 0; node < idx; node++) {
        ans = (ans + dp[m][node][(1 << n) - 1]) % M;
    }
    cout << ans;

    return 0;
}
