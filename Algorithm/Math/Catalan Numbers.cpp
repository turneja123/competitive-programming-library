//https://cses.fi/problemset/task/2187
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const long long M = 1e9 + 7;

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
    int n, k = 0;
    string s;
    cin >> n >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            k++;
        } else {
            k--;
        }
        if (k < 0) {
            cout << 0;
            return 0;
        }
    }
    n -= s.size();
    n += k;
    if (n % 2 == 1 || k > n / 2) {
        cout << 0;
        return 0;
    }
    n /= 2;
    n -= k;
    long long ans = modPow(n + 1 + k, M - 2) * (k + 1) % M * binomial(2 * n + k, n) % M;
    cout << ans;
    return 0;
}
