//https://cses.fi/problemset/task/1740/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

pair<pair<int, int>, pair<int, int>> a[N];

vector<pair<int, pair<int, int>>> v;
vector<pair<pair<int, int>, int>> h;

int segtree[4 * N];

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += val;
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

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) + getSum(mid + 1, r, lq, rq, 2 * node + 2);
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first.first >> a[i].first.second;
        cin >> a[i].second.first >> a[i].second.second;
        a[i].first.first += 1e6, a[i].first.second += 1e6;
        a[i].second.first += 1e6, a[i].second.second += 1e6;
        if (a[i].first.first == a[i].second.first) {
            v.push_back(make_pair(a[i].first.first, make_pair(a[i].first.second, a[i].second.second)));
        } else {
            h.push_back(make_pair(make_pair(a[i].first.first, a[i].second.first), a[i].first.second));
        }
    }
    n = v.size();
    int m = h.size();
    sort(v.begin(), v.end());
    sort(h.begin(), h.end());
    priority_queue<pair<int, int>> pq;
    long long ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < m && h[j].first.first <= v[i].first) {
            update(0, N - 1, h[j].second, 1, 0);
            pq.push(make_pair(-h[j].first.second, h[j].second));
            j++;
        }
        while (pq.size() && -pq.top().first < v[i].first) {
            update(0, N - 1, pq.top().second, -1, 0);
            pq.pop();
        }
        ans += getSum(0, N - 1, v[i].second.first, v[i].second.second, 0);
    }
    cout << ans;
    return 0;
}
