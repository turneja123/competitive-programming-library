//https://atcoder.jp/contests/abc383/tasks/abc383_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e6 + 5;

long long a[N];

bool composite[N];


int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            for (int j = 2 * i; j < N; j += i) {
                composite[j] = true;
            }
        }
    }

    long long n;
    cin >> n;
    long long ans = 0;
    int j = 0;
    for (int i = 2; i < N; i++) {
        if (composite[i]) {
            continue;
        }

        long long prod = 1;
        for (int j = 0; j < 2; j++) {
            prod *= i;
        }
        if (prod > n) {
            break;
        }
        a[j++] = prod;
    }
    for (int i = 0; i < j; i++) {
        long long need = n / a[i];
        int x = upper_bound(a, a + j, need) - a;
        ans += x;
    }
    for (int i = 2; i < N; i++) {
        if (composite[i]) {
            continue;
        }

        long long prod = 1;
        for (int j = 0; j < 4; j++) {
            prod *= i;
        }
        if (prod > n) {
            break;
        }
        ans--;
    }
    ans /= 2;
    for (int i = 2; i < N; i++) {
        if (composite[i]) {
            continue;
        }

        long long prod = 1;
        for (int j = 0; j < 8; j++) {
            prod *= i;
        }
        if (prod > n) {
            break;
        }
        ans++;
    }
    cout << ans;
    return 0;
}
