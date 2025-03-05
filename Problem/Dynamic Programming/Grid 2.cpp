//https://atcoder.jp/contests/dp/tasks/dp_y
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

long long dp[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> a;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(make_pair(x, y));
    }
    a.push_back(make_pair(n, m));
    sort(a.begin(), a.end(), comp);
    for (int i = 0; i <= q; i++) {
        auto [x, y] = a[i];
        dp[i] = binomial(x + y - 2, x - 1);
        for (int j = 0; j < i; j++) {
            auto [x1, y1] = a[j];
            dp[i] = (dp[i] - dp[j] * binomial(x + y - x1 - y1, x - x1) % M + M) % M;
        }
    }
    cout << dp[q];
    return 0;
}
