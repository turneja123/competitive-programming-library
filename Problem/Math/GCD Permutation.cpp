//https://atcoder.jp/contests/abc230/tasks/abc230_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int p[N];

const int D = 300;

vector<int> factors;
vector<int> expo;

int spf[N];
bool is_prime[N];

int n;
int idx = 0;

pair<pair<int, int>, int> masks[D];

long long a[D];
long long ct[N];
long long ans[N];

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
        ct[cur]++;
        long long m = ct[cur];
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

void reset_divs(int i, int cur, vector<pair<int, int>> &f, vector<pair<int, int>> &v) {
    if (i == f.size()) {
        ct[cur] = 0;
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        v[i].first = f[i].first, v[i].second = j;
        reset_divs(i + 1, cur, f, v);
        cur *= f[i].first;
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
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> p[i];
    }
    for (int ii = 2; ii <= m; ii++) {
        for (int jj = ii; jj <= m; jj += ii) {
            n = p[jj];
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
                            a[sub] -= a[h];
                        }
                    }
                }
            }
            for (int k = 0; k < d; k++) {
                int h = masks[k].first.second, g = masks[k].second;
                if (g != 1) {
                    ans[ii] += a[h];
                }
            }
            factors.clear();
            idx = 0;
        }
        for (int jj = ii; jj <= m; jj += ii) {
            n = p[jj];
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
            reset_divs(0, 1, f, v);
            factors.clear();
            idx = 0;
        }
    }
    long long sum = 0;
    for (int i = m; i >= 2; i--) {
        for (int j = 2 * i; j <= m; j += i) {
            ans[i] -= ans[j];
        }
        sum += ans[i];
    }
    cout << sum;


    return 0;
}
