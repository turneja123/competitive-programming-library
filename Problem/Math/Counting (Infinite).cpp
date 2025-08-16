//https://www.codechef.com/problems/CNTINF
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const ll M = 998244353;

int s[N][N];
ll fact[N];

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

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    s[0][0] = 1;
    for (int i = 2; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            s[i][j] = ((ll)j * s[i - 1][j] + (ll)(i - 1) * s[i - 2][j - 1]) % M;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        ll all = modPow(k, n);
        if (k > n) {
            cout << all << endl;
            continue;
        }
        ll bad = s[n][k] * fact[k] % M;
        cout << (all - bad + M) % M << endl;

    }
    return 0;
}
