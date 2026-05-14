//https://bubblecup.org/CompetitorsCorner/Problem/ARRAYPOP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e8 + 5;
const ll M = 998244353;

char is_prime[N];
int ct[N / 10];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << 1;
        return 0;
    }
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }
    int p = 0;
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            ct[p] += i <= m;
            if ((ll)i * i < N) {
                for (int j = i * i; j < N; j += i) {
                    if (is_prime[j]) {
                        ct[p] += j <= m;
                        is_prime[j] = 0;
                    }
                }
            }
            p++;
        }
    }
    p = 0;
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (is_prime[i]) {
            m -= ct[p++];
        }
        ans = ans * m % M;
    }
    cout << ans;

    return 0;
}
