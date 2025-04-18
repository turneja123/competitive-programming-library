//https://codeforces.com/contest/1834/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = N * 30;
const int K = 20;

int a[N];
int freq[N * 30];
long long table[K][N];


long long lcm(long long a, long long b) {
    if (a == -1 || b == -1) {
        return -1;
    }
    return a * b / __gcd(a, b);
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = (a[i - 1] >= INF ? -1 : a[i - 1]);
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = lcm(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            if (table[k][i] >= INF) {
                table[k][i] = -1;
            }
        }
    }
    return;
}

long long query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    long long x = lcm(table[k][l], table[k][r - (1 << k) + 1]);
    if (x >= INF) {
        return -1;
    }
    return x;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(n);
        vector<int> restore;
        for (int i = 0; i < n; i++) {
            int last = 0, L = i;
            while (L < n) {
                int l = L, r = n - 1, spl = n;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int x = query(i, mid);
                    if (x != last) {
                        spl = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                if (spl == n) {
                    break;
                }
                int y = query(i, spl);
                if (y == -1) {
                    break;
                }
                if (freq[y] == 0) {
                    freq[y] = 1;
                    restore.push_back(y);
                }
                last = y;
                L = spl + 1;
            }
        }
        for (int i = 1; i < 30 * N; i++) {
            if (freq[i] == 0) {
                cout << i << endl;
                break;
            }
        }
        for (int i : restore) {
            freq[i] = 0;
        }
    }
    return 0;
}
