//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/8
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;

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
    int n;
    cin >> n;
    long long f = 1;
    for (int i = 1; i <= n; i++) {
        f = f * i % (M - 1);
        if (f == 0) {
            break;
        }
    }
    if (f == 0) {
        cout << n;
        return 0;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + modPow(i, f)) % M;
    }
    ans = ans * modPow(modPow(n, f), M - 2) % M;
    cout << ans;

    return 0;
}
