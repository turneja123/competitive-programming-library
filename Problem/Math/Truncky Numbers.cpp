//https://www.spoj.com/problems/ADST01/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

long long modPow(long long a, long long y) {
    a = (a + M) % M;
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
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long ans = (n % M + ((-10 + M) % M * ((1 - modPow(10, n) + M) % M) % M * modPow(1 - 10, M - 2) % M) % M) * modPow(1 - 10, M - 2) % M * 5 % M + n % M;
        cout << ans % M << endl;
    }


    return 0;
}
