//https://qoj.ac/contest/2539/problem/14431
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int a[N];
int table[K][N];

int n;

void build() {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    if (l > r) {
        return n;
    }
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

int calc(int l1, int r1, int l2, int r2) {
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    if (r1 < l2) {
        return min({query(0, l1 - 1), query(r1 + 1, l2 - 1), query(r2 + 1, n - 1)});
    }
    return min(query(0, l1 - 1), query(max(r1, r2) + 1, n - 1));
}


bool comp(tuple<int, int, int> a, tuple<int, int, int> b) {
    return get<1>(a) < get<1>(b);
}

int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build();
    vector<tuple<int, int, int>> v;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        v.push_back({l, r, i});
    }
    sort(v.begin(), v.end());
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m - 1; i++) {
        auto [l1, r1, I] = v[i];
        auto [l2, r2, J] = v[i + 1];
        int cost = calc(l1, r1, l2, r2);
        edges.push_back({cost, I, J});
    }
    priority_queue<pair<int, int>> pq;
    int last = -1;
    for (int i = 0; i < m; i++) {
        auto [l1, r1, I] = v[i];
        while (pq.size() && -pq.top().first < l1) {
            last = pq.top().second;
            pq.pop();
        }
        if (last != -1) {
            auto [l2, r2, J] = v[last];
            int cost = calc(l1, r1, l2, r2);
            edges.push_back({cost, I, J});
        }
        pq.push(make_pair(-r1, i));
    }
    for (int i = 0; i < m; i++) {
        auto [l1, r1, I] = v[i];
        int j = upper_bound(v.begin(), v.end(), make_tuple(r1, N, N)) - v.begin();
        if (j != m) {
            auto [l2, r2, J] = v[j];
            int cost = calc(l1, r1, l2, r2);
            edges.push_back({cost, I, J});
        }
    }
    vector<pair<int, int>> pos;
    for (int i = 0; i < m; i++) {
        pos.push_back({get<1>(v[i]), i});
    }
    sort(pos.begin(), pos.end());
    for (int i = 0; i < n; i++) {
        int x = upper_bound(pos.begin(), pos.end(), make_pair(i - 1, N)) - pos.begin() - 1;
        int y = upper_bound(v.begin(), v.end(), make_tuple(i, N, N)) - v.begin();
        if (x >= 0 && y < m) {
            auto [l1, r1, I] = v[pos[x].second];
            auto [l2, r2, J] = v[y];
            int cost = calc(l1, r1, l2, r2);
            edges.push_back({cost, I, J});
        }
    }


    sort(v.begin(), v.end(), comp);
    for (int i = 0; i < m - 1; i++) {
        auto [l1, r1, I] = v[i];
        auto [l2, r2, J] = v[i + 1];
        int cost = calc(l1, r1, l2, r2);
        edges.push_back({cost, I, J});
    }
    for (int i = 0; i < m; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    ll ans = 0;
    sort(edges.begin(), edges.end());
    for (auto [cost, u, v] : edges) {
        u = dsu_find(u), v = dsu_find(v);
        if (u != v) {
            ans += cost;
            dsu_unite(u, v);
        }
    }
    cout << ans;

    return 0;
}
