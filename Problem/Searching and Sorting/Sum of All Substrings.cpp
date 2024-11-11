//https://atcoder.jp/contests/abc379/tasks/abc379_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

long long pw[N];
long long pref[N];

int main() {
    IOS;
    int n;
    string s;
    cin >> n >> s;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        pref[i] = (i == 0 ? s[i] - '0' : pref[i - 1] + (s[i] - '0'));
        pw[n - i] = pref[i] * (i + 1) - sum;
        sum += pref[i];
    }
    string ans = "";
    long long carry = 0;
    for (int i = 1; i <= 2 * n; i++) {
        long long cur = pw[i] + carry;
        if (cur == 0) {
            break;
        }
        ans += '0' + (cur % 10);
        carry = cur / 10;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}
