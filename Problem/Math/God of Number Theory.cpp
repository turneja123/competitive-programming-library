//https://www.spoj.com/problems/NUMG/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int INF = 2e9;
bool flag = false;

long long modPow(long long a, long long y, const long long M) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int prime_power(int p, int i, int k, int b) {
    if (__gcd(b, p) != 1) {
        return __gcd(b, p) / i;
    }
    int phi = p - p / i;
    int g = __gcd(k, phi);
    if (modPow(b, phi / g, p) != 1) {
        return 0;
    }
    flag = true;
    return g;
}

int calc(int k, int b, int n) {
    if (k == 1) {
        return 1;
    }
    vector<pair<int, int>> f;
    int ans = 1, t = n;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            int p = 1, ct = 0;
            while (n % i == 0) {
                p *= i;
                n /= i;
                ct++;
            }
            ans *= prime_power(p, i, k, b);
            f.push_back(make_pair(i, ct / k + ((ct % k) == 0 ? 0 : 1)));
        }
    }
    if (n > 1) {
        ans *= prime_power(n, n, k, b);
        f.push_back(make_pair(n, 1));
    }
    if (b == 0) {
        int prod = 1;
        for (int i = 0; i < f.size(); i++) {
            prod *= modPow(f[i].first, f[i].second, INF);
        }
        return t / prod;
    }
    if (!flag) {
        return 0;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int k, b, n;
        cin >> k >> b >> n;
        n = 2 * n + 1;
        cout << calc(k, b % n, n) << endl;
    }
/*
1
50 421875 492187*/
    return 0;
}
