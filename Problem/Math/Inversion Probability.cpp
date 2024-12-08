//https://cses.fi/problemset/task/1728/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

int a[N];

long double e[N];
long double eps = 1e-18;

int sum(int n) {
    return n * (n + 1) / 2;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(6);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long double ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            int tot = a[i] * a[j];
            int inv = (a[i] >= a[j] ? sum(a[j] - 1) : sum(a[j] - 1) - sum(a[j] - a[i] - 1));
            e[i] += (long double)inv / (long double)tot;
        }
        ans += e[i];
    }
    cout << max((long double)0.0, ans - eps);

    return 0;
}
