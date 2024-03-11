//https://atcoder.jp/contests/abc343/tasks/abc343_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
map<int, int> seg[4 * N];

void query(int l, int r, int lq, int rq, int node, map<int, int> &mp) {
    if (l > rq || r < lq || l > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        auto it = seg[node].rbegin();
        if (mp.size() < 2 || it->first >= mp.begin()->first) {
            mp[it->first] += it->second;
        }
        while (mp.size() > 2) {
            mp.erase(mp.begin());
        }
        if (seg[node].size() > 1) {
            ++it;
            if (mp.size() < 2 || it->first >= mp.begin()->first) {
                mp[it->first] += it->second;
            }
            while (mp.size() > 2) {
                mp.erase(mp.begin());
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1, mp);
    query(mid + 1, r, lq, rq, 2 * node + 2, mp);
    return;
}

void update(int l, int r, int node, int ind, int val) {
    if (l > ind || r < ind || l > r) {
        return;
    }
    if (l == r) {
        seg[node][val]++;
        seg[node][a[ind]]--;
        if (seg[node][a[ind]] == 0) {
            seg[node].erase(a[ind]);
        }
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, ind, val);
    } else {
        update(mid + 1, r, 2 * node + 2, ind, val);
    }
    seg[node][val]++;
    seg[node][a[ind]]--;
    if (seg[node][a[ind]] == 0) {
        seg[node].erase(a[ind]);
    }
    return;
}

void build(int l, int r, int node) {
    if (l == r) {
        seg[node][a[l]]++;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (auto it = seg[2 * node + 1].begin(); it != seg[2 * node + 1].end(); ++it) {
        seg[node][it->first] += it->second;
    }
    for (auto it = seg[2 * node + 2].begin(); it != seg[2 * node + 2].end(); ++it) {
        seg[node][it->first] += it->second;
    }
    return;

}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            l--;
            update(0, n - 1, 0, l, r);
            a[l] = r;
        } else {
            l--, r--;
            map<int, int> mp;
            query(0, n - 1, l, r, 0, mp);
            if (mp.size() < 2) {
                cout << 0 << endl;
            } else {
                auto it = mp.begin();
                cout << it->second << endl;
            }
        }
    }


    return 0;
}
