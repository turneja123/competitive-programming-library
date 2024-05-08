//https://www.spoj.com/problems/SLNCRD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 7;

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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long sum_1 = modDivide(n * (n + 1), 2, M);
        long long sum_2 = modDivide(n * (n + 1) % M * (2 * n + 1), 6, M);
        long long ans = modDivide(sum_1 + sum_2, 2, M);
        cout << ans << endl;
    }
    return 0;
}
