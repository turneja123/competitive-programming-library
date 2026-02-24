//https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int p[N];
int parent[N];
int sz[N];
int timer[N];
ll ct[N][2];
int st[N];
int en[N];
int go[N];

struct Item {
    int u;
    ll x;
    ll y;
    int timer;
};


int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    sz[a] += sz[b];
    parent[b] = a;
    ct[a][0] += ct[b][0];
    ct[a][1] += ct[b][1];
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> ct[i][0];
    }
    for (int i = 0; i < n; i++) {
        cin >> ct[i][1];
    }

    auto comp = [](Item a, Item b) {
        if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0) {
            return false;
        }
        if (a.x == 0 && a.y == 0) {
            return true;
        }
        if (b.x == 0 && b.y == 0) {
            return false;
        }

        return (__int128)a.x * b.y < (__int128)b.x * a.y;
    };
    priority_queue<Item, vector<Item>, decltype(comp)> pq(comp);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        st[i] = i;
        en[i] = i;
        go[i] = -1;
        if (i != 0) {
            Item j = {i, ct[i][0], ct[i][1], 0};
            pq.push(j);
        }
    }
    int t = 1;
    ll ans = 0;
    while (pq.size()) {
        auto i = pq.top();
        pq.pop();
        if (dsu_find(i.u) != i.u || timer[i.u] != i.timer) {
            continue;
        }
        int x = i.u, y = dsu_find(p[x]);
        timer[y] = t;
        ans += (ll)ct[x][0] * ct[y][1];
        dsu_unite(y, x);
        go[en[y]] = st[x];
        en[y] = en[x];
        if (y != 0) {
            pq.push({y, ct[y][0], ct[y][1], t});
        }
        t++;
    }
    cout << ans << endl;
    for (int i = 0; i != -1; i = go[i]) {
        cout << i << " ";
    }


    return 0;
}
