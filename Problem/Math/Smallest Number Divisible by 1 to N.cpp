//https://www.spoj.com/problems/SMALLM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 16;
const int N = 1e4 + 5;
const int L = 1e8 + 5;
const int M = 30;

bitset<N> is_prime;
vector<int> primes;

long long ans[N * 10];
pair<int, int> queries[N * 10];

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
    int n; long long m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries, queries + n);
    int mx = queries[n - 1].first;
    sieve(mx + 5);
    int sq = sqrt(mx + 5);
    long long prod = 1; int j = 0;
    priority_queue<pair<long long, long long>> pq;
    for (int i = 0; i < n; i++) {
        long long k = queries[i].first;
        while (j < primes.size() && primes[j] <= k) {
            long long pw = primes[j];
            while (pw <= k) {
                pw *= primes[j];
            }
            prod *= (pw / primes[j]);
            prod %= m;
            if (primes[j] <= sq && pw <= mx) {
                pq.push(make_pair(-pw, primes[j]));
            }
            j++;
        }
        while (pq.size() && -pq.top().first <= k) {
            long long pw = -pq.top().first, pr = pq.top().second;
            pq.pop();
            while (pw <= k) {
                pw *= pr;
                prod *= pr;
            }
            prod %= m;
            if (pw <= mx) {
                pq.push(make_pair(-pw, pr));
            }
        }
        ans[queries[i].second] = prod;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
