//https://codeforces.com/contest/1879/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 30;
const long long M = 998244353;

int a[N];
int cur[K];

long long sum[K][2];
long long ct[K][2];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int j = 0; j < K; j++) {
        ct[j][0] = 1;
        sum[j][0] = -1;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < K; j++) {
            int c = a[i] & (1 << j);
            if (c) {
                cur[j] ^= 1;
            }
            ans = (ans + ((long long)i * ct[j][cur[j] ^ 1] - sum[j][cur[j] ^ 1] + M) % M * (1 << j) % M) % M;
            sum[j][cur[j]] = (sum[j][cur[j]] + i) % M;
            ct[j][cur[j]]++;
        }
    }
    cout << ans;


    return 0;
}
