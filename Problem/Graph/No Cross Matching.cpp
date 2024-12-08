//https://atcoder.jp/contests/abc373/tasks/abc373_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long double INF = 1e18;

pair<long double, long double> a[N], b[N];

long double dist(pair<long double, long double> p1, pair<long double, long double> p2) {
    return sqrtl((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

long double cost[N][N];
long double u[N], v[N];
int p[N], way[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i].first >> b[i].second;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] = dist(a[i], b[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<long double> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long double delta = INF;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    long double cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[p[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
