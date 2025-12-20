//https://qoj.ac/contest/2509/problem/14101
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
ll M;

long long inv[N];
long long fact[N];
long long factinv[N];
ll ans[N];
long long cnt[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int n;

ll modul(ll x){
    return ((x % M) + M) % M;
}

ll imenilac = 1;

void doprinos(ll pro, ll sum, ll len){
    ll kome = pro - sum + len;
    if(kome >= 2 && kome <= n){
        ll val = fact[kome];
        val = modul(val * factinv[kome - len]);
        val = modul(val * imenilac);
        ans[kome] = modul(ans[kome] + val);
    }
}

void dfs(ll last, ll pro, ll sum, ll len){
    ll limit = n;
    if(pro != 1){
        limit = (n + sum - len - 1) / (pro - 1);
    }
    if(limit < last) return;
    for(int dodaj = last; dodaj <= limit; dodaj++){
        ll npro = pro * dodaj;
        ll nsum = sum + dodaj;
        ll nlen = len + 1;
        cnt[dodaj]++;
        imenilac = modul(imenilac * inv[cnt[dodaj]]);

        doprinos(npro, nsum, nlen);

        if(npro <= n + nsum - nlen){
            dfs(dodaj, npro, nsum, nlen);
        }

        imenilac = modul(imenilac * cnt[dodaj]);
        cnt[dodaj]--;
    }
}

int main() {
    IOS;
    cin >> n >> M;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }

    dfs(2, 1, 0, 0);

    //ll sum = 0;

    for (int i = 2; i <= n; i++) {
         cout << ans[i] << " ";
        //sum = modul(sum + ans[i]);
    }

    //cout << sum << endl;

    return 0;
}
