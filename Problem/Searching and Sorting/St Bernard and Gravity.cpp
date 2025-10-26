//https://www.spoj.com/problems/BGRAVITY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 30000;
const int M = 30;

char a[N][M];

vector<pair<int, int>> st[M];


void go(int j, int n, int m) {
    while (1) {
        auto [x, y] = st[j].back();
        if (x == n - 1 || a[x + 1][y] == 'X') {
            break;
        }
        if (a[x + 1][y] == '.') {
            st[j].push_back({x + 1, y});
        } else if (y != 0 && a[x][y - 1] == '.' && a[x + 1][y - 1] == '.') {
            st[j].push_back({x + 1, y - 1});
        } else if (y != m - 1 && a[x][y + 1] == '.' && a[x + 1][y + 1] == '.') {
            st[j].push_back({x + 1, y + 1});
        } else {
            break;
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j];
        }
    }
    for (int j = 0; j < m; j++) {
        st[j].push_back({0, j});
        go(j, n, m);
    }
    int q;
    cin >> q;
    for (int t = 0; t < q; t++) {
        int j;
        cin >> j;
        j--;
        auto [x, y] = st[j].back();
        a[x][y] = 'O';
        for (int j = 0; j < m; j++) {
            auto [x, y] = st[j].back();
            if (a[x][y] == 'O') {
                st[j].pop_back();
                go(j, n, m);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }


    return 0;
}
