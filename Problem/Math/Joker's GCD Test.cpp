//https://toph.co/p/joker-s-gcd-test
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

int phi[N];
long long dp[N];
vector<int> divs[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        phi[i] = i;
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
    int n, q;
    cin >> n;
    long long sum = 0, ct = (ll)n * (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int d : divs[a]) {
            sum += (ll)dp[d] * phi[d];
            dp[d]++;
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, a;
        cin >> t >> a;
        if (t == 1) {
            for (int d : divs[a]) {
                sum += dp[d] * phi[d];
                dp[d]++;
            }
            ct += n;
            n++;
        } else {
            for (int d : divs[a]) {
                dp[d]--;
                sum -= dp[d] * phi[d];
            }
            n--;
            ct -= n;
        }
        cout << (sum % M) * modPow(ct % M, M - 2) % M << endl;
    }
    return 0;
}
