//https://codeforces.com/contest/594/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 1e6 + 5;
const long long M = 1e9 + 7;

int spf[K];
int it[K];
bool is_prime[K];
vector<int> pos[K];

tuple<int, int, int> queries[N];

int a[N];
long long pref_pe[N];
long long pref_p[N];
long long ans[N];

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

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 1);
    }

    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] = t[i] * val % M;
        }
    }
    long long query(int i) {
        long long ans = 1;
        for (; i >= 1; i -= (i & -i)) {
            ans = ans * t[i] % M;
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) * modPow(query(l - 1), M - 2) % M;
    }
};


int main() {
    IOS;
    sieve(K);
    int n, q;
    cin >> n;
    BIT t(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i == 0) {
            pref_p[i] = 1;
            pref_pe[i] = 1;
        } else {
            pref_p[i] = pref_p[i - 1];
            pref_pe[i] = pref_pe[i - 1];
        }
        int m = a[i];
        while (m > 1) {
            int p = spf[m], pe = 1;
            while (m % p == 0) {
                pe *= p;
                m /= p;
            }
            pref_p[i] = pref_p[i] * p % M;
            pref_pe[i] = pref_pe[i] * pe % M;
            pos[p].push_back(i);
            if (pos[p].size() == 1) {
                t.upd(i + 1, modPow(p, M - 2) * (p - 1) % M);
            }
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_tuple(l, r, i);
    }
    sort(queries, queries + q);
    for (int i = 0, l = 0; i < q; i++) {
        auto [lf, rt, ind] = queries[i];
        while (l < lf) {
            int m = a[l];
            while (m > 1) {
                int p = spf[m];
                while (m % p == 0) {
                    m /= p;
                }
                it[p]++;
                if (it[p] < pos[p].size()) {
                    int j = pos[p][it[p]];
                    t.upd(j + 1, modPow(p, M - 2) * (p - 1) % M);
                }
            }
            l++;
        }
        ans[ind] = pref_pe[rt] * (lf == 0 ? 1 : modPow(pref_pe[lf - 1], M - 2)) % M * t.query(lf + 1, rt + 1) % M;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
