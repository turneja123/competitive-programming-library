//solution for https://cses.fi/problemset/task/1624/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

char c[8][8];

int ans = 0;

void f(int n, vector<int> v) {
    for (int i = 0; i < 8; i++) {
        if (c[n][i] == '*') {
            continue;
        }
        bool flag = true;
        for (int j = 0; j < n; j++) {
            if (i - (n - j) == v[j] || i + (n - j) == v[j] || i == v[j]) {
                flag = false;
            }
        }
        if (flag) {
            if (n == 7) {
                ans++;
                return;
            }
            vector<int> tmp = v;
            tmp.push_back(i);
            f(n + 1, tmp);
        }
    }
}

int main() {
    IOS;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> c[i][j];
        }
    }
    vector<int> t;
    f(0, t);
    cout << ans;
    return 0;
}
