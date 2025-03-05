//https://atcoder.jp/contests/abc212/tasks/abc212_h
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 16;
const long long M = 998244353;
const long long inv2 = (M + 1) / 2;

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

struct FWHT{
    int P1[1 << N], P2[1 << N];
    void wt(int *a, int n) {
        if (n == 0) {
            return;
        }
        int m = n / 2;
        wt(a, m);
        wt(a + m, m);
        for (int i = 0; i < m; i++) {
            int x = a[i], y = a[i + m];
            a[i] = (x + y) % M, a[i + m] = (x - y + M) % M;
        }
    }
    void iwt(int* a, int n) {
        if (n == 0) {
            return;
        }
        int m = n / 2;
        iwt(a, m);
        iwt(a + m, m);
        for (int i = 0; i < m; i++) {
            int x = a[i], y = a[i + m];
            a[i] = 1LL * (x + y) * inv2 % M, a[i + m] = 1LL * (x - y + M) * inv2 % M;
        }
    }
    vector<int> multiply(int n, vector<int> A, vector<int> B) {
        A.resize(n); B.resize(n);
        for (int i = 0; i < n; i++) {
            P1[i] = A[i];
        }
        for (int i = 0; i < n; i++) {
            P2[i] = B[i];
        }
        wt(P1, n);
        wt(P2, n);
        for (int i = 0; i < n; i++) {
            P1[i] = 1LL * P1[i] * P2[i] % M;
        }
        iwt(P1, n);
        return vector<int>(P1, P1 + n);
    }
    vector<int> pow(int n, vector<int> A, long long k) {
        A.resize(n);
        for (int i = 0; i < n; i++) {
            P1[i] = A[i];
        }
        wt(P1, n);
        /*for (int i = 0; i < n; i++) {
            P1[i] = modPow(P1[i], k);
        }
        iwt(P1, n);*/
        return vector<int>(P1, P1 + n);
    }
}fwht;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<int> freq(1 << N);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    vector<int> F = fwht.pow(1 << N, freq, 1);
    long long sum = 0;
    for (int i = 0; i < 1 << N; i++) {
        if (F[i] != 1) {
            sum += (long long)F[i] * (1 - modPow(F[i], n) + M) % M * modPow(1 - F[i] + M, M - 2) % M;
        } else {
            sum += n;
        }
        sum %= M;
    }
    sum = sum * modPow(1 << N, M - 2) % M;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + modPow(k, i)) % M;
    }
    ans = (ans - sum + M) % M;
    cout << ans;
    return 0;
}
