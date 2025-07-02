//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int K = 20;
const int MAX = 1e7;

mt19937 gen(3);

struct Node {
    vector<int> t;
    int left;
    int right;
    Node() : left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int get(int node, int l, int r) {
    if (node == -1 || nodes[node].t.size() == 0) {
        return 0;
    }
    int R = upper_bound(nodes[node].t.begin(), nodes[node].t.end(), r) - nodes[node].t.begin();
    int L = lower_bound(nodes[node].t.begin(), nodes[node].t.end(), l) - nodes[node].t.begin();
    return R - L;
}

int query_trie(int node, int d, int val, int need, int l, int r) {
    if (node == -1 || d == -1) {
        return 0;
    }
    int ca = need & (1 << d);
    int cb = val & (1 << d);
    int add = 0;
    if (ca == 0 && cb == 0) {
        add += get(nodes[node].right, l, r);
        return add + query_trie(nodes[node].left, d - 1, val, need, l, r);
    } else if (ca == 0 && cb != 0) {
        add += get(nodes[node].left, l, r);
        return add + query_trie(nodes[node].right, d - 1, val, need, l, r);
    } else if (ca != 0 && cb == 0) {
        return query_trie(nodes[node].right, d - 1, val, need, l, r);
    } else {
        return query_trie(nodes[node].left, d - 1, val, need, l, r);
    }
}

void add(int node, int d, int val, int i) {
    nodes[node].t.push_back(i);
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val, i);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val, i);
        return;
    }
}

int table_mx[K][N];
int mx[K][N];
int a[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] > table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mx[k][l] > table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }

    return b;
}

long long calc(int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = query(l, r);
    long long ans = 0;
    if (mid - l + 1 <= r - mid + 1) {
        for (int i = l; i <= mid; i++) {
            ans += query_trie(0, K - 1, a[i], a[mid], mid, r);
        }
    } else {
        for (int i = mid; i <= r; i++) {
            ans += query_trie(0, K - 1, a[i], a[mid], l, mid);
        }
    }
    ans += calc(l, mid - 1) + calc(mid + 1, r);
    return ans;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        //a[i] = gen() % (1000000);
        add(0, K - 1, a[i], i);
    }
    build(n);
    for (int i = 0; i < idx; i++) {
        if (nodes[i].t.size()) {
            sort(nodes[i].t.begin(), nodes[i].t.end());
        }
    }
    cout << calc(0, n - 1);

    return 0;
}
