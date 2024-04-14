//https://www.spoj.com/problems/DCEPC203/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10000000;
bitset<N / 10> prime;
bitset<N> mark;

pair<int, int> queries[1005];
int ans[1005];
int ind = 0;

long long mul(long long x, long long y, long long m){
    long long k = (x * (double)y / m) + 0.5, r = x * y - k * m;
    return r < 0 ? r + m : r;
}

long long modPow(long long x, long long y, long long m) {
    long long res = 1;
    while (y > 0) {
        if (y & 1){
            res = mul(res, x, m);
        }
        x = mul(x, x, m);
        y >>= 1;
    }
    return res;
}

int tonelli_shanks(int a, int p) {
    if (a == 0) {
        return 0;
    }
    if (modPow(a, (p - 1) / 2, p) != 1) {
        return -1;
    }
    if (p % 4 == 3) {
        return modPow(a, (p + 1) / 4, p);
    }
    int s = p - 1, n = 2, r = 0;
    while (s % 2 == 0) {
        r++;
        s /= 2;
    }
    while (modPow(n, (p - 1) / 2, p) != p - 1) {
        n++;
    }
    int x = modPow(a, (s + 1) / 2, p), b = modPow(a, s, p), g = modPow(n, s, p), m = 1;
    while (m) {
        int t = b;
        m = 0;
        for (; m < r && t != 1; m++) {
            t = (long long)t * t % p;
        }
        if (m == 0) {
            return x;
        }
        int gs = modPow(g, 1ll << (r - m - 1), p);
        g = (long long)gs * gs % p;
        x = (long long)x * gs % p;
        b = (long long)b * g % p;
        r = m;
    }
    return 0;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        queries[i] = make_pair(a, i);
    }
    sort(queries, queries + n);
    int ct = 0;
    prime[2] = true;
    for (int i = 3; i < N / 10; i += 2) {
        prime[i] = true;
    }
    for (int i = 3; i * i < N / 10; i += 2){
        for (int j = i * i; prime[i] && j < N / 10; j += (i << 1)){
            prime[j] = false;
        }
    }
    for (int i = 7; i < N / 10; i++) {
        if (!prime[i]) {
            continue;
        }
        int x = tonelli_shanks((i + 1) / 2, i);
        if (x == -1) {
            continue;
        }
        for (int j = i + x; j < N; j += i) {
            mark[j] = true;
        }
        for (int j = i + i - x; j < N; j += i) {
            mark[j] = true;
        }
    }
    for (long long i = 2; i <= N; i++) {
        while (ind < n && queries[ind].first == i) {
            ans[queries[ind].second] = ct;
            ind++;
        }
        if (mark[i]) {
            continue;
        }
        long long k = i * i * 2 - 1;
        ct += modPow(k - 2, k - 1, k) == 1;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
