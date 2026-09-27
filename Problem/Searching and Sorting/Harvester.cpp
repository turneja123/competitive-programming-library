//https://codeforces.com/contest/1219/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n, m;
    cin >> n >> m;

    vector<ll> rowold(n);
    vector<ll> colold(m);
    vector<pair<ll, int>> row(n);
    vector<pair<ll, int>> col(m);
    for (int i = 0; i < n; i++) {
        row[i] = {0, i};
    }
    for (int j = 0; j < m; j++) {
        col[j] = {0, j};
    }
    vector<vector<ll>> a(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            row[i].first += a[i][j], col[j].first += a[i][j];
            rowold[i] += a[i][j], colold[j] += a[i][j];
        }
    }
    for (int i = n * m; i < 4; i++) {
        rowold.push_back(0);
        row.push_back({0, n + i - n * m});
        vector<ll> v(m, 0);
        a.push_back(v);
    }

    sort(row.begin(), row.end(), greater<pair<ll,int>>());
    sort(col.begin(), col.end(), greater<pair<ll,int>>());

    vector<pair<int, int>> cand;
    for (int i = 0; i < min(20, (int)row.size()); i++) {
        cand.push_back({0, row[i].second});
    }
    for (int j = 0; j < min(20, (int)col.size()); j++) {
        cand.push_back({1, col[j].second});
    }
    ll ans = 0;
    for (int i = 0; i < cand.size(); i++) {
        for (int j = i + 1; j < cand.size(); j++) {
            for (int k = j + 1; k < cand.size(); k++) {
                for (int p = k + 1; p < cand.size(); p++) {
                    vector<int> l, r;
                    ll cur = 0;
                    if (cand[i].first == 0) {
                        cur += rowold[cand[i].second];
                        l.push_back(cand[i].second);
                    } else {
                        cur += colold[cand[i].second];
                        r.push_back(cand[i].second);
                    }

                    if (cand[j].first == 0) {
                        cur += rowold[cand[j].second];
                        l.push_back(cand[j].second);
                    } else {
                        cur += colold[cand[j].second];
                        r.push_back(cand[j].second);
                    }

                    if (cand[k].first == 0) {
                        cur += rowold[cand[k].second];
                        l.push_back(cand[k].second);
                    } else {
                        cur += colold[cand[k].second];
                        r.push_back(cand[k].second);
                    }

                    if (cand[p].first == 0) {
                        cur += rowold[cand[p].second];
                        l.push_back(cand[p].second);
                    } else {
                        cur += colold[cand[p].second];
                        r.push_back(cand[p].second);
                    }

                    for (int x : l) {
                        for (int y : r) {
                            cur -= a[x][y];
                        }
                    }
                    ans = max(ans, cur);
                }
            }
        }
    }
    cout << ans;

    return 0;
}
