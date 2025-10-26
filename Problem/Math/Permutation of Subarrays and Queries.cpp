//https://eolymp.com/en/problems/12256
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const ll M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

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

ll s3(ll n) {
    return n * (n + 1) % M * (n + 2) % M * inv[6] % M;
}

int main() {
	IOS;
	fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, q;
    cin >> n >> q;
    ll prod = 1, s = 0;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s = (s + a + M) % M;
        prod = prod * fact[mp[a]] % M;
        mp[a]++;
        prod = prod * factinv[mp[a]] % M;
    }
    ll ans = fact[n] * prod % M * s % M * s3(n) % M * inv[n] % M;
    cout << ans << " ";
    for (int i = 0; i < q; i++) {
        char c; int a;
        cin >> c >> a;
        int z = (c == '+' ? 1 : -1);
        s = (s + z * ((a + M) % M) + M) % M;
        prod = prod * fact[mp[a]] % M;
        mp[a] += z;
        prod = prod * factinv[mp[a]] % M;
        n += z;
        ll ans = fact[n] * prod % M * s % M * s3(n) % M * inv[n] % M;
        cout << ans << " ";
    }

	return 0;
}
