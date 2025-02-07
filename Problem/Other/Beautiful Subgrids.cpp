//https://cses.fi/problemset/task/2137
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

string s[N];
bitset<N> b[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '1') {
                b[i].set(j);
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int ct = (b[i] & b[j]).count();
            ans += (long long)ct * (ct - 1) / 2;
        }
    }
    cout << ans;


    return 0;
}
