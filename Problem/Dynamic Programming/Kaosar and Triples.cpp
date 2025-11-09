//https://eolymp.com/en/problems/12263
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;


ll dp[61][2][2][2];

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

ll calc(ll x, ll y, ll z) {
    for (int i = 0; i < 61; i++) {
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int dz = 0; dz < 2; dz++) {
                    dp[i][dx][dy][dz] = 0;
                }
            }
        }
    }
    dp[60][1][1][1] = 1;
    for (int i = 59; i >= 0; i--) {
        ll cx = min(1ll, x & (1ll << i));
        ll cy = min(1ll, y & (1ll << i));
        ll cz = min(1ll, z & (1ll << i));
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int dz = 0; dz < 2; dz++) {
                    for (int addx = 0; addx < 2; addx++) {
                        for (int addy = 0; addy < 2; addy++) {
                            int addz = addx ^ addy;
                            if (dx && !cx && addx) {
                                continue;
                            }
                            if (dy && !cy && addy) {
                                continue;
                            }
                            if (dz && !cz && addz) {
                                continue;
                            }

                            int can = 1;
                            int nx, ny, nz;
                            if (dx && addx == cx) {
                                nx = 1;
                            } else {
                                nx = 0;
                            }
                            if (dy && addy == cy) {
                                ny = 1;
                            } else {
                                ny = 0;
                            }
                            if (dz && addz == cz) {
                                nz = 1;
                            } else {
                                nz = 0;
                            }
                            dp[i][nx][ny][nz] = (dp[i][nx][ny][nz] + dp[i + 1][dx][dy][dz]) % M;
                        }
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int dx = 0; dx < 2; dx++) {
        for (int dy = 0; dy < 2; dy++) {
            for (int dz = 0; dz < 2; dz++) {
                ans = (ans + dp[0][dx][dy][dz]) % M;
            }
        }
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        ll ans = 0;
        for (int i = 0; i < 8; i++) {
            int c1 = i & 1, c2 = i & 2, c3 = i & 4;
            ll x = (c1 ? r : l - 1), y = (c2 ? r : l - 1), z = (c3 ? r : l - 1);
            int pc = (c1 > 0) + (c2 > 0) + (c3 > 0);
            ans += calc(x, y, z) * (pc % 2 == 1 ? 1 : -1);
        }
        cout << (ans + 100 * M) % M * modPow(6, M - 2) % M << endl;
    }
    return 0;
}
