//https://www.codechef.com/problems/RCTEXSCC?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 998244353;

long long modPow(long long a, long long y) {
    a %= M;
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

ll dp[N][2]; //0 - isti, 1 - drugaciji

ll f(ll d, ll p, ll add, ll c) {
    return (d * p + c * add * p) % M;
}

int main() {
	IOS;
	int m, n, k;
	cin >> m >> n >> k;
	if (k == 1) {
        cout << 1 << endl;
        return 0;
	}
    if (m == 1) {
        ll ans = n;
        for (int i = 1; i < n; i++) {
            ans = (ans - modPow(k, M - 2) + M) % M;
        }
        cout << ans;
    } else {
        ll prob_eq = (ll)k * modPow((ll)k * k, M - 2) % M;
        ll prob_neq = (1 - prob_eq + M) % M;
        ll prob_exact = modPow((ll)k * k, M - 2);

        dp[1][0] = (ll)1 * prob_eq;
        dp[1][1] = (ll)2 * prob_neq;
        for (int i = 2; i <= n; i++) {
            //dod na iste
            dp[i][0] += f(dp[i - 1][0], prob_exact, 0, prob_eq);
            dp[i][0] += f(dp[i - 1][0], (prob_eq - prob_exact + M) % M, 1, prob_eq);
            dp[i][1] += f(dp[i - 1][0], (2 * prob_eq - 2 * prob_exact % M + M) % M, 1, prob_eq);
            dp[i][1] += f(dp[i - 1][0], (prob_neq - (2 * prob_eq - 2 * prob_exact % M + M) % M + M) % M, 2, prob_eq);

            //dod na drugacije
            dp[i][0] += f(dp[i - 1][1], 2 * prob_exact % M, 0, prob_neq);
            dp[i][0] += f(dp[i - 1][1], (prob_eq - 2 * prob_exact % M + M) % M, 1, prob_neq);
            dp[i][1] += f(dp[i - 1][1], prob_exact, 0, prob_neq);
            dp[i][1] += f(dp[i - 1][1], (2 * prob_eq - 4 * prob_exact % M + M) % M, 1, prob_neq);
            dp[i][1] += f(dp[i - 1][1], (prob_neq - (2 * prob_eq - 3 * prob_exact % M + M) % M + M) % M, 2, prob_neq);

            dp[i][0] %= M;
            dp[i][1] %= M;
        }
        cout << (dp[n][0] + dp[n][1]) % M;
    }
	return 0;
}
