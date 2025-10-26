//https://evaluator.hsin.hr/events/coci26_1/tasks/HONI252615krugomet/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 30;

int up[K][N];
int a[N];
int ans[N];


int kth(int u, int k) {
    for (int i = K - 1; i >= 0; i--) {
        int c = k & (1 << i);
        if (c) {
            u = up[i][u];
        }
    }
    return u;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        j--;
        up[0][i] = j;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    for (int i = 0; i < n; i++) {
        int j = kth(i, k);
        ans[j] += a[i];
    }
    int mx = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx, ans[i]);
    }
    cout << mx << endl;
    for (int i = 0; i < n; i++) {
        if (ans[i] == mx) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
