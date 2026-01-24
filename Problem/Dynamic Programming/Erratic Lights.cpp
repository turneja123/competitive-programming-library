//https://qoj.ac/contest/2694/problem/15633
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 105;

ld dp[N][N];
int vis[N][N];


ld calc(vector<int> f, int n) {
    sort(f.begin(), f.end());
    int a = f[2], b = f[1], c = f[0];
    if (vis[a][b]) {
        return dp[a][b];
    }
    vis[a][b] = 1;
    if (b == 0) {
        return dp[a][b] = 0.0;
    }
    if (b == 1 && c == 0) {
        return dp[a][b] = 3.0;
    }


    if (c > 0) {
        f[0]--;
        f[1]++;
        ld x = calc(f, n);
        f[1]--;
        f[2]++;
        ld y = calc(f, n);
        ld ans = (1.0 + x / 3.0 + y / 3.0) * 3.0 / 2.0;
        return dp[a][b] = ans;
    } else {
        f[1]--;
        f[2]++;
        ld x = calc(f, n);
        ld ans = (1.0 + x / 3.0) * 3.0;
        return dp[a][b] = ans;
    }
}


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> f(3, 0);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'r') {
            f[0]++;
        } else if (s[i] == 'g') {
            f[1]++;
        } else {
            f[2]++;
        }
    }
    cout << calc(f, n);


    return 0;
}
