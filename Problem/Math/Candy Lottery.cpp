//https://cses.fi/problemset/task/1727/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long double pw[N];
long double ct[N];

long double Pow(long double a, int y) {
    long double res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res *= a;
        }
        y /= 2;
        a *= a;
    }
    return res;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(6);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        pw[i] = Pow((long double)i / (long double)m, n);
    }
    long double ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += (pw[i] - pw[i - 1]) * (long double)i;
    }
    cout << ans;
    return 0;
}
