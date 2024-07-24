//https://csacademy.com/contest/archive/task/maxor/statement/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 17;
const int N = 1 << K;

long long a[N];
long long b[N];
long long ans[N];

int main() {
    IOS;
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
    for (int j = 0; j < N; j++) {
        ans[j] = a[j] * a[j];
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            int c = j & (1 << i);
            if (c) {
                ans[j] -= ans[j ^ (1 << i)];
            }
        }
    }
    long long mx = 0, best = 0;
    for (int j = 0; j < N; j++) {
        long long ct = (ans[j] - b[j]) / 2;
        if (ct > 0) {
            mx = ct, best = j;
        }
    }
    cout << best << " " << mx;

    return 0;
}
