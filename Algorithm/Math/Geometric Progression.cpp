//https://atcoder.jp/contests/abc293/tasks/abc293_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

__int128 modPow(__int128 a, __int128 y, __int128 m) {
    __int128 res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

int main() {
    IOS;
    __int128 a, x, m;
    a = read(), x = read(), m = read();
    if (a == 1) {
        __int128 ans = x % m;
        print(ans);
        return 0;
    }
    __int128 M = m * (a - 1);
    __int128 ans = ((modPow(a, x, M) - 1) / (a - 1) + M) % M;
    print(ans);
    return 0;
}
