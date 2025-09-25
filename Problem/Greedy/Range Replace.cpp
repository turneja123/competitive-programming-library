//https://atcoder.jp/contests/arc206/tasks/arc206_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
int freq[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        freq[a[i]]++;
        if (a[i] != a[i + 1]) {
            ans += n - i - freq[a[i]];
        }
    }
    cout << ans + 1;
    return 0;
}
