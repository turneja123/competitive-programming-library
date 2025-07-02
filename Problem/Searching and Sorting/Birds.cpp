//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/10
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        long long ans = 0;
        int x = 0;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'R') {
                ans += x;
                x++;
                cur += -1;
            } else {
                ans += x + cur;
                cur += 1;
            }
            cur = max(cur, 0);
        }
        cout << ans << endl;

    }

    return 0;
}
