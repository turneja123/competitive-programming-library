//https://codeforces.com/contest/2007/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int deg[N];
string s;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            deg[u]++, deg[v]++;
        }
        cin >> s;
        int a = 0, b = 0, c = 0, rem = n - 1;
        for (int i = 1; i < n; i++) {
            if (deg[i] == 1) {
                if (s[i] == '0') {
                    a++;
                } else if (s[i] == '1') {
                    b++;
                } else {
                    c++;
                }
                rem--;
            } else if (s[i] != '?') {
                rem--;
            }
        }
        int ans;
        if (s[0] == '0') {
            ans = b + c / 2 + c % 2;
        } else if (s[0] == '1') {
            ans = a + c / 2 + c % 2;
        } else {
            ans = max(a, b) + c / 2;
            if (a == b && (rem % 2 == 1 && c % 2 == 1)) {
                ans++;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
        }

    }

    return 0;
}
