//https://atcoder.jp/contests/abc349/tasks/abc349_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 1 << 14;
const long long M = 998244353;

int ct[K];
long long dp[K];
long long dp_next[K];
vector<long long> factors;

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
    int n; long long m;
    cin >> n >> m;
    long long t = m;
    for (long long i = 2; i <= sqrt(m); i++) {
        if (t % i == 0) {
            long long prod = 1;
            while (t % i == 0) {
                t /= i;
                prod *= i;
            }
            factors.push_back(prod);
        }
    }
    if (t > 1) {
        factors.push_back(t);
    }
    int k = factors.size(), bits = 1 << k;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (m % a != 0) {
            continue;
        }
        int mask = 0;
        for (int j = 0; j < k; j++) {
            if (a % factors[j] == 0) {
                mask += 1 << j;
            }
        }
        ct[mask]++;
    }
    for (int i = 0; i < bits; i++) {
        long long ways = modPow(2, ct[i]) - 1;
        for (int j = 0; j < bits; j++) {
            dp_next[i | j] = (dp_next[i | j] + ways * dp[j]) % M;
        }
        dp_next[i] = (dp_next[i] + ways) % M;
        for (int j = 0; j < bits; j++) {
            dp[j] = (dp[j] + dp_next[j]) % M;
            dp_next[j] = 0;
        }
    }
    cout << dp[bits - 1];


    return 0;
}
