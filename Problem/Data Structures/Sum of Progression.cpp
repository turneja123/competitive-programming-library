//https://codeforces.com/contest/1921/problem/F
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long

const int N = 1e5 + 500;
const int M = sqrt(N);

long long a[N];
long long pref[N][M];
long long prefsum[N][M];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int sq = sqrt(n);
        for (int k = 1; k < sq; k++) {
            for (int j = 1; j <= k; j++) {
                long long sum = 0, total = 0, ct = 1;
                for (int i = j; i <= n; i += k) {
                    sum += a[i];
                    total += a[i] * ct;
                    ct++;
                }
                for (int i = j; i <= n; i += k) {
                    pref[i][k] = total;
                    prefsum[i][k] = sum;
                    total -= sum;
                    sum -= a[i];
                }
            }
        }
        for (int i = 0; i < q; i++) {
            long long s, d, k;
            cin >> s >> d >> k;
            if (d >= sq) {
                long long ans = 0;
                for (long long i = s, j = 0; j < k; i += d, j++) {
                    ans += (j + 1) * a[i];
                }
                cout << ans << " ";
            } else {
                long long ans = pref[s][d];
                if (s + d * k <= n) {
                    ans -= pref[s + d * k][d] + k * prefsum[s + d * k][d];
                }
                cout << ans << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
