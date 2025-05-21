//https://cses.fi/problemset/task/3233
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1 << 20;
const long long M = 998244353;
const long long inv2 = (M + 1) / 2;

struct FWHT{
    int P1[N], P2[N];
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
}fwht;

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(N, 0), b(N, 0);
    int s = 0, z = 0;
    a[0]++, b[0]++;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s ^= x;
        a[s]++, b[s]++;
        if (a[s] > 1) {
            z = 1;
        }
    }
    vector<int> ans = fwht.multiply(N, a, b);
    vector<int> out;
    if (z) {
        out.push_back(0);
    }
    for (int i = 1; i < N; i++) {
        if (ans[i]) {
            out.push_back(i);
        }
    }
    cout << out.size() << endl;
    for (int x : out) {
        cout << x << " ";
    }
    return 0;
}
