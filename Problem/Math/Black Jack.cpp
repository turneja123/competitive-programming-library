//https://atcoder.jp/contests/abc342/tasks/abc342_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

long double y[N];
long double diffy[N];
long double prefy[N];
long double x[N];
long double sufx[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, l, d;
    cin >> n >> l >> d;
    diffy[1] += (long double)1.0 / (long double)d;
    diffy[1 + d] -= (long double)1.0 / (long double)d;
    long double sum = 0;
    for (int i = 1; i < N; i++) {
        sum += diffy[i];
        y[i] = sum;
        if (i < l) {
            diffy[i + 1] += (long double)y[i] / (long double)d;
            diffy[i + 1 + d] -= (long double)y[i] / (long double)d;
        }
    }
    sum = 0.0;
    for (int i = l; i < N; i++) {
        sum += y[i];
    }
    for (int i = l; i < N; i++) {
        y[i] /= sum;
        prefy[i] = prefy[i - 1] + y[i];
    }
    for (int i = n; i >= 0; i--) {
        long double cur = 1.0 - (prefy[n] - prefy[i - 1]);
        x[i] = max(cur, (sufx[i + 1] - sufx[i + 1 + d]) / (long double)d);
        sufx[i] = sufx[i + 1] + x[i];
    }
    cout << x[0];

    return 0;
}
