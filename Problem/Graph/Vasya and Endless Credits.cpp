//https://codeforces.com/contest/1107/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long INF = 1e18;

long long a[N], b[N], x[N];

long long cost[N][N];
long long u[N], v[N];
int p[N], way[N];

long long hungarian(int n) {
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<long long> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = INF;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    long long cur = cost[i0][j] - u[i0] - v[j];
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
    long long c = v[0];
    for (int i = 0; i <= n; i++) {
        u[i] = 0, v[i] = 0;
        way[i] = 0, p[i] = 0;
    }
    return c;
}

long long calc(int k, int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j <= k) {
                int l = j, r = min((ll)k - 1, j + x[i] - 1);
                cost[i][j] = -(a[i] - b[i] * (r - l + 1));
            } else {
                cost[i][j] = 0;
            }
        }
    }
    return hungarian(n);
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> x[i];
    }
    int l = 1, r = n;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        long long f1 = calc(m1, n);
        long long f2 = calc(m2, n);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    long long ans = 0;
    for (; l <= r; l++) {
        ans = max(ans, calc(l, n));
    }
    cout << ans;
    return 0;
}
