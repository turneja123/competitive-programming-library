//https://codeforces.com/contest/1285/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int D = 300;

vector<int> d[N];
int freq[N];
int ct[N];
long long pairs[N];

vector<int> divs[N];

vector<int> factors;
vector<int> expo;

int spf[N];
bool is_prime[N];


int n;
int idx = 0;

pair<pair<int, int>, int> masks[D];

long long a[D];

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
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        freq[a]++;
        ans = max(ans, (long long)a);
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            if (freq[j]) {
                d[i].push_back(j / i);
            }
            divs[j].push_back(i);

        }
    }
    for (int i = N - 1; i > 0; i--) {
        pairs[i] = (long long)d[i].size() * (d[i].size() - 1) / 2;
        for (int j = 2 * i; j < N; j += i) {
            pairs[i] -= pairs[j];
        }
    }
    for (int ii = 1; ii < N; ii++) {
        if (d[ii].size() < 2 || !pairs[ii]) {
            continue;
        }
        stack<int> s;
        reverse(d[ii].begin(), d[ii].end());
        s.push(d[ii][0]);
        for (int x : divs[d[ii][0]]) {
            ct[x]++;
        }
        for (int k = 1; k < d[ii].size(); k++) {
            n = d[ii][k];
            factor(n);
            expo.resize(factors.size());
            vector<pair<int, int>> f;
            int i = 0, j = 0, m = factors.size(), y = 1;
            while (i < m) {
                int cur = factors[i];
                while (i < m && factors[i] == cur) {
                    expo[i] = y;
                    i++;
                }
                f.push_back(make_pair(factors[j], i - j));
                y *= i - j + 1;
                j = i;
            }

            vector<pair<int, int>> v(f.size());
            get_divs(0, 1, 0, 0, 0, f, v);

            //O(logn * n^(1/3)))
            for (int i = 0; i < factors.size(); i++) {
                for (int k = 0; k < y; k++) {
                    int j = masks[k].first.first, h = masks[k].first.second, c = j & (1 << i);
                    if (c) {
                        int sub = h - expo[i];
                        if (valid(sub, i, j)) {
                            a[sub] -= a[h];
                        }
                    }
                }
            }
            int cur = 0;
            for (int k = 0; k < y; k++) {
                int h = masks[k].first.second, g = masks[k].second;
                if (g == 1) {
                    cur = a[h];
                }
            }
            if (cur != 0) {
                while (cur) {
                    if (__gcd(n, s.top()) == 1) {
                        cur--;
                    }
                    if (cur == 0) {
                        break;
                    }
                    for (int x : divs[s.top()]) {
                        ct[x]--;
                    }
                    s.pop();
                }
                ans = max(ans, (long long)n * s.top() * ii);
            }
            for (int x : divs[n]) {
                ct[x]++;
            }
            factors.clear();
            idx = 0;
            s.push(n);
        }
        for (int k = 0; k < d[ii].size(); k++) {
            for (int x : divs[d[ii][k]]) {
                ct[x] = 0;
            }
        }
    }
    cout << ans;
    return 0;
}
