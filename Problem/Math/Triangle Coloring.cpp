//https://codeforces.com/contest/1795/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

long long fact[N];

long long modInverse(long long a, long long m) {
    long long res = 1;
    long long y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

long long modDivide(long long a, long long b, long long m) {
    a = a % m;
    long long inv = modInverse(b, m);
    return (inv * a) % m;
}

long long binomial(long long n, long long k, long long m) {
    long long num = fact[n];
    long long denom = (fact[k] * fact[n - k]) % m;
    return modDivide(num, denom, m);
}

int main() {
    IOS;
    long long f = 1;
    fact[0] = 1;
    for (long long i = 1; i < N; i++) {
        f *= i;
        f %= M;
        fact[i] = f;
    }
    int n;
    cin >> n;
    long long ans = 1;
    for (int i = 0; i < n; i += 3) {
        vector<int> v(3, 0);
        cin >> v[0] >> v[1] >> v[2];
        sort(v.begin(), v.end());
        if (v[0] == v[1] && v[0] != v[2]) {
            ans = ans * 2 % M;
        }
        if (v[0] == v[2]) {
            ans = ans * 3 % M;
        }
    }
    ans = ans * binomial(n / 3, n / 6, M) % M;
    cout << ans;


    return 0;
}
