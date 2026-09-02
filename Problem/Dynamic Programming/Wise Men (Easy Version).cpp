//https://codeforces.com/contest/1326/problem/F1
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 14;

string s[N];

ll dpa[1 << 7], dpb[2][1 << 7], ct[N][1 << 7];
ll ans[1 << N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    if (n == 2) {
        if (s[0][1] == '1') {
            cout << "0 2";
        } else  {
            cout << "2 0";
        }
        return 0;
    }
    int k = n / 2 + n % 2;
    for (int mask = 0; mask < 1 << n; mask++) {
        if (__builtin_popcount(mask) != k) {
            continue;
        }
        vector<int> a, b;
        for (int i = 0; i < n; i++) {
            int c = mask & (1 << i);
            if (c) {
                a.push_back(i);
            } else {
                b.push_back(i);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int x = 0; x < 1 << k; x++) {
                ct[i][x] = 0;
            }
        }

        vector<int> tb = b;
        do {
            int cur = 0;
            for (int i = 0; i < tb.size() - 1; i++) {
                int l = tb[i], r = tb[i + 1];
                if (s[l][r] == '1') {
                    cur |= 1 << i;
                }
            }
            ct[tb[0]][cur]++;

        } while (next_permutation(tb.begin(), tb.end()));

        for (int j = 0; j < k; j++) {

            vector<int> ta = a;
            ta.erase(ta.begin() + j);
            do {
                int cur = 0;
                for (int i = 0; i < ta.size() - 1; i++) {
                    int l = ta[i], r = ta[i + 1];
                    if (s[l][r] == '1') {
                        cur |= 1 << i;
                    }
                }
                int l = ta.back(), r = a[j];
                if (s[l][r] == '1') {
                    cur |= 1 << (k - 2);
                }
                dpa[cur]++;

            } while (next_permutation(ta.begin(), ta.end()));

            for (int i = 0; i < b.size(); i++) {
                int f = 0;
                int l = a[j], r = b[i];
                if (s[l][r] == '1') {
                    f = 1;
                }
                for (int y = 0; y < 1 << (n - k - 1); y++) {
                    dpb[f][y] += ct[r][y];
                }
            }

            for (int x = 0; x < 1 << (k - 1); x++) {
                for (int y = 0; y < 1 << (n - k - 1); y++) {
                    for (int f = 0; f < 2; f++) {
                        int mask = x | (f ? 1 << (k - 1) : 0) | (y << k);
                        ans[mask] += dpa[x] * dpb[f][y];
                    }
                }
            }
            for (int x = 0; x < 1 << k; x++) {
                dpa[x] = 0;
                dpb[0][x] = 0;
                dpb[1][x] = 0;
            }
        }
    }
    for (int i = 0; i < 1 << (n - 1); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
