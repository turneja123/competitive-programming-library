//https://www.spoj.com/problems/KPRIMES2/
#pragma GCC target ("sse4.2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 18;
const int N = 6e4;
const int M = 30;

bitset<N> is_prime;
vector<int> primes;
int ind = 0;
int q = 0;
vector<pair<int, int>> queries;
vector<int> ans;

void mark_query(int p) {
    if (q >= queries.size()) {
        return;
    }
    if (queries[q].first == ind) {
        ans[queries[q].second] = p;
        q++;
    }
}

void sieve(int n) {
    if (n >= 2) {
        mark_query(2);
        ind++;
    }
    if (n >= 3) {
        mark_query(3);
        ind++;
    }
    if (n >= 5) {
        mark_query(5);
        ind++;
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
    vector<int> pos(8, 0);
    int prod = 1, pl = 0;
    for (int i = 7; i <= sq; i++) {
        if (!is_prime[i]) {
            continue;
        }
        if (i <= K) {
            prod *= i;
            pl++;
            mark_query(i);
            ind++;
        }
        for (int t = 0; t < 8; ++t) {
            int j = (i <= K) ? i : i * i;
            while (j % M != iip[t]) {
                j += i << 1;
            }
            pos[t] = j / M;
        }
        sprimes.push_back(make_pair(i, pos));
    }
    vector<unsigned char> x(prod, 255);
    for (int p = 0; p < pl; p++) {
        int i = sprimes[p].first;
        vector<int> pos = sprimes[p].second;
        for (int t = 0; t < 8; ++t) {
            for (int j = pos[t]; j < prod; j += i) {
                x[j] &= (unsigned char)(~(1 << t));
            }
        }
    }
    const int block_size = ((1 << K) + prod - 1) / prod * prod;
    vector<unsigned char> block(block_size);

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
                    block[j % block_size] &= (unsigned char)(~(1 << t));
                }
                sprimes[p].second[t] = j;
            }
        }
        for (int i = l; i < r; i++) {
            int m = block[i % block_size];
            if (q == queries.size() || __builtin_popcount(m) + ind < queries[q].first) {
                ind += __builtin_popcount(m);
            } else {
                for (; m > 0; m &= m - 1) {
                    int p = i * M + iip[__builtin_ctz(m)];
                    mark_query(p);
                    ind++;
                }
            }
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    queries.resize(t);
    ans.resize(t);
    for (int i = 0; i < t; i++) {
        int a;
        cin >> a;
        queries[i] = make_pair(a - 1, i);
    }
    sort(queries.begin(), queries.end());
    sieve(1e9);
    for (int i = 0; i < t; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
