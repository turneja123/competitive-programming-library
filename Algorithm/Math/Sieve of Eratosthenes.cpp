#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

vector<int> primes;

void sieve(int n) {
    bool composite[n] = { };
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
    int n;
    cin >> n;
    sieve(n);
    return 0;
}
