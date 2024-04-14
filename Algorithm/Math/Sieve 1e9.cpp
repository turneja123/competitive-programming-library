//https://judge.yosupo.jp/problem/enumerate_primes
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;
const int N = 1e6;
const int M = 30;

bitset<N> is_prime;
vector<int> primes;

void sieve(int n) {
    if (n >= 2) {
        primes.push_back(2);
    }
    if (n >= 3) {
        primes.push_back(3);
    }
    if (n >= 5) {
        primes.push_back(5);
    }
    int iip[] = {1, 7, 11, 13, 17, 19, 23, 29};
    is_prime[2] = true;
    for (int i = 3; i < N; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i * i < N; i += 2){
        for (int j = i * i; is_prime[i] && j < N; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    int sq = sqrt(n);
    vector<pair<int, vector<int>>> sprimes;
    int prod = 1, pl = 0;
    for (int i = 7; i <= sq; i++) {
        if (!is_prime[i]) {
            continue;
        }
        if (i <= K) {
            prod *= i;
            pl++;
            primes.push_back(i);
        }
        vector<int> pos(8, 0);
        for (int t = 0; t < 8; ++t) {
            int j = (i <= K) ? i : i * i;
            while (j % M != iip[t]) {
                j += i << 1;
            }
            pos[t] = j / M;
        }
        sprimes.push_back(make_pair(i, pos));
    }
    vector<int> x(prod, 255);
    for (int p = 0; p < pl; p++) {
        int i = sprimes[p].first;
        vector<int> pos = sprimes[p].second;
        for (int t = 0; t < 8; ++t) {
            for (int j = pos[t]; j < prod; j += i) {
                x[j] &= ~(1 << t);
            }
        }
    }
    const int block_size = ((1 << K) + prod - 1) / prod * prod;
    vector<int> block(block_size);

    for (int l = 0; l < (n + M - 1) / M; l += block_size) {
        int r = min((n + M - 1) / M, l + block_size);
        for (int i = l; i < r; i++) {
            block[i - l] = x[(i - l) % prod];
        }
        if (l == 0) {
            block[0] &= 254;
        }
        for (int p = pl; p < sprimes.size(); p++) {
            int i = sprimes[p].first;
            for (int t = 0; t < 8; ++t) {
                int j = sprimes[p].second[t];
                for (; j < r; j += i) {
                    block[j % block_size] &= ~(1 << t);
                }
                sprimes[p].second[t] = j;
            }
        }
        for (int i = l; i < r; i++) {
            for (int m = block[i % block_size]; m > 0; m &= m - 1) {
                int p = i * M + iip[__builtin_ctz(m)];
                if (p <= n) {
                    primes.push_back(i * M + iip[__builtin_ctz(m)]);
                }
            }
        }
    }
    return;
}

int main() {
    IOS;
    int n, a, b;
    cin >> n >> a >> b;
    sieve(n);
    vector<int> ans;
    for (int i = b; i < primes.size(); i += a) {
        ans.push_back(primes[i]);
    }
    cout << primes.size() << " " << ans.size() << endl;
    for (int x : ans) {
        cout << x << " ";
    }
    return 0;
}
