//solution for https://cses.fi/problemset/task/1079/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 1e6 + 5;

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
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long n, k;
        cin >> n >> k;
        cout << binomial(n, k) << endl;
    }
    return 0;
}
