//https://codesprintla25.kattis.com/contests/codesprintla25open/problems/balancingthecouncil
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    int temp = n;
    int spf = 2;
    long long sq = sqrtl(n);
    for (int i = 2; i <= sq; i++) {
        if (temp % i == 0) {
            if (spf == 2) {
                spf = i;
            }
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp > 1 && spf == 2) {
        spf = temp;
    }
    if (spf == 2) {
        spf = n + 1;
    }
    if (m > n / 2) {
        m = n - m;
    }
    if (m % 2 == 0 || m >= spf) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}
