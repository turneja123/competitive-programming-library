//https://codeforces.com/contest/786/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 2000;

int a[N];
int last[N];
int ans[N];

int calc(int n, int k) {
    for (int i = 0; i < n; i++) {
        last[i] = -1;
    }
    int ans = 1;
    for (int i = 0, st = 0, cur = 0; i < n; i++) {
        if (last[a[i]] < st) {
            cur++;
        }
        if (cur > k) {
            cur -= k;
            ans++;
            st = i;
        }
        last[a[i]] = i;
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 1; i <= min(SQ, n); i++) {
        ans[i] = calc(n, i);
    }
    for (int i = SQ + 1; i <= n;) {
        ans[i] = calc(n, i);
        int l = i, r = n, spl = l;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (calc(n, mid) == ans[i]) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        int cur = ans[i];
        while (i <= spl) {
            ans[i++] = cur;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}

