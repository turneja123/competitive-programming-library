//https://judge.yosupo.jp/problem/queue_operate_all_composite
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 998244353;

long long a[N], b[N];

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
    int n, m = 0;
    cin >> n;
    long long prod = 1, sum = 0;
    for (int i = 0, j = 0; i < n; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            cin >> a[m] >> b[m];
            prod = prod * a[m] % M;
            sum = (sum * a[m] + b[m]) % M;
            m++;
        } else if (t == 1) {
            prod = prod * modPow(a[j], M - 2) % M;
            sum = (sum - prod * b[j] % M + M) % M;
            j++;
        } else {
            long long x;
            cin >> x;
            cout << (prod * x + sum) % M << endl;
        }
    }

    return 0;
}
