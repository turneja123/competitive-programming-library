//https://atcoder.jp/contests/abc361/tasks/abc361_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long ans[60];

int main() {
	IOS;
	long long n;
	cin >> n;
	for (int i = 2; i < 60; i++) {
        long long l = 2, r = sqrt(n), mx = 1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            __int128 prod = 1;
            for (int j = 0; j < i; j++) {
                prod *= (__int128)mid;
                if (prod > n) {
                    break;
                }
            }
            if (prod <= n) {
                mx = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[i] = mx - 1;
	}
	long long tot = 0;
	for (int i = 60; i >= 2; i--) {
        for (int j = 2 * i; j < 60; j += i) {
            ans[i] -= ans[j];
        }
        tot += ans[i];

	}
	cout << tot + 1;
	return 0;
}
