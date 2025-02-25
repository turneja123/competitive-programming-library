//https://dmoj.ca/problem/dcc1p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 998244353;

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

long long s2(long long n) {
    n %= M;
    return n * (n + 1) % M * (2 * n + 1) % M * modPow(6, M - 2) % M;
}

long long s(long long n) {
    long long ans = sqrtl(n);
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        long long ans = ((s(a + b) - s(b)) * (a % M + b % M + 1) + (s(b) - s(a)) * (a % M + 1) + s(a) + 1 + (s2(s(a)) + s2(s(b)) - s2(s(a + b)) + M)) % M;
        cout << ans << endl;
    }
    return 0;
}
