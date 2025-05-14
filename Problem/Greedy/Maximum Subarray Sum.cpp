//https://codeforces.com/contest/2107/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

string s;

long long calc(vector<long long> &v) {
    int n = v.size();
    long long best = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur += v[i];
        best = max(best, cur);
        cur = max(cur, 0ll);
    }
    return best;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long k;
        cin >> n >> k;
        cin >> s;
        vector<long long> a(n);
        int l = -1, r = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (s[i] == '0' && l == -1) {
                l = i;
            } else if (s[i] == '0' && l != -1 && r == -1) {
                r = i - 1;
            }
        }
        if (r == -1) {
            r = n - 1;
        }
        long long mx = -INF;
        for (int i = 0; i < n;) {
            if (s[i] == '0') {
                i++;
                continue;
            }
            vector<long long> v;
            while (i < n && s[i] == '1') {
                v.push_back(a[i]);
                i++;
            }
            mx = max(mx, calc(v));
        }
        if (l == -1 && mx == k) {
            cout << "Yes" << endl;
            for (int i = 0; i < n; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
            continue;
        }
        if (l == -1 && mx != k) {
            cout << "No" << endl;
            continue;
        }
        if (mx > k) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        vector<long long> ans = a;
        for (int i = r + 1; i < n; i++) {
            if (s[i] == '0') {
                ans[i] = -INF;
            }
        }
        long long sum = 0, mn = 0;
        mx = 0;
        for (int i = 0; i <= l; i++) {
            sum += a[i];
            mn = min(mn, sum);
        }
        for (int i = l; i <= r; i++) {
            sum += a[i];
            mx = max(mx, sum - mn);
        }
        ans[l] = k - mx;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
