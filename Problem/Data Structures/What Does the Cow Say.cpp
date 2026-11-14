//https://codeforces.com/contest/2261/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
int pref[N][2];

struct Node {
    int pref;
    int sum;
    int val;
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(ll x) {
        sentinel = 0;
        pref = x;
        sum = x;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node = Node();
    node.sentinel = 0;
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node((l % 2 == 0 ? a[l] : -a[l]));
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        int m = 0;
        int ct = 0; char cur = '(';
        for (int i = 0; i < n; i++) {
            if (s[i] == cur) {
                ct++;
            } else {
                a[m++] = ct;
                ct = 1;
                cur = s[i];
            }
            if (i == n - 1) {
                a[m++] = ct;
            }
        }
        for (int i = 0; i < m; i++) {
            pref[i][0] = (i == 0 ? 0 : pref[i - 1][0]);
            pref[i][1] = (i == 0 ? 0 : pref[i - 1][1]);
            pref[i][i % 2] += a[i];
        }
        build(0, m - 1, 0);
        int ans = 0;
        for (int i = 2; i < m; i += 2) {
            int l = i, r = m - 1, spl = l;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (pref[mid][1] - pref[i - 1][1] <= k) {
                    l = mid + 1;
                    spl = mid;
                } else {
                    r = mid - 1;
                }
            }
            Node node = query(0, m - 1, i, spl, 0);
            ans = max(ans, node.pref);
        }
        int sum = a[0];
        ans = max(ans, sum + min(k, n / 2 - sum));
        for (int i = 1; i < m; i += 2) {
            if (k >= a[i]) {
                k -= a[i];
                if (i != m - 1) {
                    sum += a[i + 1];
                }
                ans = max(ans, sum + min(k, n / 2 - sum));

            } else {
                break;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
