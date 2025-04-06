//https://www.spoj.com/problems/TENALI/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const long long M = 1e9 + 7;

int phi[N];
vector<int> divs[N];

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

long long binomial(long long n, long long k) {
    long long ans = 1;
    for (int i = n; i > n - k; i--) {
        ans = ans * i % M;
    }
    for (int i = 1; i <= k; i++) {
        ans = ans * modPow(i, M - 2) % M;
    }
    return ans;
}

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        phi[i] = i;
	}
	for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
	}
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int g = __gcd(n, k);
        long long ans = 0;
        for (int d : divs[g]) {
            long long cur = phi[d] * binomial(n / d, k / d) % M;
            if (k % 2 == (k / d) % 2) {
                ans = (ans + cur) % M;
            } else {
                ans = (ans - cur + M) % M;
            }
        }
        cout << ans * modPow(n, M - 2) % M  << endl;
    }
    return 0;
}
