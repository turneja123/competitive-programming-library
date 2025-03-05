//https://codeforces.com/contest/2021/problem/E3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

int parent[N];
int sz[N];
int ct[N];
//long long dp[N][N];
int a[N];
multiset<long long> st[N];
long long old[N];

tuple<int, int, int> edge[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b, int wt) {
    /*if (sz[b] > sz[a]) {
        swap(a, b);
    }
    vector<long long> dp_nw(ct[a] + ct[b] + 1, INF);
    for (int i = 0; i <= ct[a]; i++) {
        for (int j = 0; j <= ct[b]; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (i == 0) {
                dp_nw[j] = min(dp_nw[j], dp[b][j] + (long long)wt * ct[a]);
            } else if (j == 0) {
                dp_nw[i] = min(dp_nw[i], dp[a][i] + (long long)wt * ct[b]);
            } else {
                dp_nw[i + j] = min(dp_nw[i + j], dp[a][i] + dp[b][j]);
            }
        }
    }
    for (int i = 0; i <= ct[a] + ct[b]; i++) {
        dp[a][i] = dp_nw[i];
    }
    sz[a] += sz[b];*/
    if (st[b].size() > st[a].size()) {
        swap(a, b);
    }
    long long dpa = *st[a].begin() + old[a];
    st[a].erase(st[a].begin());
    st[a].insert(dpa - (long long)wt * ct[a]);


    long long dpb = *st[b].begin() + old[b];
    st[b].erase(st[b].begin());
    st[b].insert(dpb - (long long)wt * ct[b]);


    for (long long x : st[b]) {
        st[a].insert(x);
    }
    ct[a] += ct[b];
    old[a] = (long long)wt * ct[a];
    parent[b] = a;
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < k; i++) {
            int u;
            cin >> u;
            u--;
            a[u] = 1;
        }
        for (int i = 0; i < m; i++) {
            int a, b, wt;
            cin >> a >> b >> wt;
            a--, b--;
            edge[i] = make_tuple(wt, a, b);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            st[i].insert(0);
            old[i] = 0;
            ct[i] = a[i];
        }
        sort(edge, edge + m);
        for (int i = 0; i < m; i++) {
            auto [wt, a, b] = edge[i];
            int p1 = dsu_find(a);
            int p2 = dsu_find(b);
            if (p1 != p2) {
                dsu_unite(p1, p2, wt);
            }
        }
        int p = dsu_find(0);
        vector<long long> diff, out;
        for (long long x : st[p]) {
            diff.push_back(x);
        }
        reverse(diff.begin(), diff.end());
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            out.push_back(ans);
            ans -= diff[i];
        }
        reverse(out.begin(), out.end());
        for (long long x : out) {
            cout << x << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            st[i].clear();
            a[i] = 0;
        }
        /*for (int i = 1; i <= n; i++) {
            cout << dp[p][i] << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
            }
            a[i] = 0;
        }*/
    }

    return 0;
}
