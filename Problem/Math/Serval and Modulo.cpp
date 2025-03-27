//https://codeforces.com/contest/2085/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

int freq[N];
int a[N], b[N];

bool calc(int n, int k) {
    bool can = true;
    for (int i = 0; i < n; i++) {
        freq[a[i] % k]++;
    }
    for (int i = 0; i < n && can; i++) {
        freq[b[i]]--;
        if (freq[b[i]] < 0) {
            can = false;
        }
    }
    for (int i = 0; i < n; i++) {
        if (freq[a[i] % k] != 0 || freq[b[i]] != 0) {
            can = false;
        }
        freq[a[i] % k] = 0;
        freq[b[i]] = 0;
    }
    return can;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long s = 0;
        int mxa = 0, mxb = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            s += a[i];
            mxa = max(mxa, a[i]);
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            s -= b[i];
            mxb = max(mxb, b[i]);
        }
        if (s <= 0) {
            int ans = mxa + 1;
            sort(a, a + n);
            sort(b, b + n);
            for (int i = 0; i < n; i++) {
                if (a[i] != b[i]) {
                    ans = -1;
                }
            }
            cout << ans << endl;
            continue;
        }
        int ans = -1;
        long long sq = sqrtl(s);
        for (long long k = 1; k <= sq; k++) {
            if (s % k == 0) {
                if (k > mxb) {
                    bool can = calc(n, k);
                    if (can) {
                        ans = k;
                        break;
                    }
                }
                if (s / k > mxb && s / k <= INF) {
                    bool can = calc(n, s / k);
                    if (can) {
                        ans = s / k;
                        break;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
