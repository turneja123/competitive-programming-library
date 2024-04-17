//solution for https://www.spoj.com/problems/ASUMEXTR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;
const long long M = 1234567891;

long long fl[N];
long long fr[N];
long long inv[N];

long long pow(long long a, long long b) {
    a %= M, b %= M;
    long long r = 1;
    for(; b; a = a * a % M, b >>= 1) {
        if (b & 1) {
            r = r * a % M;
        }
    }
    return r;
}

pair<long long, long long> calc(long long n, long long k) {
    long long ansl = 0;
    long long ansr = 0;
    if (n <= k + 2) {
        for (long long i = 1; i <= n; ++i) {
            long long p = pow(i, k);
            ansl = (ansl + p) % M;
            p *= i, p %= M;
            ansr = (ansr + p) % M;
        }
    } else {
		fl[0] = 0, fr[0] = 0, inv[0] = 0, inv[1] = 1;
		for (long long i = 1; i <= k + 2; ++i) {
            long long p = pow(i, k);
            fl[i] = (fl[i - 1] + p) % M;
            p *= i, p %= M;
            fr[i] = (fr[i - 1] + p) % M;
		}
		for (long long i = 2; i <= k + 2; ++i) {
            inv[i] = M / i * (M - inv[M % i]) % M;
		}
		long long l = 1;
		for (long long i = 1; i <= k + 1; ++i) {
            l = (M - l * ((n - i) % M) % M) * inv[i] % M;
		}
		long long r = (M - l * ((n - k - 2) % M) % M) * inv[k + 2] % M;
		for (long long i = 1; i <= k + 1; ++i) {
            long long p = pow(n - i, M - 2);
            l = l * (M - k - 2 + i) % M * inv[i] % M * ((n - i + 1) % M) % M * p % M, ansl = (ansl + l * fl[i]) % M;
            r = r * (M - k - 3 + i) % M * inv[i] % M * ((n - i + 1) % M) % M * p % M, ansr = (ansr + r * fr[i]) % M;
		}
		r = r * (M - 1) % M * inv[k + 2] % M * ((n - k - 1) % M) % M * pow(n - k - 2, M - 2) % M, ansr = (ansr + r * fr[k + 2]) % M;
	}
	return {ansl, ansr};
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        pair<long long, long long> ans = calc(n, k);
        cout << (long long)(((((n + 1) % M) * ans.first) % M - ans.second + M) % M) << endl;

    }

    return 0;
}
