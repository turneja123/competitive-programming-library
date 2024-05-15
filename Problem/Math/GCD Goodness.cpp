//https://www.spoj.com/problems/GCDGOOD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

long long freq[N];
long long sum[N];
long long pw[N];

int main() {
	IOS;
	int n;
	cin >> n;
	long long ans = 0;
	for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
        pw[i] = ((i == 0) ? 1 : pw[i - 1] * 2 % M);
	}
    for (int i = 1; i < N; i++) {
        long long ct = 0;
        for (int j = i; j < N; j += i) {
            sum[i] = (sum[i] + freq[j] * j) % M;
            ct += freq[j];
        }
        sum[i] = sum[i] * pw[ct - 1] % M;
    }
    for (int i = N - 1; i > 0; i--) {
        for (int j = 2 * i; j < N; j += i) {
            sum[i] = (sum[i] - sum[j] + M) % M;
        }
        ans = (ans + sum[i] * i) % M;
    }
    cout << ans;
	return 0;
}
