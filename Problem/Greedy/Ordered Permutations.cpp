//https://codeforces.com/contest/2040/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50;

long long pw[N];

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2;
    }
    int t;
    cin >> t;
    while (t--) {
        int n; long long k;
        cin >> n >> k;
        if (n == 1) {
            if (k == 1) {
                cout << 1 << endl;
            } else {
                cout << -1 << endl;
            }
            continue;
        }
        vector<int> ans(n, 0);
        if (n < N && pw[n - 1] < k) {
            cout << -1 << endl;
            continue;
        }
        int i = 0, j = n - 1, p = 0;
        k--;
        while (p < n) {
            int ind = n - 2 - p;
            if (ind < N) {
                long long c = k & pw[ind];
                if (!c) {
                    ans[i++] = p++;
                } else {
                    ans[j--] = p++;
                }
            } else {
                ans[i++] = p++;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
