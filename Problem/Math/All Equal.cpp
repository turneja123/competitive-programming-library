//https://www.codechef.com/START166A/problems/ALLEQ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int D = 300;
const long long M = 998244353;

vector<int> factors;
vector<int> expo;

int spf[N];
bool is_prime[N];

int x, n;
int idx = 0;

pair<pair<int, int>, int> masks[D];

long long a[D];
long long pref[N];

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
        long long m = x / cur;
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
    int tt;
    cin >> tt;
    for (int t = 0; t < tt; t++) {
        int s;
        cin >> s >> x;
        long long tot = 0;
        if (s == 1) {
            tot = (tot + modPow(x, s) * x) % M;
            cout << tot << endl;
            continue;
        }
        for (n = 1; n <= x; n++) {
            if (n == 1) {
                tot = (tot + modPow(x, s)) % M;
                continue;
            }

            factor(n);
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

            //O(logn * n^(1/3)))
            for (int i = 0; i < factors.size(); i++) {
                for (int k = 0; k < d; k++) {
                    int j = masks[k].first.first, h = masks[k].first.second, c = j & (1 << i);
                    if (c) {
                        int sub = h - expo[i];
                        if (valid(sub, i, j)) {
                            a[sub] = (a[sub] - a[h] + M) % M;
                        }
                    }
                }
            }

            for (int k = 0; k < d; k++) {
                int h = masks[k].first.second, g = masks[k].second;
                tot = (tot + modPow(a[h], s)) % M;
            }
            idx = 0;
            factors.clear();
        }
        cout << tot << endl;
    }

    return 0;
}
