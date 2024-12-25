//https://atcoder.jp/contests/abc212/tasks/abc212_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

long long a[N];

int main() {
    IOS;
    long long m;
    cin >> m;
    long long phi = m - 1;
    vector<long long> divs;
    long long sq = sqrtl(phi);
    for (long long i = 1; i <= sq; i++) {
        if (phi % i == 0) {
            divs.push_back(i);
            if (i * i != phi) {
                divs.push_back(phi / i);
            }
        }
    }
    sort(divs.begin(), divs.end());
    long long ans = 0;
    for (int i = 0; i < divs.size(); i++) {
        a[i] += divs[i];
        for (int j = i + 1; j < divs.size(); j++) {
            if (divs[j] % divs[i] == 0) {
                a[j] -= a[i];
            }
        }
        ans += a[i] % M * (divs[i] % M) % M;
    }
    cout << (ans + 1) % M;

    return 0;
}
