//https://codeforces.com/contest/2101/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

vector<pair<int, int>> mov{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int a[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int x = n / 2 - ((n + 1) % 2), y = n / 2 - ((n + 1) % 2);
        int i = 0, j = 1, z = 0, p = 0;
        a[x][y] = i;
        while (x < n && y < n && x >= 0 && y >= 0) {
            for (int k = 0; k < j; k++) {
                x += mov[p].first;
                y += mov[p].second;
                if (x < 0 || y < 0) {
                    break;
                }
                a[x][y] = ++i;
            }
            z++;
            if (z % 2 == 0) {
                j++;
                z = 0;
            }
            p = (p + 1) % 4;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }


    return 0;
}
