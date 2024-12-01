//https://codeforces.com/contest/2029/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int root[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> op;
        for (int i = 0 ; i < n; i++) {
            root[i] = false;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (u != 0 && v != 0) {
                op.push_back(make_pair(u, v));
            } else if (u != 0) {
                root[u] = 1;
            } else {
                root[v] = 1;
            }
        }
        vector<tuple<int, int, int>> ans;
        for (int i = 0; i < op.size(); i++) {
            int u = op[i].first, v = op[i].second;
            ans.push_back(make_tuple(0, u, v));
            root[u] ^= 1, root[v] ^= 1;
        }
        stack<int> s;
        for (int i = 1; i < n; i++) {
            if (root[i]) {
                s.push(i);
            }
        }
        if (s.size()) {
            for (int i = 1; i < n; i++) {
                if (!root[i]) {
                    int u = s.top();
                    s.pop();
                    ans.push_back(make_tuple(0, u, i));
                    s.push(i);
                }
            }
        }
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << get<0>(ans[i]) + 1 << " " << get<1>(ans[i]) + 1 << " " << get<2>(ans[i]) + 1 << endl;
        }
    }

    return 0;
}
