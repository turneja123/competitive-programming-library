//https://tlx.toki.id/contests/troc-42/problems/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 17;
const ll M = 998244353;

int a[1 << N];

ll pref[1 << N][N][2];
ll ct[2][2][N]; //pc, popcount, flipovan
ll sum[2][2][2][N];

int pc(int x) {
    if (x == 0) {
        return 0;
    }
    return __builtin_popcount(x);
}

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

ll calc(int n) {
    ll ans = 0;
    for (int b = 0; b < 2; b++) {
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                for (int j = 0; j < n; j++) {
                    ct[b][x][j] = 0;
                    sum[b][x][y][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 1 << n; i++) {
        int b = pc(a[i]) % 2;

        for (int j = 0; j < n; j++) {
            pref[i][j][0] = (i == 0 ? 0 : pref[i - 1][j][0]);
            pref[i][j][1] = (i == 0 ? 0 : pref[i - 1][j][1]);
            int c = a[i] & (1 << j);
            if (c) {
                pref[i][j][0] += 1;
                pref[i][j][0] %= M;
            } else {
                pref[i][j][1] += 1;
                pref[i][j][1] %= M;
            }
            if (i == 0) {
                continue;
            }

            int zr = pc(a[i] % (1 << j));
            if (zr % 2 == 1) {
                ans = (ans + (pref[i][j][0] * ct[b][1][j] % M - sum[b][1][0][j] + M) * (1 << j)) % M; //normal
                ans = (ans + (pref[i][j][1] * ct[b][0][j] % M - sum[b][0][1][j] + M) * (1 << j)) % M; //flip
            } else {
                ans = (ans + (pref[i][j][0] * ct[b][0][j] % M - sum[b][0][0][j] + M) * (1 << j)) % M;
                ans = (ans + (pref[i][j][1] * ct[b][1][j] % M - sum[b][1][1][j] + M) * (1 << j)) % M;

            }
        }
        for (int j = 0; j < n; j++) {
            int c = a[i] & (1 << j);
            int zl = pc(a[i] % (1 << (j + 1))) % 2;

            sum[b][zl][0][j] = (sum[b][zl][0][j] + (i == 0 ? 0 : pref[i - 1][j][0])) % M;
            sum[b][zl][1][j] = (sum[b][zl][1][j] + (i == 0 ? 0 : pref[i - 1][j][1])) % M;

            ct[b][zl][j]++;
        }
    }
    return ans;

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    ll ans = calc(n);
    reverse(a, a + (1 << n));
    ans = (ans + calc(n)) % M;
    ans = ans * modPow(1 << n, M - 2) % M;
    cout << ans;

    return 0;
}
