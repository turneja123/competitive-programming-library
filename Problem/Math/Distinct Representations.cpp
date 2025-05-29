//https://www.codechef.com/START187A/problems/DIREP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

long long ways[N];

int main() {
    IOS;
    for (int i = 0; i < 4; i++) {
        ways[i] = 1;
    }
    for (int i = 4; i < N; i++) {
        ways[i] = (ways[i - 1] + ways[i - 3]) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        long long ans = 1;
        char last = s[0]; int ct = 1;
        for (int i = 1; i < n; i++) {
            if (last == s[i]) {
                ans = ans * ways[ct] % M;
                ct = 0;
            }
            ct++;
            last = s[i];
        }
        ans = (ans * ways[ct]) % M;
        cout << ans << endl;
    }
    return 0;
}
