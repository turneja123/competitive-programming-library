//https://dmoj.ca/problem/cpc21c1p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

struct Node {
    int mn;
    int pos;
    Node() {
    }
    Node(int x, int i) {
        mn = x;
        pos = i;
    }
};

Node combine(Node &left, Node &right) {
    Node node = Node();
    if (left.mn <= right.mn) {
        node.mn = left.mn;
        node.pos = left.pos;
    } else {
        node.mn = right.mn;
        node.pos = right.pos;
    }
    return node;
}


int val[N];
Node seg[2 * N];


void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = Node(INF, i);
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = combine(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int pos, ll val, int n) {
    pos += n;
    seg[pos] = Node(val, pos - n);
    while (pos > 1) {
        pos /= 2;
        seg[pos] = combine(seg[2 * pos], seg[2 * pos + 1]);
    }
}

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int kth(int k) {
        int pos = 0;
        int pw = 1;
        while ((pw << 1) <= n) {
            pw <<= 1;
        }
        for (int d = pw; d; d >>= 1) {
            if (pos + d <= n && t[pos + d] < k) {
                k -= t[pos + d];
                pos += d;
            }
        }
        return pos + 1;
    }
    int first_left(int r) {
        r++;
        int k = query(r);
        if (k == 0) {
            return -1;
        }
        return kth(k) - 1;
    }
    int first_right(int l) {
        l++;
        int k = query(l - 1) + 1;
        if (k > query(n)) {
            return -1;
        }
        return kth(k) - 1;
    }
};


int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> items;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        items.push_back({x, y, z});
    }
    sort(items.begin(), items.end());
    build(N);
    BIT bit(N);
    bit.upd(0, 1);
    update(0, 0, N);

    int best = get<0>(items.back());
    tuple<int, int, int> ans = {best, 0, 0};
    for (int i = n - 1; i >= 0; i--) {
        auto [x, y, z] = items[i];
        y--;
        int x_cost = (i == 0 ? 0 : get<0>(items[i - 1]));

        int l = bit.first_left(y);
        if (val[l] < z) {
            int r = bit.first_right(y + 1);
            if (r != y + 1) {
                val[y + 1] = val[l];
                bit.upd(y + 1, 1);
                update(y + 1, y + 1 + val[y + 1], N);
            }
            int last = l;
            while (1) {
                last = l;
                val[l] = 0;
                bit.upd(l, -1);
                update(l, INF, N);
                l = bit.first_left(y);
                if (l == -1 || val[l] >= z) {
                    break;
                }
            }
            val[last] = z;
            bit.upd(last, 1);
            update(last, last + val[last], N);
        }
        int p = seg[1].pos;
        if (x_cost + p + val[p] < best) {
            best = x_cost + p + val[p];
            ans = {x_cost, p, val[p]};
        }
    }
    auto [x, y, z] = ans;
    cout << x << " " << y << " " << z;

    return 0;
}
