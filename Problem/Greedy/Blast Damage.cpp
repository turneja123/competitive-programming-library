//https://usaco.org/index.php?page=viewproblem&cpid=1585
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int deg[N];


pair<ll, vector<pair<int, int>>> calc(vector<int> &a, int f) {
    int n = a.size();
    vector<int> ans(n);
    for (int i = (f == 1 ? 0 : n - 1); (f == 1 ? i < n : i >= 0); i += f) {
        int need = (f == 1 ? a[i] - ((i == 0 ? 0 : ans[i - 1]) + ans[i]) : a[i] - ((i == n - 1 ? 0 : ans[i + 1]) + ans[i]));
        if (need <= 0) {
            continue;
        }
        if (f == 1) {
            if (i != n - 1) {
                int ct = min(need, a[i + 1] - ans[i + 1]);
                ans[i + 1] += ct;
                need -= ct;
            }

            int ct = min(need, a[i] - ans[i]);
            ans[i] += ct;
            need -= ct;

            if (i != 0) {
                ct = min(need, a[i - 1] - ans[i - 1]);
                ans[i - 1] += ct;
                need -= ct;
            }
        } else {
            if (i != 0) {
                int ct = min(need, a[i - 1] - ans[i - 1]);
                ans[i - 1] += ct;
                need -= ct;
            }

            int ct = min(need, a[i] - ans[i]);
            ans[i] += ct;
            need -= ct;

            if (i != n - 1) {
                int ct = min(need, a[i + 1] - ans[i + 1]);
                ans[i + 1] += ct;
                need -= ct;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (ans[i] + ans[i - 1] > a[i]) {
            deg[i - 1]++;
            adj[i].push_back(i - 1);
        }
        if (ans[i] + ans[i - 1] > a[i - 1]) {
            deg[i]++;
            adj[i - 1].push_back(i);
        }
    }
    vector<pair<int, int>> ord;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        if (ans[u]) {
            ord.push_back({u + 1, ans[u]});
        }
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    ll s = 0;
    for (int i = 0; i < n; i++) {
        s += ans[i];
        adj[i].clear();
    }
    return {s, ord};
}

int main() {
    IOS;
    int t, m;
    cin >> t >> m;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        auto try1 = calc(a, 1), try2 = calc(a, -1);
        ll s = try1.first;
        vector<pair<int, int>> ord;
        if (try1.second.size() < try2.second.size()) {
            ord = try1.second;
        } else {
            ord = try2.second;
        }


        cout << s << endl;
        if (m != 0) {
            cout << ord.size() << endl;
            for (auto [i, j] : ord) {
                cout << i << " " << j << endl;
            }
        }

    }
    return 0;
}
