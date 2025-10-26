//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    freopen("1.txt", "r", stdin);
    freopen("2.txt", "w", stdout);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        string ans = "Bob";
        int z = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == 'A') {
                z++;
            } else {
                z--;
            }
            if (z > 0) {
                ans = "Alice";
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;
    }

    return 0;
}
