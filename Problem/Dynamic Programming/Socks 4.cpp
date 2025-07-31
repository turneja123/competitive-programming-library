//https://atcoder.jp/contests/abc412/tasks/abc412_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const ll M = 998244353;

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

int freq[N];
int pref[N];
long long dp[N];

ll s, inv;

ll calc(int i) {
    if (dp[i] != -1) {
        return dp[i];
    }
    ll ans = 0;
    for (int j = i + 1; j < N; j++) {
        if (freq[j]) {
            ans = (ans + calc(j) * j % M * freq[j] % M * inv % M) % M;
        }
    }
    ans = (ans + 1) * s % M * modPow(s - pref[i] + i, M - 2) % M;
    return dp[i] = ans;
}

int main() {
    IOS;
    int n, c;
    cin >> n >> c;
    c--;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
        if (c == i) {
            freq[a[i] + 1]++;
        } else {
            freq[a[i]]++;
        }
    }
    inv = modPow(s, M - 2);
    for (int i = 0; i < N; i++) {
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + freq[i] * i;
        dp[i] = -1;
    }
    cout << calc(a[c] + 1);
    return 0;
}
