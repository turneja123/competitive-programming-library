//https://codeforces.com/contest/2257/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e4 + 5;
const ll INF = 1e18;

int x;

struct Node {
    ll sz;
    int sentinel;
    ll dp[10][10];

    Node() {
        sentinel = 1;
    }
    Node(int d, int s) {
        sentinel = 0;
        sz = d;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                dp[i][j] = INF;
            }
        }

        for (int i = 0; i < min(d, 10); i++) {
            for (int j = min(d, 10) - 1; j >= 0; j--) {
                int l = i, r = d - 1 - j;
                int dist = r - l;
                if (dist == 0) {
                    dp[i][j] = 0;
                } else if (dist > 0) {
                    dp[i][j] = (ll)(dist + x - 1) / x * s;
                }
            }
        }

    }
};

const int MAX = 1e6 + 5;

ll pref_best[10][10];
int d[MAX];
int s[MAX];

Node combine(Node left, Node right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node = Node();
    node.sentinel = 0;
    node.sz = left.sz + right.sz;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            node.dp[i][j] = INF;
        }
    }
    for (int r_en = 0; r_en < min(right.sz, 10ll); r_en++) {
        for (int r_st = 0; r_st < min(right.sz, 10ll); r_st++) {
            pref_best[r_en][r_st] = min(right.dp[r_st][r_en], (r_st == 0 ? INF : pref_best[r_en][r_st - 1]));
        }
    }

    for (int l_st = 0; l_st < min(left.sz, 10ll); l_st++) {
        for (int l_en = 0; l_en < min(left.sz, 10ll); l_en++) {
            if (left.dp[l_st][l_en] == INF) {
                continue;
            }
            for (int r_en = 0; r_en < min(right.sz, 10ll); r_en++) {
                if (l_en + right.sz - r_en <= x) {
                    node.dp[l_st][r_en] = min(node.dp[l_st][r_en], left.dp[l_st][l_en]);
                }
                int r_st = min(right.sz - 1, (ll)x - l_en - 1);
                if (r_st >= 0) {
                    node.dp[l_st][r_en] = min(node.dp[l_st][r_en], left.dp[l_st][l_en] + pref_best[r_en][r_st]);
                }
            }
        }
    }

    return node;
}

Node seg[2 * N];
Node nodes[N];


void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = nodes[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = combine(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int pos, int d, int s, int n) {
    pos += n;
    seg[pos] = Node(d, s);
    while (pos > 1) {
        pos /= 2;
        seg[pos] = combine(seg[2 * pos], seg[2 * pos + 1]);
    }
}

Node query(int l, int r, int n) {
    r++;
    l += n;
    r += n;
    Node L, R;
    while (l < r) {
        if (r % 2 == 1) {
            R = combine(seg[--r], R);
        }
        if (l % 2 == 1) {
            L = combine(L, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return combine(L, R);
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q >> x;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<int> id(n);
    vector<int> mark(n);
    vector<tuple<char, int, int>> queries;
    for (int i = 0; i < q; i++) {
        char c; int l, r;
        cin >> c >> l >> r;
        queries.push_back({c, l, r});
        if (c == '?') {
            l--, r--;
            mark[l] = 1;
            mark[r] = 1;
        } else {
            l--;
            mark[l] = 1;
        }
    }
    int j = 0;
    Node cur;
    for (int i = 0; i < n; i++) {
        if (mark[i]) {
            id[i] = j;
            nodes[j] = Node(d[i], s[i]);
            j++;
        } else {
            cur = combine(cur, Node(d[i], s[i]));
            id[i] = j;
            if (i == n - 1 || mark[i + 1]) {
                nodes[j] = cur;
                j++;
                cur = Node();
            }
        }
    }
    build(j);
    for (int i = 0; i < q; i++) {
        auto [c, l, r] = queries[i];
        if (c == '?') {
            l--, r--;
            Node node = query(id[l], id[r], j);
            cout << node.dp[0][0] << endl;
        } else if (c == '1') {
            l--;
            d[l] = r;
            update(id[l], d[l], s[l], j);
        } else {
            l--;
            s[l] = r;
            update(id[l], d[l], s[l], j);
        }
    }

    return 0;
}
