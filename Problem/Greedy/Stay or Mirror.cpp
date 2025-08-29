//https://codeforces.com/contest/2129/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int sum = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (a[j] > a[i]) {
                    sum++;
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[i]) {
                    sum++;
                }
            }
        }
        sum /= 2;
        ans = sum;
        for (int i = n - 1; i >= 0; i--) {
            int olds = sum, olda = a[i];
            for (int j = 0; j < i; j++) {
                if (a[j] > a[i]) {
                    sum--;
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[i]) {
                    sum--;
                }
            }
            a[i] = 2 * n - a[i];
            for (int j = 0; j < i; j++) {
                if (a[j] > a[i]) {
                    sum++;
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[i]) {
                    sum++;
                }
            }
            ans = min(ans, sum);
            if (sum > olds) {
                a[i] = olda;
                sum = olds;
            }
        }
        cout << ans << endl;

    }
    return 0;
}
