//https://codeforces.com/contest/2104/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;

vector<int> primes;
vector<long long> pref_primes;
bool is_prime[N];

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int m = primes.size();
    pref_primes.resize(m);
    for (int i = 0; i < m; i++) {
        pref_primes[i] = (i == 0 ? primes[i] : pref_primes[i - 1] + primes[i]);
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end(), greater<int>());
        long long s = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            s += a[i];
            if (s >= pref_primes[i]) {
                ans = i + 1;
            }
        }
        cout << n - ans << endl;
    }

    return 0;
}
