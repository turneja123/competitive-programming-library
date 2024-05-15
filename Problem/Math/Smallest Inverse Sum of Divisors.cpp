//https://www.spoj.com/problems/INVDIV/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e8 + 5;
const int SQ = 1e4 + 5;

int sum[N];
int ans[N];
int spf[SQ];
bool is_prime[SQ];
bool bad[N];

int main() {
	IOS;
	is_prime[2] = true;
	for (int i = 3; i < SQ; i += 2) {
        is_prime[i] = true;
	}
	int sq = sqrt(N);
	for (int i = 1; i < SQ; i++) {
        spf[i] = i;
	}
	for (int i = 1; i < SQ; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < SQ; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
	}
	for (int i = 1; i < N; i++) {
        ans[i] = N;
        sum[i] = i + 1;
        if (i < SQ && is_prime[i]) {
            for (int j = i * i, k = i; j < N; j += i, k++) {
                int r = j + k + i + 1;
                if (r >= N) {
                    bad[j] = true;
                }
            }
        }
	}
	ans[1] = 1;
    for (int i = 2; i < N; i++) {
        if (i <= sq) {
            int s = (2 * i) / spf[i], inc = i / spf[i];
            for (int j = 2 * i, k = 2; j < N; j += i, k++, s += inc) {
                if (j + spf[i] + s + 1 >= N) {
                    break;
                }
                if (sum[j] >= N) {
                    continue;
                }
                sum[j] += i;
                if (k > sq) {
                    sum[j] += k;
                }
            }
        }
        if (sum[i] < N && !bad[i]) {
            ans[sum[i]] = min(ans[sum[i]], i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n >= N || ans[n] == N) {
            cout << -1;
        } else {
            cout << ans[n];
        }
        cout << endl;
    }
	return 0;
}
