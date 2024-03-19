//https://dmoj.ca/problem/mnyc16p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long segtree[4 * N];
map<string, int> pos;
int n = 0;

ll query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

long long calc(string s) {
    long long ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += s[i] - 'a' + 1;
    }
    return ans;
}

int main() {
    IOS;
    int q;
    cin >> q;
    while (q--) {
        char c; string s, x, y;
        cin >> c;
        if (c == 'A') {
            cin >> s;
            if (pos.find(s) != pos.end()) {
                cout << "Can't add " << s << endl;
                continue;
            }
            pos[s] = n;
            update(0, N - 1, n, calc(s), 0);
            n++;
        } else if (c == 'S') {
            cin >> x >> y;
            int t = pos[x];
            pos[x] = pos[y];
            pos[y] = t;
            update(0, N - 1, pos[x], calc(x), 0);
            update(0, N - 1, pos[y], calc(y), 0);
        } else if (c == 'M') {
            cin >> x >> y;
            int l = pos[x], r = pos[y];
            if (l > r) {
                swap(l, r);
            }
            cout << query(0, N - 1, l, r, 0) << endl;
        } else if (c == 'R') {
            cin >> x >> y;
            pos[y] = pos[x];
            pos.erase(x);
            update(0, N - 1, pos[y], calc(y), 0);
        } else {
            cout << n << endl;
        }
    }
    return 0;
}
