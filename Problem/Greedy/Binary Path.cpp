//https://codeforces.com/contest/1937/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        int has = -1;
        for (int i = 0; i < n; i++) {
            if (i == n - 1 || a[i + 1] == '1' && b[i] == '0') {
                has = i;
                break;
            }
        }
        int suf = -1;
        for (int i = 0; i < has; i++) {
            if (a[i + 1] == '0' && b[i] == '1') {
                suf = i;
            }
        }
        string ans = a.substr(0, has + 1) + b.substr(has, n - has);
        cout << ans << endl << has - suf << endl;
    }


    return 0;
}
