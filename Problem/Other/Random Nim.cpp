//https://www.codechef.com/problems/RANDOM_NIM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 7;

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
	int t;
	cin >> t;
	while (t--) {
        int n, d, sum = 0;
        cin >> n >> d;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            sum ^= a;
        }
        long long ans;
        if (sum > 0) {
            ans = (d + 1) * modPow(2 * d, M - 2) % M;
        } else {
            ans = (d - 1) * modPow(2 * d, M - 2) % M;
        }
        cout << ans << endl;
	}

	return 0;
}
