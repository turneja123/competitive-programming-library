//https://atcoder.jp/contests/ndpc/tasks/ndpc2026_l
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int D = 1000;
const long long M = 998244353;

vector<int> factors;
vector<int> expo;
vector<int> divs[N];


int spf[N];
bool is_prime[N];
ll dp[N];
ll ans[N];
ll inv[N];

int idx = 0;

pair<pair<int, int>, int> masks[D];

long long a[D];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
        for (int j = i; j < n; j += i) {
            divs[j].push_back(i);
        }
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

void factor(int n) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        n = n / p;
    }
    return;
}

void get_divs(int i, int cur, int mask, int h, int bit, vector<pair<int, int>> &f, vector<pair<int, int>> &v) {
    if (i == f.size()) {
        long long m = dp[cur];
        masks[idx++] = make_pair(make_pair(mask, h), cur);
        a[h] = m;

        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        v[i].first = f[i].first, v[i].second = j;
        get_divs(i + 1, cur, mask, h, bit + f[i].second, f, v);
        cur *= f[i].first;
        mask += 1 << (bit + j), h += expo[bit + j];
    }
    v[i] = make_pair(0, 0);
    return;
}

bool valid(int h, int i, int mask) {
    if (i != factors.size() - 1) {
        int c = mask & (1 << (i + 1));
        if (expo[i] == expo[i + 1] && c) {
            return false;
        }
    }
    return true;
}

int main() {
    IOS;
    sieve(N);
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }
    int n;
    cin >> n;
    for (int tt = 0; tt < n; tt++) {
        int x;
        cin >> x;
        factor(x);
        expo.resize(factors.size());
        vector<pair<int, int>> f;
        int i = 0, j = 0, m = factors.size(), d = 1;
        while (i < m) {
            int cur = factors[i];
            while (i < m && factors[i] == cur) {
                expo[i] = d;
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));
            d *= i - j + 1;
            j = i;
        }

        vector<pair<int, int>> v(f.size());
        get_divs(0, 1, 0, 0, 0, f, v);

        for (int i = 0; i < factors.size(); i++) {
            for (int k = 0; k < d; k++) {
                int j = masks[k].first.first, h = masks[k].first.second, c = j & (1 << i);
                if (c) {
                    int sub = h - expo[i];
                    if (valid(sub, i, j)) {
                        a[sub] = (a[sub] -  a[h] + M) % M;
                    }
                }
            }
        }

        for (int k = 0; k < d; k++) {
            int h = masks[k].first.second, g = masks[k].second;
            ans[x] += a[h] * x % M * inv[g] % M;
        }
        ans[x] %= M;
        if (tt != 0) {
            cout << ans[x] << endl;
        } else {
            ans[x] = 1;
        }
        factors.clear();
        idx = 0;
        for (int y : divs[x]) {
            dp[y] = (dp[y] + ans[x] * x) % M;
        }

    }

    return 0;
}
