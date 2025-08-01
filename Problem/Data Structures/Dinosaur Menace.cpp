//https://www.spoj.com/problems/DINOSM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

const int N = 305;

pair<int, int> a[N];
int sz[N];
int parent[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void dsu_unite(int u, int v) {
    if (sz[u] > sz[v]) {
        swap(u, v);
    }
    sz[v] += sz[u];
    parent[u] = v;

}

ld euclidean(int x1, int x2, int y1, int y2) {
    return sqrt((ld)(x1 - x2) * (x1 - x2) + (ld)(y1 - y2) * (y1 - y2));
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(3);
    while (1) {
        int n, w, h;
        cin >> n >> w >> h;
        if (n == -1) {
            break;
        }
        vector<tuple<ld, int, int>> events;
        for (int i = 0; i < n + 4; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 4; i < n + 4; i++) {
            int x, y;
            cin >> x >> y;
            events.push_back({(ld)x, i, 1});
            events.push_back({(ld)w - (ld)x, i, 3});
            events.push_back({(ld)y, i, 0});
            events.push_back({(ld)h - (ld)y, i, 2});
            a[i] = {x, y};
        }
        for (int i = 4; i < n + 4; i++) {
            for (int j = i + 1; j < n + 4; j++) {
                auto [x1, y1] = a[i];
                auto [x2, y2] = a[j];
                events.push_back({euclidean(x1, x2, y1, y2) / 2.0, i, j});
            }
        }
        sort(events.begin(), events.end());
        for (auto [d, a, b] : events) {
            a = dsu_find(a);
            b = dsu_find(b);
            if (a != b) {
                dsu_unite(a, b);
            }
            if (dsu_find(0) == dsu_find(2) || dsu_find(0) == dsu_find(1) || dsu_find(1) == dsu_find(3) || dsu_find(2) == dsu_find(3)) {
                cout << d << endl;
                break;
            }
        }

    }
    return 0;
}
