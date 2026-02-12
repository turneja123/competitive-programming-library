//https://codeforces.com/contest/1548/problem/D1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll unsigned long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6005;

int freq[4][4];

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> p;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x %= 4, y %= 4;
        p.push_back({x, y});
        freq[x][y]++;
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto [x, y] = p[i];
        freq[x][y]--;
        for (int xa = 0; xa < 4; xa++) {
            for (int ya = 0; ya < 4; ya++) {
                for (int xb = 0; xb < 4; xb++) {
                    for (int yb = 0; yb < 4; yb++) {
                        int b = __gcd(abs(x - xa), abs(y - ya)) + __gcd(abs(x - xb), abs(y - yb)) + __gcd(abs(xa - xb), abs(ya - yb));
                        if ((b % 4 == 0 && abs((xa - x) * (yb - y) - (xb - x) * (ya - y)) % 4 == 0) || (b % 4 != 0 && abs((xa - x) * (yb - y) - (xb - x) * (ya - y)) % 4 == 2)) {
                            ans += freq[xa][ya] * freq[xb][yb];
                            if (xa == xb && ya == yb) {
                                ans -= freq[xa][ya];
                            }
                        }
                    }
                }
            }
        }
        freq[x][y]++;
    }
    cout << ans / 6;


    return 0;
}
