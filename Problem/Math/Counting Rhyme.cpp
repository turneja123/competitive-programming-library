//https://codeforces.com/contest/1884/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

long long a[N];
long long sum[N];
long long ans[N];
bool divs[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            m = max(m, x);
            a[x]++;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j += i) {
                sum[i] += a[j];
            }
        }
        for (int i = 1; i <= m; i++) {
            ans[i] = sum[i] * sum[i];
            if (a[i]) {
                for (int j = i; j <= m; j += i) {
                    divs[j] = true;
                }
            }
        }
        for (int i = m; i >= 1; i--) {
            for (int j = i * 2; j <= m; j += i) {
                ans[i] -= ans[j];
            }
        }
        long long ct = (long long)n * (n - 1) / 2;
        for (int i = 1; i <= m; i++) {
            ans[i] = (ans[i] - a[i]) / 2;
            if (divs[i]) {
                ct -= ans[i];
            }
            sum[i] = 0, a[i] = 0, divs[i] = false;
        }
        cout << ct << endl;
    }

    return 0;
}
