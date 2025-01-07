//https://atcoder.jp/contests/abc386/tasks/abc386_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int MAX = 2e7 + 5;
const int K = 60;

struct Node {
    int left;
    int right;
    Node() : left(-1), right(-1) {}
};

long long a[N];
Node nodes[MAX];
int idx = 0;

long long query(int node, long long d, long long val, long long ans) {
    if (d == -1) {
        return ans;
    }
    long long c = val & (1ll << d);
    if (c == 0) {
        if (nodes[node].right != -1) {
            return query(nodes[node].right, d - 1, val, ans ^ (1ll << d));
        } else {
            return query(nodes[node].left, d - 1, val, ans);
        }
    } else {
        if (nodes[node].left != -1) {
            return query(nodes[node].left, d - 1, val, ans ^ (1ll << d));
        } else {
            return query(nodes[node].right, d - 1, val, ans);
        }
    }
}

void add(int node, long long d, long long val) {
    if (d < 0) {
        return;
    }
    long long c = val & (1ll << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val);
        return;
    }
}

long long brute = 0;
long long whole = 0;

int n, k;

void calc1(int j, int ct, long long val) {
    if (ct == k) {
        brute = max(brute, val);
        return;
    }
    if (j == n) {
        return;
    }
    if (ct + n - j < k) {
        return;
    }
    for (int i = j; i < n; i++) {
        calc1(i + 1, ct + 1, val ^ a[i]);
    }
    return;
}

void calc2(int j, int ct, long long val) {
    if (ct == k) {
        brute = max(brute, whole ^ val);
        return;
    }

    if (j == n) {
        return;
    }

    if (ct + n - j < k) {
        return;
    }
    for (int i = j; i < n; i++) {
        calc2(i + 1, ct + 1, val ^ a[i]);
    }
    return;
}

int main() {
    IOS;
    nodes[idx++] = Node();
    cin >> n >> k;
    long long mx = 0, pr = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        whole ^= a[i];
        if (i != 0) {
            pr = max(pr, query(0, K - 1, a[i], 0));
        }
        add(0, K - 1, a[i]);
        mx = max(mx, a[i]);
    }
    if (k == n) {
        cout << whole;
        return 0;
    }
    if (k == 1) {
        cout << mx;
        return 0;
    } else if (k == 2) {
        cout << pr;
        return 0;
    }
    if (k <= n / 2) {
        for (int i = 0; i < n; i++) {
            calc1(i + 1, 1, a[i]);
        }
        cout << brute;
    } else {
        k = n - k;
        for (int i = 0; i < n; i++) {
            calc2(i + 1, 1, a[i]);
        }
        cout << brute;
    }
    return 0;
}
