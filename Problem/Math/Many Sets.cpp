//https://atcoder.jp/contests/arc218/tasks/arc218_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const ll M = 998244353;

vector<int> a[N];
vector<pair<int, int>> pos[N * N];

vector<pair<int, int>> rle(vector<int> &a) {
    int n = a.size();
    vector<pair<int, int>> v;
    int last = -1, ct = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != last) {
            if (ct) {
                v.push_back({last, ct});
            }
            last = a[i];
            ct = 1;
        } else {
            ct++;
        }
    }
    v.push_back({last, ct});
    return v;
}

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            a[i][j]--;
        }
        sort(a[i].begin(), a[i].end());
        vector<pair<int, int>> v = rle(a[i]);
        for (auto [x, y] : v) {
            pos[x].push_back({i, y});
        }
    }
    ll ans = 0;
    for (int x = 0; x < n * m; x++) {
        ll prod = 1; int last = 0;
        for (auto [i, y] : pos[x]) {
            prod = prod * modPow(m, i - last) % M;
            ans = (ans + prod * y % M * modPow(m, n - i - 1)) % M;
            prod = prod * (m - y) % M;
            last = i + 1;
        }
    }
    cout << ans;

    return 0;
}
