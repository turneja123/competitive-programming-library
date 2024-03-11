//solution for https://www.spoj.com/problems/CPDUEL5B/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

int a[N];

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

bool frac(long long a, long long b, long long c, long long d) {
    long long y = a * d - b * c;
    return (y > 0) ? true : false;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long p = 0, q = 1;
    for (long long i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            cout << -1 << endl;
            return 0;
        }
        if (frac(a[i] - a[0], i, p, q)) {
            p = a[i] - a[0];
            q = i;
            long long gcd = __gcd(p, q);
            p /= gcd;
            q /= gcd;
        }
    }
    for (long long i = 1; i < n; i++) {
        if (a[0] + (p * i) / q != a[i]) {
            cout << -1 << endl;
            return 0;
        }
    }
    long long ans = (p * modInverse(q, M)) % M;
    cout << ans << endl;
    return 0;
}
