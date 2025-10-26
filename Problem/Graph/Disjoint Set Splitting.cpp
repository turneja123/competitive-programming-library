//https://qoj.ac/contest/2559/problem/14418
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int parent[N];
int sz[N];

vector<pair<int, int>> add[N];

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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + (x.second << 32) + FIXED_RANDOM);
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        gp_hash_table<pair<int, int>, int, custom_hash> mp;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        int comps = n;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u > v) {
                swap(u, v);
            }
            mp[{u, v}] = q;
        }
        int last2 = 0, last3 = 0;
        for (int i = 0; i < q; i++) {
            int a, b;
            cin >> a >> b;
            int u = (last2 + a) % n, v = (last3 + b) % n;
            if (u > v) {
                swap(u, v);
            }
            auto it = mp.find({u, v});
            if (it == mp.end()) {
                last2 = (last2 * 2 + 1) % n;
                last3 = (last3 * 3 + 1) % n;
                continue;
            }
            mp[{u, v}] = min(mp[{u, v}], i);
            last2 = (last2 * 2 + 1) % n;
            last3 = (last3 * 3 + 1) % n;

        }

        for (auto it = mp.begin(); it != mp.end(); it++) {
            auto [u, v] = it->first; int tim = it->second;
            add[tim].push_back({u, v});
        }
        int spl = -1;
        for (auto [u, v] : add[q]) {
            u = dsu_find(u), v = dsu_find(v);
            if (u != v) {
                comps--;
                dsu_unite(u, v);
            }
        }
        if (comps == 1) {
            spl = q - 1;
        } else {
            for (int i = q - 1; i >= 0; i--) {
                for (auto [u, v] : add[i]) {
                    u = dsu_find(u), v = dsu_find(v);
                    if (u != v) {
                        comps--;
                        dsu_unite(u, v);
                    }
                }
                if (comps == 1) {
                    spl = i - 1;
                    break;
                }
            }
        }
        for (int i = 0; i <= spl; i++) {
            cout << 1 << endl;
        }
        for (int i = spl + 1; i < q; i++) {
            cout << 0 << endl;
        }
        for (int i = 0; i <= q; i++) {
            add[i].clear();
        }

    }
    return 0;
}
