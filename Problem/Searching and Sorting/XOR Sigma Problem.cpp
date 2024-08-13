//https://atcoder.jp/contests/abc365/tasks/abc365_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pref[N];
int ct[30];

int main() {
    IOS;
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum ^= a[i];
        pref[i] = sum;
        for (int j = 0; j < 30; j++) {
            int c = sum & (1 << j);
            if (c) {
                ct[j]++;
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 30; j++) {
            ans += (long long)ct[j] * (1 << j);
            int c = a[i] & (1 << j);
            if (c) {
                ct[j]--;
                ct[j] = n - i - 1 - ct[j];
            }
        }
        ans -= a[i];
    }
    cout << ans;
    return 0;
}
