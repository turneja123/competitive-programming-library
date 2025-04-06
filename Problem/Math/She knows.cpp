//https://codeforces.com/contest/2092/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

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
    int t;
    cin >> t;
    while (t--) {
        long long n, m; int k;
        cin >> n >> m >> k;
        int X = 0, ct = 0;
        for (int i = 0; i < k; i++) {
            int x, y, c;
            cin >> x >> y >> c;
            if ((x == 1 || x == n || y == 1 || y == m) && !(x == 1 && y == 1) && !(x == 1 && y == m) && !(x == n && y == 1) && !(x == n && y == m)) {
                ct++;
                X ^= c;
            }
        }
        long long ans = modPow(2, n * m - k);
        if (n * 2 + m * 2 - 8 != ct) {
            ans = ans * modPow(2, M - 2) % M;
        }
        cout << (n * 2 + m * 2 - 8 == ct && X ? 0 : ans) << endl;

    }

    return 0;
}
