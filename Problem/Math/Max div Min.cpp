//https://atcoder.jp/contests/abc356/tasks/abc356_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int freq[N];
int a[N];
long long pref[N];

long long sum(int l, int r) {
    return pref[r] - pref[l - 1];
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    long long ans = 0;
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + freq[i];
        ans += (long long)freq[i] * (freq[i] - 1) / 2;
    }
    for (int i = 0; i < n; i++) {
        int sq = sqrt(a[i]);
        for (int j = 1; j <= sq; j++) {
            int l = a[i] / (j + 1) + 1, r = a[i] / j;
            if (j == 1) {
                r--;
            }
            ans += (long long)j * sum(l, r);

        }
        for (int j = 1; j <= a[i]; j++) {
            if (a[i] / j <= sq) {
                break;
            }
            ans += (long long)a[i] / j * freq[j];
        }
    }
    cout << ans;

    return 0;
}
