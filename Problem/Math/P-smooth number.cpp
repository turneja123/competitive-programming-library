//https://atcoder.jp/contests/abc300/tasks/abc300_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e7;

int lpf[N];
int val[N];

vector<int> primes;
vector<int> v[30];

ll ans = 0;

int f(int n, int k) {
    if (k == -1) {
        return 1;
    }
    return upper_bound(v[k].begin(), v[k].end(), n) - v[k].begin();
}

void calc(int i, ll n, ll prod) {
    if (i == -1) {
        ans++;
        return;
    }

    while (1) {
        if (n / prod >= N) {
            calc(i - 1, n, prod);
        }
        if (prod * primes[i] > n) {
            return;
        }
        prod *= primes[i];
        if (n / prod < N) {
            ans += f(n / prod, i - 1);
        }
    }

}

int main() {
    IOS;
    ll n; int p;
    cin >> n >> p;

    for (int i = 1; i < N; i++) {
        val[i] = i;
    }

    for (int i = 2; i <= p; i++) {
        if (val[i] == i) {
            lpf[i] = primes.size();
            val[i] /= i;
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                while (val[j] % i == 0) {
                    val[j] /= i;
                }
                lpf[j] = primes.size() - 1;
            }
        }
    }

    for (int i = 1; i < N; i++) {
        if (val[i] == 1) {
            for (int j = lpf[i]; j < primes.size(); j++) {
                v[j].push_back(i);
            }
        }
    }
    int m = primes.size();
    if (n < N) {
        cout << f(n, m - 1);
        return 0;
    }

    calc(m - 1, n, 1);
    cout << ans;
    return 0;
}
