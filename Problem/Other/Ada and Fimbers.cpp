//https://www.spoj.com/problems/ADAFIMBR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e6 + 5;
const int F = 33;

int dp[N];
int f[F];
int freq[N];


int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        dp[i] = -1;
    }
    f[0] = 1, f[1] = 1;
    for (int i = 2; i < F; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        int ct = 0;
        for (int j = 0; j < F; j++) {
            if (i - f[j] < 0) {
                break;
            }
            freq[dp[i - f[j]]]++;
            while (freq[ct]) {
                ct++;
            }
        }
        dp[i] = ct;
        for (int j = 0; j < F; j++) {
            if (i - f[j] < 0) {
                break;
            }
            freq[dp[i - f[j]]]--;
        }
    }
    int t;
    cin >> t;
    int ans = 0;
    while (t--) {
        int n;
        cin >> n;
        ans ^= dp[n];
    }
    if (ans) {
        cout << "Ada" << endl;
    } else {
        cout << "Vinit" << endl;
    }
    return 0;
}
