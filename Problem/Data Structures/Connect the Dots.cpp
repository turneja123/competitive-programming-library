//https://codeforces.com/contest/2020/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int sz[N];
set<pair<int, int>> ivals[11][11];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void interval_insert(int l, int r, int n, int m) {
    if (ivals[n][m].empty()) {
        ivals[n][m].insert(make_pair(l, r));
        return;
    }
    auto it = ivals[n][m].lower_bound({l, r});
    if (it != ivals[n][m].begin()) {
        --it;
        if (it->second < l) {
            ++it;
        }
    }
    int new_l = l;
    int new_r = r;
    while (it != ivals[n][m].end() && it->first <= r) {
        new_l = min(new_l, it->first);
        new_r = max(new_r, it->second);
        it = ivals[n][m].erase(it);
    }
    ivals[n][m].insert(make_pair(new_l, new_r));
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int a, d, k;
            cin >> a >> d >> k;
            a--;
            interval_insert(a / d, a / d + k, d, a % d);
        }
        for (int x = 1; x < 11; x++) {
            for (int y = 0; y < x; y++) {
                for (auto it = ivals[x][y].begin(); it != ivals[x][y].end(); ++it) {
                    for (int i = it->first; i <= it->second; i++) {
                        int a = it->first * x + y, b = i * x + y;
                        a = dsu_find(a), b = dsu_find(b);
                        if (a != b) {
                            dsu_unite(a, b);
                        }
                    }
                }
                ivals[x][y].clear();
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i) {
                ans++;
            }
        }
        cout << ans << endl;

    }

    return 0;
}
