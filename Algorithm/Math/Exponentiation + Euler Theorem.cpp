//https://cses.fi/problemset/task/1712/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}
int phi(int n) {
    int res = n;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;
    long long p = phi(M);
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        long long e = p + modPow(b, c, p);
        if (a == 0 && b == 0 && c == 0) {
            cout << 0 << endl;
        } else if (a == 0 && b == 0) {
            cout << 1 << endl;
        } else {
            cout << modPow(a, e, M) << endl;
        }

    }
    return 0;
}
