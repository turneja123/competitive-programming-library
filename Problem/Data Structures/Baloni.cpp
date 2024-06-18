//http://algoge.com/problem/sio_2009_3_baloni
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

pair<char, int> query[N];
set<pair<int, int>> st;
map<pair<int, int>, int> pos;

long long segtree[4 * N];
long long segct[4 * N];

int mx = -1;

long long getct(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segct[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return getct(l, mid, lq, rq, 2 * node + 1) + getct(mid + 1, r, lq, rq, 2 * node + 2);
}

void traverse(int l, int r, int node, long long cur, long long sum) {
    if (l == r) {
        if (cur + segtree[node] <= sum) {
            mx = max(mx, r);
        }
        return;
    }
    int mid = (l + r) / 2;
    if (cur + segtree[2 * node + 1] <= sum) {
        mx = max(mx, mid);
        traverse(mid + 1, r, 2 * node + 2, cur + segtree[2 * node + 1], sum);
    } else {
        traverse(l, mid, 2 * node + 1, cur, sum);
    }

}

void update(int l, int r, int ind, long long val, int node) {
    if (l == r) {
        segtree[node] = val;
        segct[node] = 1;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    segct[node] = segct[2 * node + 1] + segct[2 * node + 2];
}

int main() {
	IOS;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
        cin >> query[i].first >> query[i].second;
        if (query[i].first == 'N') {
            st.insert(make_pair(query[i].second, i));
        }
	}
	int m = 0;
	for (auto it = st.begin(); it != st.end(); it++) {
        pos[*it] = m++;
	}
    for (int i = 0; i < q; i++) {
        if (query[i].first == 'N') {
            int ind = pos[make_pair(query[i].second, i)];
            update(0, m - 1, ind, query[i].second, 0);
        } else {
            if (m == 0) {
                cout << 0 << endl;
                continue;
            }
            mx = -1;
            traverse(0, m - 1, 0, 0, query[i].second);
            int ans;
            if (mx == -1) {
                ans = 0;
            } else {
                ans = getct(0, m - 1, 0, mx, 0);
            }
            cout << ans << endl;
        }
	}
	return 0;
}
