//https://csacademy.com/contest/archive/task/and-closure/statement/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 20;
const int N = 1 << K;

int freq[N];
int a[N];
int b[N];
int ans[N];
int temp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    a[0] = 1, ans[0] = 1;
    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        freq[x]++;
        ans[x] = 1;
    }
    int ct = 0;
    for (int t = 0; t < K; t++) {
        for (int j = 0; j < N; j++) {
            temp[j] = ans[j];
            if (freq[j] > 0) {
                a[j] = 1;
            } else {
                a[j] = 0;
            }
        }
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                int c = j & (1 << i);
                if (c) {
                    ans[j ^ (1 << i)] += ans[j];
                    a[j ^ (1 << i)] += a[j];
                }
            }
        }
        for (int j = 0; j < N; j++) {
            b[j] = ans[j] * a[j];
        }
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                int c = j & (1 << i);
                if (c) {
                    b[j ^ (1 << i)] -= b[j];
                }
            }
        }
        int cur = 0;
        for (int j = 0; j < N; j++) {
            ans[j] = max(temp[j], b[j]);
            cur += ans[j] > 0;
            ans[j] = min(ans[j], 1);
        }
        if (cur == ct) {
            break;
        }
        ct = cur;
    }
    cout << ct;

    return 0;
}
