//https://codeforces.com/contest/2040/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e6 + 5;
const long long M = 998244353;

long long fact[N];
long long phi[N];
bool is_prime[N];
int spf[N];

vector<int> factors;

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

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

void factor(int n) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        n = n / p;
    }
    return;
}

void get_divs(int i, int cur,  vector<pair<int, int>> &f, vector<int> &v) {
    if (i == f.size()) {
        v.push_back(cur);
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {;
        get_divs(i + 1, cur, f, v);
        cur *= f[i].first;
    }
    return;
}


vector<int> calc(int n) {
    factor(n);
    vector<pair<int, int>> f;
    int i = 0, j = 0, m = factors.size(), d = 1;
    while (i < m) {
        int cur = factors[i];
        while (i < m && factors[i] == cur) {
            i++;
        }
        f.push_back(make_pair(factors[j], i - j));
        d *= i - j + 1;
        j = i;
    }
    vector<int> v;
    get_divs(0, 1, f, v);
    factors.clear();
    return v;
}

int main() {
    IOS;
    sieve(N);
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        phi[i] = i;
        fact[i] = fact[i - 1] * i % M;
	}

    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b, c, k;
        cin >> a >> b >> c >> k;
        vector<int> d(k);
        int g;
        for (int i = 0; i < k; i++) {
            cin >> d[i];
            g = (i == 0 ? d[i] : __gcd(g, d[i]));
        }
        vector<long long> ans(a * b * c + 1, 0);
        vector<int> da = calc(a), db = calc(b), dc = calc(c);

        for (int x : da) {
            long long lx = x;
            if (g % lx != 0) {
                continue;
            }
            for (int y : db) {
                long long ly = lx * y / __gcd(lx, (long long)y);
                if (g % ly != 0) {
                    continue;
                }
                for (int z : dc) {
                    long long lz = ly * z / __gcd(ly, (long long)z);
                    if (g % lz != 0) {
                        continue;
                    }
                    ans[lz] = (ans[lz] + phi[x] * phi[y] % M * phi[z] % M) % M;
                }
            }
        }
        long long tot = 0;
        for (int i = 1; i <= a * b * c; i++) {
            if (ans[i] != 0) {
                ans[i] = ans[i] * fact[a * b * c / i] % M;
                for (int j = 0; j < k; j++) {
                    ans[i] = ans[i] * modPow(fact[d[j] / i], M - 2) % M;
                }
                tot = (tot + ans[i]) % M;
            }
        }
        cout << tot * modPow(a * b * c, M - 2) % M << endl;
    }
    return 0;
}
