//https://codeforces.com/contest/1255/problem/E2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

bool is_prime[N];
vector<int> primes;

ll calc(vector<int> &a, ll m) {
    int n = a.size();
    ll ans = 0;
    for (int i = 0; i < n;) {
        vector<int> b;
        ll s = 0;
        while (i < n && s < m) {
            if (s + a[i] > m) {
                b.push_back(m - s);
                a[i] -= m - s;
                break;
            }
            s += a[i];
            b.push_back(a[i++]);
        }
        ll best = 1e18;
        ll ctl = 0, suml = 0, ctr = 0, sumr = 0;
        int k = b.size();
        for (int j = 0; j < k; j++) {
            ctr += b[j];
            sumr += (ll)j * b[j];
        }
        for (int j = 0; j < k; j++) {
            ctr -= b[j];
            sumr -= (ll)j * b[j];
            ctl += b[j];
            suml += (ll)j * b[j];

            best = min(best, ctl * j - suml + sumr - ctr * j);
        }
        ans += best;
    }
    return ans;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j < N; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    int n;
    cin >> n;
    ll s = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }
    if (s == 1) {
        cout << -1;
        return 0;
    }
    ll best = 1e18;

    ll t = s;
    for (int p : primes) {
        if (t % p == 0) {
            vector<int> b(n);
            for (int i = 0; i < n; i++) {
                b[i] = a[i] % p;
            }
            best = min(best, calc(b, p));
            while (t % p == 0) {
                t /= p;
            }
        }
    }
    if (t > 1) {
        best = min(best, calc(a, t));
    }

    cout << best;



    return 0;
}
