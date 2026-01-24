//https://www.codechef.com/START222A/problems/GCDLIM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

bool is_prime[N];
int m[N];
ll inv[N];
ll ans[N];
vector<int> divs[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        m[i] = 1;
        is_prime[i] = i != 1;
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            m[i] = -1;
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = 0;
                if ((ll)j % ((ll)i * i) == 0) {
                    m[j] = 0;
                }
                m[j] *= -1;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll sum = 0;
        for (int i = 2; i <= n; i++) {
            ans[i] = 0;
            for (int j : divs[i]) {
                ans[i] = (ans[i] + (n - n / j) * (M + m[i / j]) % M * inv[n - n / i] % M) % M;
            }
            sum = (sum + ans[i] * (n / i)) % M;
        }
        cout << sum * inv[n] % M << endl;
    }


    return 0;
}
