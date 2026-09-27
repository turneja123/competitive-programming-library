//https://atcoder.jp/contests/arc229/tasks/arc229_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

vector<int> v[2];
int p[2];

ll calc(vector<int> &cur) {

    for (int i = 1; i < cur.size() - 1; i++) {
        int z = (cur[i - 1] % 2) ^ 1;
        if (p[z] == v[z].size()) {
            z ^= 1;
        }
        cur[i] = v[z][p[z]++];
    }
    ll ans = 0;
    for (int i = 1; i < cur.size(); i++) {
        ans += (cur[i] + cur[i - 1]) / 2;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            v[a[i] % 2].push_back(a[i]);
        }
        if (n == 2) {
            cout << (a[0] + a[1]) / 2 << endl;
            v[0].clear();
            v[1].clear();
            continue;
        }
        sort(v[0].begin(), v[0].end(), greater<int>());
        sort(v[1].begin(), v[1].end(), greater<int>());

        ll ans = INF;
        if (v[0].size() >= 1 && v[1].size() >= 1) {
            vector<int> cur(n, 0);
            cur[0] = v[0][0];
            cur.back() = v[1][0];
            p[0] = 1;
            p[1] = 1;
            ans = min(ans, calc(cur));
        }
        if (v[0].size() >= 1 && v[1].size() >= 1) {
            vector<int> cur(n, 0);
            cur[0] = v[1][0];
            cur.back() = v[0][0];
            p[0] = 1;
            p[1] = 1;
            ans = min(ans, calc(cur));
        }

        if (v[0].size() >= 2) {
            vector<int> cur(n, 0);
            cur[0] = v[0][0];
            cur.back() = v[0][1];
            p[0] = 2;
            p[1] = 0;
            ans = min(ans, calc(cur));
        }
        if (v[1].size() >= 2) {
            vector<int> cur(n, 0);
            cur[0] = v[1][0];
            cur.back() = v[1][1];
            p[0] = 0;
            p[1] = 2;
            ans = min(ans, calc(cur));
        }

        cout << ans << endl;
        v[0].clear();
        v[1].clear();
    }
    return 0;
}
