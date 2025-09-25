//https://basecamp.eolymp.com/en/problems/12216
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<int> divs[N];
ll sum[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    bool flipped = false;
    if (n > m) {
        flipped = true;
        vector<vector<int>> tmp(m, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[j][i] = a[i][j];
            }
        }
        swap(n, m);
        a = tmp;
    }

    int q;
    cin >> q;
    vector<tuple<int, int, int, int, ll>> queries;

    for (int i = 0; i < q; i++) {
        int x, y, d, c; ll s;
        cin >> x >> y >> d >> c >> s;
        x--, y--;
        if (flipped) {
            swap(x, y);
        }
        queries.push_back({x, y, d, c, s});
    }
    int SQ = sqrt(n);
    vector<vector<ll>> ans(n, vector<ll>(m, 0));
    vector<vector<vector<pair<int, ll>>>> op_add(SQ, vector<vector<pair<int, ll>>>(m, vector<pair<int, ll>>()));
    vector<vector<vector<pair<int, ll>>>> op_rem(SQ, vector<vector<pair<int, ll>>>(m, vector<pair<int, ll>>()));

    for (int k = 0; k < n; k++) {
        int lf = k * SQ, rt = min(n - 1, (k + 1) * SQ - 1);
        if (lf >= n) {
            break;
        }

        for (int i = 0; i < q; i++) {
            auto [x, y, d, c, s] = queries[i];
            for (int j = min(rt, x); j >= max(lf, 0); j--) {
                ll z = (ll)d * d - (ll)(x - j) * (x - j);
                if (z < 0) {
                    break;
                }
                ll L = sqrtl(z);
                int len = L;
                int l = max(0, y - len), r = min(m - 1, y + len);
                op_add[j - lf][l].push_back({c, s});
                op_rem[j - lf][r].push_back({c, s});
            }
            for (int j = max(lf, x + 1); j <= min(rt, n - 1); j++) {
                ll z = (ll)d * d - (ll)(x - j) * (x - j);
                if (z < 0) {
                    break;
                }
                ll L = sqrtl(z);
                int len = L;
                int l = max(0, y - len), r = min(m - 1, y + len);
                op_add[j - lf][l].push_back({c, s});
                op_rem[j - lf][r].push_back({c, s});
            }
        }
        ll sumall = 0;
        for (int i = lf; i <= rt; i++) {
            for (int j = 0; j < m; j++) {
                for (auto [d, s] : op_add[i - lf][j]) {
                    sum[d] += s;
                    sumall += s;
                }
                if (a[i][j] > 0) {
                    for (int d : divs[a[i][j]]) {
                        ans[i][j] += sum[d];
                    }
                } else {
                    ans[i][j] += sumall;
                }
                for (auto [d, s] : op_rem[i - lf][j]) {
                    sum[d] -= s;
                    sumall -= s;
                }
                op_add[i - lf][j].clear();
                op_rem[i - lf][j].clear();
            }
        }
    }


    if (flipped) {
        vector<vector<ll>> tmp(m, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[j][i] = ans[i][j];
            }
        }
        swap(n, m);
        ans = tmp;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
