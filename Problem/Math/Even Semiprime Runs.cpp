//https://www.spoj.com/problems/EVENSEMIP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = 1e7 + 5;
vector<char> is_prime(P, false);
vector<long long> primes{2};

auto udiv = [](const uint64_t& a, const uint32_t& b) -> uint64_t {
    return (double)a / b + 1e-9;
};

void segmentedSieve(long long l, long long r) {
    vector<int> factors(r - l + 1, 0);
    vector<long long> a(r - l + 1);
    for (int i = 0; i < r - l + 1; i++) {
        a[i] = l + i;
    }
    for (long long i : primes) {
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i) {
            while (factors[j - l] <= 2 && a[j - l] % i == 0) {
                a[j - l] = udiv(a[j - l], i);
                factors[j - l]++;
            }
        }
    }
    vector<long long> cur, ans;
    for (int i = 0; i < r - l + 1; i++) {
        if (a[i] > 1) {
            factors[i]++;
        }
        if (factors[i] == 2) {
            if ((l + i) % 2 == 1) {
                cur.clear();
            } else {
                cur.push_back(l + i);
                if (cur.size() > ans.size()) {
                    ans = cur;
                }
            }
        }
    }
    cout << ans.size() << endl;
    for (long long p : ans) {
        cout << p << " ";
    }
    cout << endl;
    return;
}

int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i < P; i += 2){
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (long long j = (long long)i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long l, r;
        cin >> l >> r;
        segmentedSieve(l, r);
    }

    return 0;
}
