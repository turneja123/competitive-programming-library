//solution for https://cses.fi/problemset/task/2417/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int M = 1e3 + 5;

vector <int> primes;
vector <int> v[N];
unordered_map <int, int> mp;

int a[N];

void eratosten(int n) {
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
    eratosten(M);
    ll n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int temp = a[i];
        for (int j = 0; j < primes.size(); j++) {
            if (temp % primes[j] == 0) {
                v[i].push_back(primes[j]);
                while (temp % primes[j] == 0) {
                    temp /= primes[j];
                }
            }
        }
        if (temp > 1) {
            v[i].push_back(temp);
        }
    }

    for (int i = 0; i < n; i++) {
        int pw = 1 << v[i].size();
        for (int j = 1; j < pw; j++) {
            int p = 1;
            for (int k = 0; k < v[i].size(); k++) {
                if (j & (1 << k)) {
                    p *= v[i][k];
                }
            }
            auto it = mp.find(p);
            if (it == mp.end()) {
                mp.insert({p, 1});
            } else {
                it->second++;
            }
        }
    }
    ll tot = n * (n - 1) / 2;
    ll diff = 0;
    for (int i = 0; i < n; i++) {
        int pw = 1 << v[i].size();
        for (int j = 1; j < pw; j++) {
            int p = 1;
            int bits = 0;
            for (int k = 0; k < v[i].size(); k++) {
                if (j & (1 << k)) {
                    p *= v[i][k];
                    bits++;
                }
            }
            auto it = mp.find(p);
            if (bits % 2 == 1) {
                diff += it->second - 1;
            } else {
                diff -= it->second - 1;
            }
        }
    }
    diff /= 2;
    cout << tot - diff;
    return 0;

}
