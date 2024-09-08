//https://www.spoj.com/problems/LCMP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;
const int SQ = 350;
const int K = 17;
const long long M = 1e9 + 7;

bool is_prime[N];
int spf[N];
int a[N];
int pos[N];
int val[70][N];
int freq[N];

long long ans[N];
long long inv[N];

vector<int> primes;

int table[70][K][N];
long long pw[32][70];

vector<tuple<int, int, int, int>> queries;

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

void build(int n, int m) {
    for (int i = 1; i <= n; i++) {
        table[m][0][i] = val[m][i - 1];
    }
    for (int k = 1; k < 17; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[m][k][i] = max(table[m][k - 1][i], table[m][k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r, int m) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[m][k][l], table[m][k][r - (1 << k) + 1]);
}

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
        inv[i] = modPow(i, M - 2);
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            pos[i] = primes.size();
            primes.push_back(i);
            if (i < SQ) {
            }
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

bool comp(tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
    int block1 = get<0>(a) / 225;
    int block2 = get<0>(b) / 225;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

int main() {
    IOS;
    sieve(N);
    for (int i = 0; i < 70; i++) {
        pw[0][i] = 1;
        for (int j = 1; j < 32; j++) {
            pw[j][i] = pw[j - 1][i] * primes[i];
            if (pw[j][i] > N) {
                break;
            }
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int t = a[i];
        while (t > 1) {
            int p = spf[t], e = 0;
            while (t % p == 0) {
                e++;
                t /= p;
            }
            if (p < SQ) {
                val[pos[p]][i] = e;
            }
        }
    }
    for (int i = 0; i < 70; i++) {
        build(n, i);
    }
    int last = 1;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            cin >> last;
        } else {
            int l, r;
            cin >> l >> r;
            int pos = queries.size();
            ans[pos] = 1;
            for (int j = 0; j < 70; j++) {
                if (primes[j] == last) {
                    continue;
                }
                int e = query(l, r, j);
                ans[pos] = ans[pos] * pw[e][j] % M;
            }
            queries.push_back(make_tuple(l - 1, r - 1, last, pos));
        }
    }
    sort(queries.begin(), queries.end(), comp);
    int l = 0, r = -1;
    long long prod = 1;
    for (int i = 0; i < n; i++) {
        while (spf[a[i]] < SQ) {
            a[i] /= spf[a[i]];
            if (a[i] == 1) {
                break;
            }
        }
    }
    for (int i = 0; i < queries.size(); i++) {
        int cur = get<3>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int last = get<2>(queries[i]);
        while (r < rq) {
            r++;
            freq[a[r]]++;
            if (freq[a[r]] == 1) {
                prod = prod * a[r] % M;
            }
        }
        while (r > rq) {
            freq[a[r]]--;
            if (freq[a[r]] == 0) {
                prod = prod * inv[a[r]] % M;
            }
            r--;
        }
        while (l < lq) {
            freq[a[l]]--;
            if (freq[a[l]] == 0) {
                prod = prod * inv[a[l]] % M;
            }
            l++;
        }
        while (l > lq) {
            l--;
            freq[a[l]]++;
            if (freq[a[l]] == 1) {
                prod = prod * a[l] % M;
            }
        }
        ans[cur] = ans[cur] * prod % M;
        if (freq[last] > 0) {
            ans[cur] = ans[cur] * inv[last] % M;
        }
    }
    for (int i = 0; i < queries.size(); i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
