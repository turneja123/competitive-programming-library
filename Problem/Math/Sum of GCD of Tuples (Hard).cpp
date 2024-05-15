//https://atcoder.jp/contests/abc162/tasks/abc162_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long ct[N];

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

int main() {
	IOS;
	int n, k;
	cin >> n >> k;
	long long ans = 0;
    for (int i = 1; i <= k; i++) {
        ct[i] = modPow(k / i, n, M);
    }
    for (int i = k; i > 0; i--) {
        for (int j = 2 * i; j <= k; j += i) {
            ct[i] = (ct[i] - ct[j] + M) % M;
        }
        ans = (ans + ct[i] * i) % M;
    }
    cout << ans;
	return 0;
}
