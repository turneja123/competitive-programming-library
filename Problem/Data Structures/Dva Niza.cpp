//https://arena.petlja.org/sr-Latn-RS/competition/2024-2025-kv1-testiranje#tab_138080
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int K = 30;
const int MAX = 1e7 + 5;

int a[N], b[N];

struct Node {
    int left;
    int right;
    int ind;
    Node(int val) : left(-1), right(-1), ind(val) {}
    Node() : left(-1), right(-1), ind(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int d, int val, int ind, int ans) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].right != -1 && nodes[nodes[node].right].ind >= ind) {
            return query(nodes[node].right, d - 1, val, ind, ans ^ (1 << d));
        } else {
            return query(nodes[node].left, d - 1, val, ind, ans);
        }
    } else {
        if (nodes[node].left != -1 && nodes[nodes[node].left].ind >= ind) {
            return query(nodes[node].left, d - 1, val, ind, ans ^ (1 << d));
        } else {
            return query(nodes[node].right, d - 1, val, ind, ans);
        }
    }
}

void add(int node, int d, int val, int ind) {
    nodes[node].ind = max(nodes[node].ind, ind);
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(ind);
        }
        add(nodes[node].left, d - 1, val, ind);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(ind);
        }
        add(nodes[node].right, d - 1, val, ind);
        return;
    }
}


int main() {
    IOS;
    nodes[idx++] = Node();
    add(0, K, 0, -1);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    map<int, int> mp;
    int sum = 0; long long ans = 0;
    for (int i = 0; i < n; i++) {
        map<int, int> nx;
        nx[b[i]] = i;
        for (auto it = mp.begin(); it != mp.end(); it++) {
            int x = it->first & b[i];
            auto f = nx.find(x);
            if (f == nx.end()) {
                nx[x] = it->second;
            } else {
                nx[x] = min(nx[x], it->second);
            }
        }
        mp = nx;
        sum ^= a[i];
        for (auto it = mp.begin(); it != mp.end(); it++) {
            int q = query(0, K, sum, it->second - 1, 0);
            ans = max(ans, (long long)q * it->first);
        }
        add(0, K, sum, i);
    }
    cout << ans;
    return 0;
}
