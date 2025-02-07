//https://atcoder.jp/contests/abc391/tasks/abc391_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int ans[N];
vector<pair<int, int>> v[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        ans[i] = -1;
        int x, y;
        cin >> x >> y;
        x--, y--;
        v[x].push_back(make_pair(y, i));
    }
    for (int i = 0; i < m; i++) {
        sort(v[i].begin(), v[i].end());
        reverse(v[i].begin(), v[i].end());
    }
    int mx = -1, j = 1;
    while (1) {
        bool has = true;

        for (int i = 0; i < m; i++) {
            if (v[i].empty()) {
                has = false;
                break;
            }
            mx = max(mx, v[i].back().first);
        }
        if (!has) {
            break;
        }
        for (int i = 0; i < m; i++) {
            ans[v[i].back().second] = j + mx;
            v[i].pop_back();
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, x;
        cin >> t >> x;
        x--;
        if (ans[x] == -1) {
            cout << "Yes" << endl;
            continue;
        }
        if (ans[x] <= t) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
