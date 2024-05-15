//https://www.spoj.com/problems/PRLCM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const __int128 M = 998244353;

long long freq[N];
__int128 sum[N];

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
	IOS;
	int n;
	cin >> n;
	__int128 ans = 0;
	for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
	}
    for (int i = 1; i < N; i++) {
        __int128 pref = 0;
        for (int j = i; j < N; j += i) {
            sum[i] += (__int128)j * pref * freq[j];
            sum[i] += (__int128)(freq[j] * (freq[j] - 1) / 2) * j * j;
            pref += (__int128)j * freq[j];
        }
    }
    for (int i = N - 1; i > 0; i--) {
        for (int j = 2 * i; j < N; j += i) {
            sum[i] -= sum[j];
        }
        ans += sum[i] / (__int128)i;
        ans %= M;
    }
    print(ans);
	return 0;
}
