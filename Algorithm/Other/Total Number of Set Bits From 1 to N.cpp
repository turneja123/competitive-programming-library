//https://cses.fi/problemset/task/1146/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long bits(long long n, long long k) {
    long long ans = (n >> (k + 1)) << k;
    if ((n >> k) & (long long)1) {
        ans += n & (((long long)1 << k) - 1);
    }
    return ans;
}

int main() {
	IOS;
	long long n;
	cin >> n;
	long long ans = 0;
	for (int i = 0; i < 63; i++) {
        ans += bits(n + 1, i);
	}
	cout << ans;
	return 0;
}
