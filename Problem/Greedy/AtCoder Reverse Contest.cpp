//https://atcoder.jp/contests/arc229/tasks/arc229_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int x;
    cin >> x;
    int n = 99 - 99 / 2;
    vector<int> v(n, 1);
    int ct = 625, pos = 25;
    for (int i = n / 2; i < n; i++) {
        v[i] = 0;
    }
    for (int j = 0; j < ct - x; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (v[i] == 1 && v[i + 1] == 0) {
                swap(v[i], v[i + 1]);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (v[i] == 1) {
            cout << 'A';
        } else {
            cout << 'C';
        }
        if (i != n - 1) {
            cout << 'R';
        }
    }


    return 0;
}
