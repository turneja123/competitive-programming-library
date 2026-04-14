//https://codeforces.com/contest/1436/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;
const int N = 1e5 + 5;

struct Info {
    ll ct;
    ll n;
    ll s;
    ll ns;
    ll s2;
    ll ns2;
    Info() {
        ct = 0;
        n = 0;
        s = 0;
        ns = 0;
        s2 = 0;
        ns2 = 0;
    }
};

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

int freq[N];
ll pw[N];
ll inv[N];
Info dp[N];



int main() {
    IOS;
    inv[2] = modPow(2, M - 2), inv[4] = modPow(4, M - 2), inv[8] = modPow(8, M - 2);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a, f;
        cin >> a >> f;
        freq[a] = f;
        pw[a] = modPow(2, f);
    }
    for (int i = 1; i < N; i++) {
        dp[i].ct = 1;
        for (ll j = i; j < N; j += i) {
            if (freq[j] == 0) {
                continue;
            }
            Info nx;
            ll f = freq[j];
            ll c0 = pw[j];
            ll c1 = f * c0 % M * inv[2] % M;
            ll c2 = f * ((f + 1) % M) % M * c0 % M * inv[4] % M;
            ll c3 = f * f % M * ((f + 3) % M) % M * c0 % M * inv[8] % M;
            nx.ct = dp[i].ct * c0 % M;
            nx.n = (dp[i].n * c0 + dp[i].ct * c1) % M;
            nx.s = (dp[i].s * c0 + j * dp[i].ct % M * c1) % M;
            nx.ns = (dp[i].ns * c0 + dp[i].s * c1 + j * dp[i].n % M * c1 + j * dp[i].ct % M * c2) % M;
            nx.s2 = (dp[i].s2 * c0 + 2 * j % M * dp[i].s % M * c1 + j * j % M * dp[i].ct % M * c2) % M;
            nx.ns2 = (dp[i].ns2 * c0 + 2 * j % M * dp[i].ns % M * c1 + j * j % M * dp[i].n % M * c2 + dp[i].s2 * c1 + 2 * j % M * dp[i].s % M * c2 + j * j % M * dp[i].ct % M * c3) % M;
            dp[i] = nx;
        }
    }
    for (int i = N - 1; i > 0; i--) {
        for (int j = 2 * i; j < N; j += i) {
            dp[i].s2 = (dp[i].s2 - dp[j].s2 + M) % M;
            dp[i].ns2 = (dp[i].ns2 - dp[j].ns2 + M) % M;
        }
    }
    cout << (dp[1].ns2 - dp[1].s2 + M) % M;

    return 0;
}
