//https://atcoder.jp/contests/dp/tasks/dp_w
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const long long INF = 1e18;


tuple<long long, long long, long long> a[N];
long long segtree[4 * N];
long long lazy[4 * N];

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree[node] += lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = max(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}


long long rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return -INF;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, long long val, int node) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] += val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
        apply(2 * node + 1, l, mid);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
        apply(2 * node + 2, mid + 1, r);
    }
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l == r) {
        segtree[node] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = 0;
}

int main() {
	IOS;
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
        cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);
        get<0>(a[i])--, get<1>(a[i])--;
	}
	sort(a, a + n);

	priority_queue<pair<int, int>> pq;
	long long sum = 0, ans = 0;
	for (int i = 0, j = 0; i < m; i++) {
        while (j < n && get<0>(a[j]) <= i) {
            sum += get<2>(a[j]);
            incUpdate(0, 0, m - 1, get<0>(a[j]), get<1>(a[j]), -get<2>(a[j]));
            pq.push(make_pair(-get<1>(a[j]), j));
            j++;
        }
        while (pq.size() && -pq.top().first < i) {
            int k = pq.top().second;
            incUpdate(0, 0, m - 1, get<0>(a[k]), get<1>(a[k]), get<2>(a[k]));
            sum -= get<2>(a[k]);
            pq.pop();
        }
        long long mx = sum;
        if (i != 0) {
            mx = max(mx, rmq(0, m - 1, 0, i - 1, 0) + sum);
        }
        ans = max(ans, mx);
        update(0, m - 1, i, mx, 0);
	}
    cout << ans;
	return 0;
}
