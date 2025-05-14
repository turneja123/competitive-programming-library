//https://codeforces.com/contest/2007/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int a[N];
int d[N];

int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = d[i];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = __gcd(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return __gcd(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    set<int> pw;
    int p = 1;
    for (int i = 0; i < 30; i++) {
        pw.insert(p);
        p *= 2;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i > 0) {
                d[i] = abs(a[i] - a[i - 1]);
            }
        }
        build(n);
        int j = 0, last = a[0];
        for (int i = 1; i < n; i++) {
            if (last != a[i]) {
                last = a[i];
                j = i;
            }
            ans += i - j + 1;
            int l = 0, r = j - 1, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int g = query(mid + 1, i);
                if (pw.find(g) != pw.end()) {
                    spl = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ans += spl + 1;
        }

        cout << ans << endl;

    }
    return 0;
}
