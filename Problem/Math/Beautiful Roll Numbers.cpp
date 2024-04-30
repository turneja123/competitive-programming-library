//https://www.spoj.com/problems/NUMBERTH/
#pragma GCC optimize("Ofast")
#pragma GCC target ("sse4.2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;
const int N = 4e6;
const int M = 30;
const int Q = 1e4 + 5;

bitset<N> is_prime;
vector<int> primes;
vector<int> digits[Q];

int ind = 0;
long long pw[10];

gp_hash_table<long long, int> mp;

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
        for (int i = 0; i < block_size; i++) {
            block[i] = x[i % prod];
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
                    primes[ind++] = p;
                }
            }
        }
    }
    return;
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < 10; i++) {
        pw[i] = pw[i - 1] * 10;
    }
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int d = s.size(), bits = 1 << d;
        digits[i].resize(d);
        for (int j = 0; j < d; j++) {
            digits[i][j] = s[j] - '0';
        }
        for (int j = 1; j < bits; j++) {
            long long h = 0;
            for (int k = 0; k < d; k++) {
                int c = j & (1 << k);
                if (c != 0) {
                    long long a = digits[i][k];
                    h += pw[a] * (a + 1);
                }
            }
            mp[h] = 0;
        }
    }
    sieve(1e7);
    for (int i = 0; i < ind; i++) {
        long long h = 0;
        while(primes[i] > 0) {
            long long a = primes[i] % 10;
            h += pw[a] * (a + 1);
            primes[i] /= 10;
        }
        auto it = mp.find(h);
        if (it != mp.end()) {
            it->second++;
        }
    }
    for (int i = 0; i < n; i++) {
        long long ans = 0;
        int d = digits[i].size(), bits = 1 << d;
        set<long long> st;
        for (int j = 1; j < bits; j++) {
            long long h = 0;
            for (int k = 0; k < d; k++) {
                int c = j & (1 << k);
                if (c != 0) {
                    long long a = digits[i][k];
                    h += pw[a] * (a + 1);
                }
            }
            auto it = st.find(h);
            if (it == st.end()) {
                ans += mp[h];
                st.insert(h);
            }
        }
        cout << ans << endl;
    }



    return 0;
}
