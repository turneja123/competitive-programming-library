//https://codeforces.com/contest/1717/problem/E
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long ans[N];

int spf[N];
int ind[N];
bool is_prime[N];
bool sorted[N];
vector<int> divs[N];

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
	long long tot = 0;
    int n;
    cin >> n;
    for (int k = 2; k < n; k++) {
        if (!sorted[k]) {
            sort(divs[k].begin(), divs[k].end(), greater<int>());
            sorted[k] = true;
        }
        for (int j : divs[k]) {
            ans[j] = k / j;
        }
        for (int j : divs[k]) {
            for (int p : divs[j]) {
                if (j != p) {
                    ans[p] -= ans[j];
                }
            }
            if (j != k) {
                tot += ans[j] * j * (n - k) / __gcd(j, n - k);
            }
        }
    }
    cout << tot % M << endl;
	return 0;
}
