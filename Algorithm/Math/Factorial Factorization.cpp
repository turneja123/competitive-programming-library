#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 7;

bool composite[N];
vector <ll> primes;

void eratosten(int n) {
    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= n; j += i) {
                composite[j] = true;
            }
        }
    }
}

int main() {
    IOS;
    eratosten(N);
    int n;
    cin >> n;
    int *ct = (int *)malloc(sizeof(int) * primes.size());
    for (int i = 0; i < primes.size(); i++) {
        ll ctcur = 0;
        ll cur = primes[i];
        while (cur <= n) {
            ctcur += n / cur;
            cur *= primes[i];
        }
        ct[i] = ctcur;
    }
    bool first = true;
    for (int i = 0; i < primes.size(); i++) {
        if (ct[i] > 0) {
            if (!first) {
                cout << "* ";
            }
            cout << primes[i] << "^" << ct[i] << " ";
            first = false;
        }
    }
    return 0;
}
