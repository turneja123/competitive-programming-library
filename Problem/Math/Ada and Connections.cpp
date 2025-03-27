//https://www.spoj.com/problems/ADACON/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

int spf[N];
bool is_prime[N];
bool seen[N];

int ans = N;
int ct = 0;
vector<int> a;

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}


void calc(int x, int n) {
    ct++;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int m = a[i] % x;
        cur += min(m, x - m);
        if (cur >= ans) {
            return;
        }
    }
    ans = cur;
    return;
}

void go(int x, int n) {
    while (x > 1) {
        if (!seen[spf[x]]) {
            calc(spf[x], n);
            seen[spf[x]] = true;
        }
        x /= spf[x];
    }
    return;
}

int main() {
    IOS;
    sieve(N);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0) {
            a.push_back(x);
        }
    }
    n = a.size();
    if (!n) {
        cout << 2;
        return 0;
    }
    calc(2, n);
    seen[2] = true;
    for (int i = 0; i < N; i++) {
        int j = a[generator() % n];
        go(j - 1, n);
        go(j, n);
        go(j + 1, n);
        if (ct > 100) {
            break;
        }
    }
    cout << ans;
    return 0;
}
