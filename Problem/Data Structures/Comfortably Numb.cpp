//https://codeforces.com/contest/1777/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int K = 30;
const int MAX = 1e7;

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

int query_trie(int node, int d, int val, int ans, int lq, int rq) {
    if (d == -1 || node == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].right != -1 && get(nodes[node].right, lq, rq) > 0) {
            return query_trie(nodes[node].right, d - 1, val, ans ^ (1 << d), lq, rq);
        } else {
            return query_trie(nodes[node].left, d - 1, val, ans, lq, rq);
        }
    } else {
        if (nodes[node].left != -1 && get(nodes[node].left, lq, rq) > 0) {
            return query_trie(nodes[node].left, d - 1, val, ans ^ (1 << d), lq, rq);
        } else {
            return query_trie(nodes[node].right, d - 1, val, ans, lq, rq);
        }
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
int pref[N];

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

int calc(int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = query(l, r);
    int ans = 0;
    if (mid - l + 1 <= r - mid + 1) {
        for (int i = l; i <= mid; i++) {
            int val = a[mid] ^ pref[i];
            ans = max(ans, query_trie(0, K - 1, val, 0, mid + 1, r + 1));
        }
    } else {
        for (int i = mid; i <= r; i++) {
            int val = a[mid] ^ pref[i] ^ a[i];
            ans = max(ans, query_trie(0, K - 1, val, 0, l, mid));
        }
    }

    ans = max({ans, calc(l, mid - 1), calc(mid + 1, r)});
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        nodes[idx++] = Node();
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i] = sum;
            add(0, K - 1, sum, i);
            sum ^= a[i];
        }
        add(0, K - 1, sum, n);
        build(n);
        for (int i = 0; i < idx; i++) {
            if (nodes[i].t.size()) {
                sort(nodes[i].t.begin(), nodes[i].t.end());
            }
        }
        cout << calc(0, n - 1) << endl;
        idx = 0;
    }

    return 0;
}
