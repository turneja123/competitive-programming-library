//https://codeforces.com/contest/1292/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5001;

int freq[N];
ll pref[N];
bool is_prime[N];
int spf[N];
int len[N];
int pw[N][N];

vector<int> del[N];
vector<int> primes;

ll calc(int l, int r, int i, int n) {
    if (i == -1) {
        return 0;
    }
    ll ans = 0;
    int p = primes[i];
    int lt = l;
    ll add = 0;
    while (l <= r) {
        int e = pw[l][p], l_nx;
        auto it = upper_bound(del[p].begin(), del[p].end(), l);
        if (it == del[p].end()) {
            l_nx = r;
        } else {
            l_nx = min(r, *it - 1);
        }
        add += (ll)2 * e * (pref[l_nx] - pref[l - 1]);
        ans = max(ans, add + (ll)2 * e * (pref[r] - pref[l_nx]) - (ll)n * e + calc(l, l_nx, i - 1, n));

        l = l_nx + 1;

    }
    return ans;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
        spf[i] = i;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                spf[j] = min(spf[j], i);
                is_prime[j] = 0;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        len[i] = len[i - 1];
        for (int j = 0; j <= i; j++) {
            pw[i][j] = pw[i - 1][j];
        }
        int n = i;
        while (n > 1) {
            int p = spf[n];
            del[p].push_back(i);
            while (n % p == 0) {
                len[i]++;
                n /= p;
                pw[i][p]++;
            }
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    ll mx = 0, ans = 0;
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + freq[i];
        ans += (ll)len[i] * freq[i];
    }

    for (int i = 0; i < primes.size(); i++) {
        int l = del[primes[i]][0];
        int r = (i == primes.size() - 1 ? 5000 : del[primes[i + 1]][0] - 1);
        mx = max(mx, calc(l, r, i, n));
    }
    cout << ans - mx;


    return 0;
}
