//https://www.codechef.com/problems/ARRCONCAT
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 2e6 + 5;

long long fact[N];

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

long long binomial(long long n, long long k) {
    return fact[n] * modPow(fact[k] * fact[n - k] % M, M - 2) % M;
}

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int n = a + b;
        long long ans = 0;
        for (int i = 0; i <= n / 4; i++) {
            int one = n / 2;
            if (b >= i * 2 && b - i * 2 <= one) {
                ans += binomial(one, b - i * 2) * binomial(n / 4, i) % M * binomial(n / 2 - n / 4, i) % M;
            }
        }
        cout << ans % M << endl;
    }
    return 0;
}
