//https://www.spoj.com/problems/HAPPINESS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int lf[N], rt[N];

long long ans[N];
vector<tuple<int, int, int>> operate[N];

class Seg {
public:
    vector<long long> segtree;
    vector<long long> lazy;
    vector<long long> lazy_a;

    Seg() {
        segtree.resize(4 * N, 0);
        lazy.resize(4 * N, 0);
        lazy_a.resize(4 * N, 0);
    }

    void compose(int parent, int child, long long d) {
        lazy_a[child] += lazy_a[parent];
        if (child % 2) {
            lazy[child] += lazy[parent];
        } else {
            lazy[child] += lazy[parent] + lazy_a[parent] * d;
        }
    }

    void apply(int node, int l, int r) {
        segtree[node] += (r - l + 1) * (2 * lazy[node] + (r - l) * lazy_a[node]) / 2;
        if (l != r) {
            compose(node, 2 * node + 1, (l + r) / 2 - l + 1);
            compose(node, 2 * node + 2, (l + r) / 2 - l + 1);
        }
        lazy[node] = 0;
        lazy_a[node] = 0;
    }

    void a_incUpdate(int node, int l, int r, long long val, int lq, int rq) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            lazy[node] += val * (l - lq + 1);
            lazy_a[node] += val;;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        a_incUpdate(node * 2 + 1, l, mid, val, lq, rq);
        a_incUpdate(node * 2 + 2, mid + 1, r, val, lq, rq);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    }

    void incUpdate(int node, int l, int r, long long val, int lq, int rq) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            lazy[node] += val;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, val, lq, rq);
        incUpdate(node * 2 + 2, mid + 1, r, val, lq, rq);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    }

    ll getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node];
        }

        int mid = (l + r) / 2;
        return getSum(l, mid, lq, rq, 2 * node + 1) +
               getSum(mid + 1, r, lq, rq, 2 * node + 2);
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (s.size() && a[s.top()] > a[i]) {
                rt[s.top()] = i - 1;
                s.pop();
            }
            s.push(i);
        }
        while (s.size()) {
            rt[s.top()] = n - 1;
            s.pop();
        }
        for (int i = n - 1; i >= 0; i--) {
            while (s.size() && a[s.top()] > a[i]) {
                lf[s.top()] = i + 1;
                s.pop();
            }
            s.push(i);
        }
        while (s.size()) {
            lf[s.top()] = 0;
            s.pop();
        }
        Seg init;
        for (int i = 0; i < n; i++) {
            int l = i - lf[i] + 1;
            init.a_incUpdate(0, 0, n - 1, l, i, rt[i]);
            init.incUpdate(0, 0, n - 1, (long long)l * (rt[i] - i + 1), rt[i] + 1, n - 1);
            operate[lf[i]].push_back(make_tuple(lf[i], i, rt[i]));
        }
        vector<tuple<int, int, int>> queries;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries.push_back(make_tuple(l, r, i));
        }
        sort(queries.begin(), queries.end());
        Seg ct, diff;
        for (int i = 0, j = 0; i < n; i++) {
            while (j < queries.size() && get<0>(queries[j]) == i) {
                int x = get<1>(queries[j]);
                long long cur = init.getSum(0, n - 1, x, x, 0);
                cur -= (long long)i * ct.getSum(0, n - 1, x, x, 0) - diff.getSum(0, n - 1, x, x, 0);
                ans[get<2>(queries[j])] = cur;
                j++;
            }

            for (auto [l, m, r] : operate[i]) {
                diff.incUpdate(0, 0, n - 1, (long long)i * (r - m + 1), r + 1, n - 1);
                diff.a_incUpdate(0, 0, n - 1, i, m, r);
                ct.incUpdate(0, 0, n - 1, (r - m + 1), r + 1, n - 1);
                ct.a_incUpdate(0, 0, n - 1, 1, m, r);
            }

            diff.incUpdate(0, 0, n - 1, (long long)-lf[i] * (rt[i] - i + 1), rt[i] + 1, n - 1);
            diff.a_incUpdate(0, 0, n - 1, -lf[i], i, rt[i]);
            ct.incUpdate(0, 0, n - 1, -(rt[i] - i + 1), rt[i] + 1, n - 1);
            ct.a_incUpdate(0, 0, n - 1, -1, i, rt[i]);

            int l = i - lf[i] + 1;
            init.a_incUpdate(0, 0, n - 1, -l, i, rt[i]);
            init.incUpdate(0, 0, n - 1, (long long)-l * (rt[i] - i + 1), rt[i] + 1, n - 1);
        }
        cout << "Case " << tt << ":" << endl;
        for (int i = 0; i < queries.size(); i++) {
            cout << ans[i] << endl;
            operate[i].clear();
        }
    }
    return 0;
}
