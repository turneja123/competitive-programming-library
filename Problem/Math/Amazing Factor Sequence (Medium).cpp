//https://www.spoj.com/problems/AFS2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

__int128 sum(__int128 n) {
    return n * (n + 1) / 2;
}

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        long long n, sq;
        cin >> n;
        sq = sqrt(n);
        __int128 ans = 0;
        for (int i = 1; i <= sq; i++) {
            ans += (__int128)i * (n / i) + sum(n / i) - sum(sq);
        }
        ans -= sum(n);
        print(ans);
        putchar('\n');
	}
	return 0;
}
