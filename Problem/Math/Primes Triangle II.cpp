#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("lzcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 19;
const int N = 1e5 + 5;
const int M = 30;

bitset<N> is_prime;
vector<int> primes;
int ind = 0;

pair<int, int> queries[N];
pair<int, int> ans[N];

auto udiv = [](const uint32_t& a, const uint32_t& b) -> uint32_t {
    return (double)a / b + 1e-9;
};

void sieve(int n) {
    primes.resize(max(100, (int)(n / (log(n) * 0.9))));
    if (n >= 2) {
        primes[ind++] = 2;
    }
    if (n >= 3) {
        primes[ind++] = 3;
    }
    if (n >= 5) {
        primes[ind++] = 5;
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
            primes[ind++] = i;
        }
        vector<int> pos(8, 0);
        for (int t = 0; t < 8; ++t) {
            int j = (i <= K) ? i : i * i;
            while (j % M != iip[t]) {
                j += i << 1;
            }
            pos[t] = udiv(j, M);
        }
        sprimes.push_back(make_pair(i, pos));
    }
    vector<unsigned char> x(prod, 255);
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
    vector<unsigned char> block(block_size);

    for (int l = 0; l < (n + M - 1) / M; l += block_size) {
        int r = min((n + M - 1) / M, l + block_size);
        for (int i = 0, im = 0; i < block_size; i++, im++) {
            if (im == prod) {
                im = 0;
            }
            block[i] = x[im];
        }
        if (l == 0) {
            block[0] &= 254;
        }
        for (int p = pl; p < sprimes.size(); p++) {
            int i = sprimes[p].first;
            for (int t = 0; t < 8; ++t) {
                int j = sprimes[p].second[t];
                for (int jm = j - block_size * udiv(j, block_size); j < r; j += i, jm += i) {
                    if (jm > block_size) {
                        jm -= block_size;
                    }
                    block[jm] &= ~(1 << t);
                }
                sprimes[p].second[t] = j;
            }
        }
        for (int i = l, im = i % block_size; i < r; i++, im++) {
            if (im == block_size) {
                im = 0;
            }
            for (int m = block[im]; m > 0; m &= m - 1) {
                int p = i * M + iip[__builtin_ctz(m)];
                if (p <= n) {
                    primes[ind++] = p;
                }
            }
        }
    }
    return;
}

int main() {
    IOS;
    sieve(1e9);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries, queries + t);
    ind = 0; int x = 1, y = 1;
    for (int i = 0; i < primes.size(); i++) {
        while (ind < t && queries[ind].first < primes[i]) {
            ind++;
        }
        while (ind < t && queries[ind].first == primes[i]) {
            ans[queries[ind].second].first = y, ans[queries[ind].second].second = x;
            ind++;
        }
        x++;
        if (x > y) {
            y++, x = 1;
        }
    }
    for (int i = 0; i < t; i++) {
        if (ans[i].first == 0) {
            cout << -1 << endl;
        } else {
            cout << ans[i].first << " " << ans[i].second << endl;
        }
    }
    return 0;
}
