//https://codeforces.com/contest/575/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50005;

int n; ll M;

ll s[N];

struct Node {
    int sentinel;
    ll dp[2][2];

    Node() {
        sentinel = 1;
        dp[0][0] = 0, dp[0][1] = 0;
        dp[1][0] = 0, dp[1][1] = 0;
    }
    Node(ll x, ll y) {
        sentinel = 0;
        dp[0][0] = 0, dp[0][1] = x;
        dp[1][0] = 1, dp[1][1] = y;
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
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                node.dp[i][j] = (node.dp[i][j] + left.dp[i][k] * right.dp[k][j]) % M;
            }
        }
    }

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

void update(int l, int r, int ind, int d, int s, int node) {
    if (l == r) {
        segtree[node] = Node(d, s);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, d, s, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, d, s, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(s[l], s[(l + 1) % n]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

vector<ll> mul_vec(vector<ll> v, Node node) {
    vector<ll> ans(2, 0);
    ans[0] = (v[0] * node.dp[0][0] + v[1] * node.dp[1][0]) % M;
    ans[1] = (v[0] * node.dp[0][1] + v[1] * node.dp[1][1]) % M;
    return ans;
}


Node modPow(Node a, ll k) {
    Node id;
    id.sentinel = 0;
    id.dp[0][0] = 1, id.dp[1][1] = 1;
    while (k > 0) {
        if (k % 2 == 1) {
            id = combine(id, a);
        }
        a = combine(a, a);
        k /= 2;
    }
    return id;
}

vector<ll> calc(vector<ll> ans, ll l, ll r) {
    if (l > r) {
        return ans;
    }
    ll id_l = l / n, id_r = r / n;
    if (id_l == id_r) {
        ans = mul_vec(ans, query(0, n - 1, l % n, r % n, 0));
    } else {
        ans = mul_vec(ans, query(0, n - 1, l % n, n - 1, 0));
        ans = mul_vec(ans, modPow(query(0, n - 1, 0, n - 1, 0), id_r - id_l - 1));
        ans = mul_vec(ans, query(0, n - 1, 0, r % n, 0));
    }
    return ans;
}

int main() {
    IOS;
    ll k;
    cin >> k >> M;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    if (n == 1) {
        s[1] = s[0], s[2] = s[0], s[3] = s[0];
        n = 4;
    }
    if (n == 2) {
        s[2] = s[0], s[3] = s[1];
        n = 4;
    }
    if (n == 3) {
        s[3] = s[0], s[4] = s[1], s[5] = s[2];
        n = 6;
    }
    int m;
    cin >> m;
    vector<pair<ll, int>> v;
    for (int i = 0; i < m; i++) {
        ll j; int s;
        cin >> j >> s;
        v.push_back({j, s});
    }
    sort(v.begin(), v.end());
    if (k == 0) {
        cout << 0;
        return 0;
    }
    if (k == 1) {
        cout << 1 % M;
        return 0;
    }
    if (v.back().first < k) {
        v.push_back({k, 0});
    }
    build(0, n - 1, 0);
    ll j = 0;
    int i = 0;
    vector<ll> ans{0, 1};
    while (j <= k - 2) {
        auto [ind, val] = v[i];
        ll z = min(k - 2, ind - 2);

        ans = calc(ans, j, z);
        j = z + 1;
        if (j > k - 2) {
            break;
        }
        ll s_prev;
        if (i == 0 || ind - v[i - 1].first > 1) {
            s_prev = s[(ind % n - 1 + n) % n];
        } else {
            s_prev = v[i - 1].second;
        }

        ll s_cur = val;
        Node node = Node(s_prev, s_cur);
        ans = mul_vec(ans, node);

        j++;
        i++;
        while (1) {
            s_prev = s_cur;
            if (j > k - 2) {
                break;
            }
            if (v[i].first - v[i - 1].first == 1) {
                s_cur = v[i].second;
                Node node = Node(s_prev, s_cur);
                ans = mul_vec(ans, node);
                i++;
                j++;

            } else {
                ll ind = v[i - 1].first;
                s_cur = s[(ind + 1) % n];
                Node node = Node(s_prev, s_cur);
                ans = mul_vec(ans, node);
                j++;
                break;
            }
        }

    }
    cout << ans[1];

    return 0;
}
