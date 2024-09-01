//https://atcoder.jp/contests/arc167/tasks/arc167_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;

long long modPow(long long a, long long y) {
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

int main() {
    IOS;
    long long n, k;
    cin >> n >> k;
    vector<pair<long long, long long>> f;
    long long m = n;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (m % i == 0) {
            int ct = 0;
            while (m % i == 0) {
                m /= i;
                ct++;
            }
            f.push_back(make_pair(i, ct));
        }
    }
    if (m > 1) {
        f.push_back(make_pair(m, 1));
    }
    long long mn = 1e18, p = -1;
    for (int i = 0; i < f.size(); i++) {
        if (f[i].second < mn) {
            mn = f[i].second;
            p = f[i].first;
        }
    }
    long long d = (k % M * mn % M) * (k % M * mn % M + 1) % M * modPow(2, M - 2) % M;
    __int128 MOD = M * mn;
    __int128 d_m = ((__int128)k % MOD * (mn / 2) % MOD) * ((__int128)k % MOD * mn % MOD + 1) % MOD;
    for (int i = 0; i < f.size(); i++) {
        if (f[i].first != p) {
            d = d * (k % M * f[i].second % M + 1) % M;
            d_m = d_m * ((__int128)k % MOD * f[i].second % MOD + 1) % MOD;
        }
    }
    if (mn % 2 == 0) {
        d = (d - d_m % mn + M) % M * modPow(mn, M - 2) % M;
    } else {
        d = d * modPow(mn, M - 2) % M;
    }
    cout << d;

    return 0;
}
