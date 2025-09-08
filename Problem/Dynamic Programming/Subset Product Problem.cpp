//https://atcoder.jp/contests/arc205/tasks/arc205_e
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 20;
const int N = 4e5 + 5;
const ll M = 998244353;

int a[N];

long long dp_initial[1 << K];
long long dp[1 << K];

void rebuild() {
    int bits = 1 << K;
    for (int j = 0; j < bits; j++) {
        dp[j] = dp_initial[j];
    }
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < bits; j++) {
            int c = j & (1 << k);
            if (c) {
                dp[j] = (dp[j] * dp[j ^ (1 << k)]) % M;
            }
        }
    }

}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int bits = 1 << K;
    for (int i = 0; i < bits; i++) {
        dp_initial[i] = 1;
        dp[i] = 1;
    }
    vector<int> buffer;
    for (int i = 0; i < n; i++) {
        buffer.push_back(a[i]);
        if (buffer.size() > 2000) {
            for (int x : buffer) {
                dp_initial[x] = dp_initial[x] * x % M;
            }
            buffer.clear();
            rebuild();
        }
        ll ans = 1;
        for (int &x : buffer) {
            int j = a[i] | x;
            if (j == a[i]) {
                ans = ans * x % M;
            }
        }
        cout << dp[a[i]] * ans % M << endl;
    }


    return 0;
}
