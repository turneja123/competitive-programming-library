//https://www.codechef.com/problems/MAXOR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 20;
const int N = 1 << K;

long long a[N];
long long b[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            a[x]++;
            b[x]++;
        }

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                int c = j & (1 << i);
                if (c) {
                    a[j] += a[j ^ (1 << i)];
                }
            }
        }

        long long ans = 0;
        for (int j = 0; j < N; j++) {
            ans += (a[j] - b[j]) * b[j] + b[j] * (b[j] - 1) / 2;
            a[j] = 0, b[j] = 0;
        }
        cout << ans << endl;
    }

    return 0;
}
