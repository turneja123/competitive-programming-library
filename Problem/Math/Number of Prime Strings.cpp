//https://www.spoj.com/problems/PSTR/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

int spf[N];
int ind[N];
bool is_prime[N];
bool sorted[N];
vector<int> divs[N];
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

int factor(int n, vector<pair<int, int>> &f) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        if (p != last) {
            if (last != -1) {
                f.push_back(make_pair(last, ct));
            }
            last = p;
            cnt *= ct + 1;
            ct = 1;
        } else {
            ct++;
        }
        n = n / p;
    }
    if (ct > 0) {
        cnt *= ct + 1;
        f.push_back(make_pair(last, ct));
    }
    return cnt;
}

void get_divs(int i, int cur, int n, vector<pair<int, int>> &f) {
    if (i == f.size()) {
        divs[n][ind[n]++] = cur;
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, n, f);
        cur *= f[i].first;
    }
    return;
}

int main() {
    IOS;
    sieve(N);
    vector<pair<int, int>> f;
    for (int i = 2; i < N; i++) {
        int d = factor(i, f);
        divs[i].resize(d);
        get_divs(0, 1, i, f);
        f.clear();
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> k >> n;
        if (n == 1) {
            cout << k << endl;
            continue;
        }
        for (int i : divs[n]) {
            if (!sorted[i]) {
                sort(divs[i].begin(), divs[i].end());
                sorted[i] = true;
            }
            ans[i] = modPow(k, i);
        }
        for (int i : divs[n]) {
            for (int j : divs[i]) {
                if (i != j) {
                    ans[i] = (ans[i] - ans[j] + M) % M;
                }
            }
        }
        cout << ans[n] << endl;
    }


    return 0;
}
