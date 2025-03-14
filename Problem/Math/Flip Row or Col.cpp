//https://atcoder.jp/contests/abc396/tasks/abc396_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1 << 18;
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
    int n, m;
    cin >> n >> m;
    vector<int> a(1 << m, 0), b(1 << m);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') {
                mask += 1 << j;
            }
        }
        a[mask]++;
    }
    for (int j = 0; j < 1 << m; j++) {
        int pc = __builtin_popcount(j);
        b[j] = min(pc, m - pc);
    }
    int ans = M;
    vector<int> c = fwht.multiply(1 << m, a, b);
    for (int i = 0; i < 1 << m; i++) {
        ans = min(ans, c[i]);
    }
    cout << ans;
    return 0;
}
