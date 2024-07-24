//https://www.codechef.com/problems/ORAND
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 20;
const int N = 1 << K;

int freq[2][N];
int a[N];
int b[N];
int ans[N];
int temp[N];

void conv(int n, int k) {
    for (int t = 0; t < 2 * k; t++) {
        int bit = (t + 1) % 2;
        for (int j = 0; j < n; j++) {
            if (freq[bit][j] > 0) {
                a[j] = 1;
            } else {
                a[j] = 0;
            }
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                int c = j & (1 << i);
                if (c) {
                    int l = j, r = j ^ (1 << i);
                    if (bit) {
                        swap(l, r);
                    }
                    ans[l] += ans[r];
                    a[l] += a[r];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            b[j] = ans[j] * a[j];
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                int c = j & (1 << i);
                if (c) {
                    int l = j, r = j ^ (1 << i);
                    if (bit) {
                        swap(l, r);
                    }
                    b[l] -= b[r];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            ans[j] = max(temp[j], b[j]);
            ans[j] = min(ans[j], 1);
            temp[j] = ans[j];
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, mx = 0;
        cin >> n >> m;
        temp[0] = 1, a[0] = 1, ans[0] = 1;
        for (int j = 0; j < n; j++) {
            int y;
            cin >> y;
            freq[0][y]++;
            ans[y] = 1;
            temp[y] = 1;
            mx = max(mx, y);
        }
        for (int i = 0; i < m; i++) {
            int y;
            cin >> y;
            freq[1][y]++;
            mx = max(mx, y);
        }
        int k = 0; n = 1;
        while (mx >= n) {
            k++, n *= 2;
        }
        conv(n, k);

        int tot = 0;
        for (int j = 0; j < n; j++) {
            if (ans[j] > 0) {
                tot++;
            }
            ans[j] = 0;
            b[j] = 0;
            freq[0][j] = 0;
            freq[1][j] = 0;
            a[j] = 0;
            temp[j] = 0;
        }
        cout << tot << endl;

    }

    return 0;
}
